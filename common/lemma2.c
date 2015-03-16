#include "lemma2.h"


void mEqualsN(int m);
int mLessThanN(Graph *G, int m, int root);
int childNumber(Graph *G, int root, int *childs, int parent);
void printChildTree(Graph *G, int parent, int vertex);


void lemma2_(char *fileName, int m)
/*int main(int argc, char *argv[])*/
{
	int root;
	Graph *G;
	srand(seed);
	
	G = read(fileName);
	root = (int)(G->V*1.0*rand()/RAND_MAX);

	if(G->V == m)
		mEqualsN(m);
	else
		mLessThanN(G, m, root);
}




void mEqualsN(int m)
{
	int i;
	for(i = 0; i<m; i++)
		printf("%d ", i);
	printf("\n0\n");
}


int mLessThanN(Graph *G, int m, int root)
{
	int *childs;
	Vertex *v;
	int falseRoot = root, parent = root;

	childs = malloc(G->V*sizeof(int));
	childNumber(G, root, childs, root);

	while(1)
	{
		for(v = G->adj[falseRoot]; v!= NULL && (childs[v->vertex] <= m || v->vertex == parent) ; v = v->next)
			/* If the tree satisfies the condition of the lemma, the tree is a answer 
			 We don't need to comes down in the tree*/
			/* ??????????? */

			if (childs[v->vertex] > m/2.0 && v->vertex != parent)
			{
				printChildTree(G, falseRoot, v->vertex);
				printf("\n1\n");
				return 0;
			}
		/* when (if) it finish, v will be the root of the tree with more than m vertices */
		
		
		/* Comes down in the tree */
		if (v != NULL)
		{
			parent = falseRoot;
			falseRoot = v->vertex;
		}

		/* Add trees (more than one) at B
		   If the answer is only one tree, it will be detected at the fist "for"*/
		else
		{
			int numVerticesB = 0;
			int numVerticesCut = 0;
			for(v = G->adj[falseRoot]; v!=NULL; v = v->next)
			{
				if (numVerticesB + childs[v->vertex] <= m && v->vertex != parent)
				{
					numVerticesB += childs[v->vertex];
					printChildTree(G, falseRoot, v->vertex);
					numVerticesCut ++;
				}
				else if(v->vertex!=parent)
				{
					printf("\n%d \n", numVerticesCut);
					return 0;
				}
			}
			printf("\n%d\n", numVerticesCut);
			return 0;
		}
	}
	return 0;
}





/*-----------------------------------------------------------------------
  -----------------------------------------------------------------------
  ---------------------- AUXILIARY FUNTIONS -----------------------------
  -----------------------------------------------------------------------
  -----------------------------------------------------------------------*/

int childNumber(Graph *G, int root, int *childs, int parent)
{
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]; i!= NULL; i = i->next)
		if (i->vertex != parent)
			sum += childNumber(G, i->vertex, childs, root);
	childs[root] = ++sum;
	return sum;
}

void printChildTree(Graph *G, int parent, int vertex)
{
	Vertex *v;
	for(v = G->adj[vertex]; v!= NULL; v = v->next)
		if(v->vertex != parent)
			printChildTree(G, vertex, v->vertex);	
	printf("%d ", vertex);
}
