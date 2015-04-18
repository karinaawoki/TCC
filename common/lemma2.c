#include "lemma2.h"


int mEqualsN(int m);
int searchByNode(Graph *G, int m, int root, int parent, int *descendant);
void printChildTree(Graph *G, int parent, int vertex);
void deleteChildTree(Graph *G, int parent, int vertex);
int mLessThanN(Graph *G, int m, int root);


int numVerticesCut = 0;
/* This modele prints the vertices of B (according to the 
    lemma2) and returns the number of edges at the cut.   */ 


int lemma2(Graph *G, int m, int root)
/*int main(int argc, char *argv[])*/
{
	if(DEBUG)
		printf("m: %d\n", m);
	if(G->V == m)
		return mEqualsN(m);
	else if(m == 0)
		return 0;
	else
		return mLessThanN(G, m, root);
}



int mEqualsN(int m)
{
	/* Return the number of edges in the cut */
	int i;
	for(i = 0; i<m; i++)
		printf("%d ", i);
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
	for(v = G->adj[root]->next; v!= NULL && (descendant[v->vertex] <= m || v->vertex == parent) ; v = v->next)
		/* If the tree satisfies the condition of the lemma, the tree is a answer 
		 We don't need to comes down in the tree*/
		/* ??????????? */
	{
		if (descendant[v->vertex] > m/2 && v->vertex != parent)
			/* m/2.0  -->  m/2 */
		{
			int removeDescendant = descendant[v->vertex];
			if(DEBUG)
				printf("encontrou filho certinho -- raiz: %d\n", v->vertex);
			printChildTree(G, root, v->vertex);

			deleteChildTree(G, root, v->vertex);
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
		if(DEBUG)
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
		if(DEBUG)
			printf("filhos com menos de m vertices.. raiz: %d\n", root);
		for(v = G->adj[root]; v->next!=NULL; v = v->next)
		{
			if (numVerticesB + descendant[v->next->vertex] <= m && v->next->vertex != parent)
			{
				/* Sum each set (roots childs) */ 
				if(DEBUG)
					printf("  arvore filha sendo acrescentada raiz: %d\n", v->next->vertex);
				numVerticesB += descendant[v->next->vertex];
				printChildTree(G, root, v->next->vertex);
				deleteChildTree(G, root, v->next->vertex);
				numVerticesCut ++;
			}
			else if(v->next->vertex!=parent)
			{
				if(DEBUG)
					printf("saiu \n");
				descendant[root] -= numVerticesB;
				descendant[root] = -5;

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
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != parent)
			sum += childNumber(G, i->vertex, descendant, root);
	descendant[root] = ++sum;
	return sum;
}

void printChildTree(Graph *G, int parent, int vertex)
{
	Vertex *v;
	for(v = G->adj[vertex]->next; v!= NULL; v = v->next)
		if(v->vertex != parent)
			printChildTree(G, vertex, v->vertex);	
	printf("%d ", vertex);
}

void deleteChildTree(Graph *G, int parent, int vertex)
/* Delete the edge that connect the childTree with the tree */
{	
	Vertex *v;
	for(v = G->adj[parent]; v->next!=NULL; v = v->next)
		if (v->next->vertex == vertex)
		{
			Vertex *rem;
			rem = v->next;
			v->next = rem->next;
			free(rem);
			break;
		}

	for(v = G->adj[vertex]; v->next!=NULL; v = v->next)
		if(v->next->vertex == parent)
		{
			Vertex *rem;
			rem = v->next;
			v->next = rem->next;
			free(rem);
			break;
		}
}
