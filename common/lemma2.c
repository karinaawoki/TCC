#include "lemma2.h"


int mEqualsN(Graph *G, int m, int root);
int searchByNode(Graph *G, int m, int root, int parent, int *descendant);
void printChildTree(Graph *G, int parent, int vertex);
int mLessThanN(Graph *G, int m, int root);
void save(Graph *G, int parent, int vertex);



int numVerticesCut = 0;
/* This modele prints the vertices of B (according to the 
    lemma2) and returns the number of edges at the cut.   */ 


int lemma2(Graph *G, int m, int root, int NumVert)
/*int main(int argc, char *argv[])*/
{
	if(DEBUG == 1)
		printf("m: %d\n", m);
	if(NumVert == m)
		return mEqualsN(G, m, root);
	else if(m == 0)
		return 0;
	else
		return mLessThanN(G, m, root);
}



int mEqualsN(Graph *G, int m, int root)
{
	/* Return the number of edges in the cut */
	/*int i;
	printf("trataaaar -----------");
	for(i = 0; i<m; i++)
	{
		printf("%d ", i);
		B[Blength++] = i;
		setB[i] = 1;
	}*/
	
	save(G, root, root);
	
	return 0;
}

int mLessThanN(Graph *G, int m, int root)
{
	int *descendant;
	descendant = malloc(G->V*sizeof(int));
	childNumber(G, root, descendant, root);
	numVerticesCut = 0;
	searchByNode(G, m, root, root, descendant);

	free(descendant);
	return numVerticesCut;
}


int searchByNode(Graph *G, int m, int root, int parent, int *descendant)
{
	/* Return the vertices number of B */
	Vertex *v;
	for(v = G->adj[root]->next; v!= NULL && 
		(descendant[v->vertex] <= m || v->edge==0 || v->vertex == parent) ; v = v->next)
		/* If the tree satisfies the condition of the lemma, the tree is a answer 
		 We don't need to comes down in the tree*/
		/* ??????????? */
	{
		if (descendant[v->vertex] > m/2.0 && v->vertex != parent && v->edge == 1)
			/* m/2.0  -->  m/2 */
		{
			int removeDescendant = descendant[v->vertex];
			if(DEBUG == 1)
				printf("encontrou filho certinho -- raiz: %d\n", v->vertex);
			printChildTree(G, root, v->vertex);
			save(G, root, v->vertex);

			/* separate B and W */
			eraseEdge(G, root, v->vertex);

			descendant[root] -= removeDescendant;
			numVerticesCut = 1;
			return removeDescendant;
		}
	}
	/* when (if) it finish, v will be the root of the tree with more than m vertices */
			
	/* Comes down in the tree */
	if (v != NULL)
	{
		int aux;
		if(DEBUG == 1)
			printf("Desceu para: %d \n", v->vertex);
		aux = searchByNode(G, m, v->vertex, root, descendant);
		descendant[root] -= aux;
		return aux;
	}

	/* Add trees (more than one) at B
	   If the answer is only one tree, it will be detected at the fist "for"*/
	else
	{
		int numVerticesB = 0;
		if(DEBUG == 1)
			printf("filhos com menos de m vertices.. raiz: %d\n", root);
		for(v = G->adj[root]; v->next!=NULL; v = v->next)
		{

			while (v->next!=NULL && numVerticesB + descendant[v->next->vertex] <= m 
				|| v->next->vertex == parent || v->next->edge != 1)
			{
				/* Sum each set (roots childs) */ 
				if(v->next->edge == 1 && v->next->vertex != parent)
				{
					if(DEBUG == 1)
						printf("  arvore filha sendo acrescentada raiz: %d\n", v->next->vertex);
					numVerticesB += descendant[v->next->vertex];
					printChildTree(G, root, v->next->vertex);
					save(G, root, v->next->vertex);
					/* Separate B and W */
					eraseEdge(G, root, v->next->vertex);
					v = v->next;
					numVerticesCut ++;
				}
				else
					v=v->next;
				if(v->next == NULL)
					break;
			}
			if( v->next==NULL )
				break;
			else if(v->next->vertex!=parent)
			{
				if(DEBUG == 1)
					printf("saiu \n");
				descendant[root] -= numVerticesB;

				return numVerticesB;
			}
		}
		descendant[root] -= numVerticesB;
		return numVerticesB;	
	}
}





/*-----------------------------------------------------------------------
  -----------------------------------------------------------------------
  ---------------------- AUXILIARY FUNTIONS -----------------------------
  -----------------------------------------------------------------------
  -----------------------------------------------------------------------*/

int childNumber(Graph *G, int root, int *descendant, int parent)
{
	/* This recursive function return rhe number of descendant
	it is used to construct the descendant vector
	-- descendant number includes the own root */
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != parent && i->edge == 1)
			sum += childNumber(G, i->vertex, descendant, root);
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
	printf("%d ", vertex);
}

void save(Graph *G, int parent, int vertex)
{
	/* save vertex and all of its descendants */
	Vertex *v;
	for(v = G->adj[vertex]->next; v!= NULL; v = v->next)
		if(v->vertex != parent && v->edge==1)
			save(G, vertex, v->vertex);	
    setB[vertex] = 1;
    Blength++;
}
