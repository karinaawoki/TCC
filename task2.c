
#include "input.h"
#include "list/queue.h"


void mEqualsN(int m);
void mLessThanN(Graph *G, int m, int n);
int childNumber(Graph *G, int root, int *childs, int parent);



int main(int argc, char *argv[])
{
	/* argv[2] = m */

	int i, m = atoi(argv[2]);
	int root = 6;
	
	/*aletoriezar*/

	Graph *G;
	G = read(argv[1]);

	childNumber(G, root, childs, root);

	/*for(i = 0; i<G->V; i++)
	{
		printf("%d - %d\n", i, childs[i]);
	}*/
	if(G->V == m)
		mEqualsN(m);

	return 0;
}



void mEqualsN(int m)
{
	int i;
	for(i = 0; i<m; i++)
	{
		printf("%d ", i);
	}
	printf("\n0\n");
}

void printChildTree(Graph *G, int parent, int vertex)
{
	Vertex *v;
	for(v = G->adj[vertex]; v!= NULL; v = v->next)
	{
		printChildTree(G, vertex, v->vertex);	
	}
	printf("%d ", vertex);
}

void mLessThanN(Graph *G, int m, int n, int root)
{
	int *childs;
	Vertex *v;
	int falseRoot, parent;

	childs = malloc(G->V*sizeof(int));

	while(bla != )
	{
		for(v = G->adj[falseRoot]; v!= NULL && (childs[v->vertex] <= m || childs[v->vertex] == parent) ; v = v->next)
		{
			if (childs[v->vertex] > m/2.0)
			{
				printChildTree(G, falseRoot, v->vertex);
				printf("\n1\n");
				return 0;
			}
		}
		/* quando terminar, v será vertice com mais que m filhos*/
		if (v->vertex < G->V)
		{
			falseRoot = v->vertex;
		}
		else
		{
			for(v = G->adj[])
		}

	}
	printf("\n");
}

/*int childNumber(Graph *G, int vertex, int root)
{
	int childs = 0;
	Vertex *v;
	for(v = G->adj[vertex]; v!= NULL; v = v->next)
		childs ++;
	if (root == vertex)
		return childs;
	else
		return childs -1;
}*/

int childNumber(Graph *G, int root, int *childs, int parent)
{
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]; i!= NULL; i = i->next)
	{
		if (i->vertex != parent)
		{
			sum += childNumber(G, i->vertex, childs, root);
		}
	}
	childs[root] = ++sum;

	return sum;
}