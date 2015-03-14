#include "input.h"
#include "list/queue.h"

int fartherVertex(Graph *G, int vertex, int *parents);
void printPath(int *parents, int init, int end);

int main(int argc, char *argv[])
{
	Graph *G;
	int x0, y0, r, *parents;
	G = read(argv[1]);
	srand(seed);

	r = (int)(G->V*1.0*rand()/RAND_MAX);
	printf("%d -- r \n", r);
	parents = malloc(G->V*sizeof(int));
	x0 = fartherVertex(G, r, parents);
	y0 = fartherVertex(G, x0, parents);
	printPath(parents, x0, y0);

	return 0;
}

void printPath(int *parents, int init, int end)
{
	int vertex;
	printf("TASK 1 - The longest path in the tree is: \n");
	printf("%d  ", end);
	vertex = parents[end];
	while(vertex!=init)
	{
		printf("%d  ", vertex);

		vertex = parents[vertex];
	}
	printf("%d\n\n", init);
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
		for(aux = G->adj[q->init->num]; aux!=NULL; aux = aux->next)
		{
			if (parents[aux->vertex]==-1)
			{
				insertQueue(q, aux->vertex);
				parents[aux->vertex] = q->init->num;
			}
		}
		farther = removeQueue(q);
	}

	return farther;
}