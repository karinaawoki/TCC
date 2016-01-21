#include "simpleApproxCut.h"


int mEqualsN(Graph *G, int m, int root, int parent);
int Algorithm1(Graph *G, int NumVert, int m, int root, int *descendant, int parent);
void printChildTree(Graph *G, int parent, int vertex);
void save(Graph *G, int parent, int vertex);



int numEdgesCut = 0; /* Updates the vector of descendants */
/* This model prints the vertices of B (according to the 
    simpleApproxCut - lemma2) and returns the number of edges at the cut.   */ 


int Algorithm2(Graph *G, int m, int root, int NumVert, int leftNeighbor, int rightNeighbor)
{
	/* Returns the number of edges in the cut */
	int *descendant, i, mPrime = m;
	Vertex *v;

	if(STEP) printf("      Simple approximate cut (Lemma 2)\n");
	if(DEBUG || STEP) {
		printf("        root: %d\n", root);
		printf("        m: %d\n", m);
	}
	
	descendant = malloc(G->V*sizeof(int));
	for (i = 0; i < G->V; i++)
	{
		descendant[i] = -1;
	}
	descendantsNumber(G, root, descendant, leftNeighbor, rightNeighbor);
	numEdgesCut = 0;


	for(v = G->adj[root]->next; v!=NULL; v = v->next)
	/* Components V_1,...,V_n */
	{
		if(v->vertex != rightNeighbor && v->vertex != leftNeighbor && v->edge!=0)
		{
			if(DEBUG) printf("vertex (sub-tree): %d\n", v->vertex);
			if(descendant[v->vertex] <= mPrime)
			{
				save(G, root, v->vertex);

				mPrime -= descendant[v->vertex];
				eraseEdge(G, root, v->vertex);
			}
			else
				break;
		}
		if(DEBUG) printf("mPrime: %d\n", mPrime);
	}

	if(mPrime > 0)
	{
		if(v == NULL) printf("ERROR: m = |Tz| \n");
		Algorithm1(G, NumVert, mPrime, v->vertex, descendant, root);
	}

	free(descendant);
	return numEdgesCut;
}






int Algorithm1(Graph *G, int NumVert, int m, int root, int *descendant, int parent)
/* Adaptation of Algorithm 1. 
   Input: tree T with adjacent vertices root and parent, m, descendant. 
   Corresponding input of Algorithm 2: a tree T' consisting of the component of T-parent containing root
   T'has at least m vertices, and descendant is the number of descendants of each vertex in T' with root. 
   Computes a cut (B,W) in T' where m/2 < |B| <= m with e(B,W) <= Delta(G). */

{
	Vertex *v;
	int adequadeChild = -1;

	if(NumVert == m)
		return mEqualsN(G, m, root, parent);

	
	for(v = G->adj[root]->next; v!= NULL; v = v->next)
	{
		/* Comes down in the tree */
		if(descendant[v->vertex] > m && v->edge!=0 && v->vertex != parent)
		{
			int aux;
			if(DEBUG == 1) printf("Desceu para: %d \n", v->vertex);
			aux = Algorithm1(G, NumVert, m, v->vertex, descendant, root);
			descendant[root] -= aux;
			return aux;
		}
		else if(descendant[v->vertex] > m/2.0 && v->edge!=0 && v->vertex != parent)
		{
			/* finds, if exist, a subtree that satifies the lemma condition  */
			adequadeChild = v->vertex;
		}
	}
	
	if(adequadeChild != -1)
	{
		int removeDescendant = descendant[adequadeChild];
		printChildTree(G, root, adequadeChild);
		save(G, root, adequadeChild);

		/* separate B and W */
		eraseEdge(G, root, adequadeChild);

		descendant[root] -= removeDescendant;
		return removeDescendant;
	}
	

	else
	{
	/* Add trees (more than one) at B
	   If the answer is only one tree, it will be detected at above condition */
		int numVerticesB = 0;
		if(DEBUG == 1)
			printf("filhos com menos de m vertices.. raiz: %d\n", root);
		for(v = G->adj[root]; v->next!=NULL;v = v->next)
		{

			/* Sum each set (roots childs) */ 
			if(v->next->edge == 1 && v->next->vertex!= parent)
			{
				if(numVerticesB + descendant[v->next->vertex] <= m)
				{
					if(DEBUG == 1)
						printf("  arvore filha sendo acrescentada raiz: %d\n", v->next->vertex);
					numVerticesB += descendant[v->next->vertex];
					printChildTree(G, root, v->next->vertex);
					save(G, root, v->next->vertex);
					/* Separate B and W */
					eraseEdge(G, root, v->next->vertex);
					numEdgesCut ++;
				}
				else
				{
					break;
				}
			}
		}
		descendant[root] -= numVerticesB;
		return numVerticesB;	
	}
}




int mEqualsN(Graph *G, int m, int root, int parent)
{
	/* Returns the number of edges in the cut */
	save(G, parent, root);
	
	eraseEdge(G, parent, root);

	return 0;
}




/*-----------------------------------------------------------------------
  -----------------------------------------------------------------------
  ---------------------- AUXILIARY FUNTIONS -----------------------------
  -----------------------------------------------------------------------
  -----------------------------------------------------------------------*/

int descendantsNumber(Graph *G, int root, int *descendant, int leftNeighbor, int rightNeighbor)
{
	/* This recursive function returns rhe number of descendant of the vertex root
	it is used to construct the descendant vector
	-- the number of descendant includes the own root */
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != leftNeighbor && i->vertex!=rightNeighbor && i->edge == 1)
			sum += descendantsNumber(G, i->vertex, descendant, root, -1);
	descendant[root] = ++sum;
	return sum;
}

void printChildTree(Graph *G, int parent, int vertex)
{
	/* print vertex and all of its descendants */
	Vertex *v;
	for(v = G->adj[vertex]->next; v!= NULL; v = v->next)
		if(v->vertex != parent && v->edge==1)
			printChildTree(G, vertex, v->vertex);	
	if (DEBUG) printf("printChildTree: %d \n", vertex);
}

void save(Graph *G, int parent, int vertex)
{
	/* save vertex and all of its descendants at setB */
	Vertex *v;
	for(v = G->adj[vertex]->next; v!= NULL; v = v->next)
		if(v->vertex != parent && v->edge==1)
			save(G, vertex, v->vertex);	
    setB[vertex] = 1;
    Blength++;
}
