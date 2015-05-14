#include "lemma2.h" 
#include "list/queue.h"


int fartherVertex(Graph *G, int vertex, int *parents);
void printPath(int *parents, int init, int end, int *maxPath);



int *maximumPath(Graph *G, int r)
{
	/* The result will be a vector with 
	the maximum path - the number -1 indicate 
	the end of the path */
	int x0, y0, *parents, *maxPath;
	printf("%d -- r \n", r); 
	parents = malloc(G->V*sizeof(int));
	maxPath = malloc((1+G->V)*sizeof(int));

	x0 = fartherVertex(G, r, parents);
	y0 = fartherVertex(G, x0, parents);
	printPath(parents, x0, y0, maxPath);

	free(parents);
	return maxPath;
}

void printPath(int *parents, int init, int end, int *maxPath)
{
	int vertex, i = 1;

	printf("TASK 1 - The longest path in the tree is: \n");
	printf("%d  ", end);
	maxPath[0] = end;
	vertex = parents[end];
	while(vertex!=init)
	{
		printf("%d  ", vertex);
		maxPath[i] = vertex;
		vertex = parents[vertex];
		i ++;
	}
	printf("%d\n\n", init);
	maxPath[i] = init;
	maxPathLength = i+1;
	maxPath[i+1] = -1;

}

int fartherVertex(Graph *G, int vertex, int *parents)
{	/* QUEUE of vertex - farther at the end */
	Queue *q;
	int i,farther = -1;
	for(i = 0; i<G->V; i++)
	{
		parents[i] = -1;
	}

	q = initQueue(vertex);
	parents[vertex] = vertex;
	while(!emptyQueue(q))
	{
		Vertex *aux;
		for(aux = G->adj[q->init->num]->next; aux!=NULL; aux = aux->next)
		{
			if (parents[aux->vertex]==-1 && aux->edge==1)
			{
				insertQueue(q, aux->vertex);
				parents[aux->vertex] = q->init->num;
			}
		}
		farther = removeQueue(q);
	}
	freeQueue(q);

	return farther;
}