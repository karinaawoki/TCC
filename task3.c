#include "common/lemma2.h"


int changeOrderAtAdj(Graph *G, int *maxPath);
int *label(Graph *G, int *maxPath, int max);
void depthFirst(Graph *G, int vertex, int parent, int *vertLabel);
void printLabel(Graph *G, int *vLabel);

int count;

int main(int argc, char *argv[])
{
	/* argv[1] = filename */

	int *maxPath, *vLabel, max;
	Graph *G;
	int r;
	G = read(argv[1]);
	r = (int)(G->V*1.0*rand()/RAND_MAX);
	maxPath = maximumPath(G, r);
	max = changeOrderAtAdj(G, maxPath);
	vLabel = label(G, maxPath, max);
	free(maxPath);
	printLabel(G, vLabel);
	free(vLabel);
	freeGraph(G);
	return 0;
}


void printLabel(Graph *G, int *vLabel)
{
	int i;
	for (i = 0; i < G->V; ++i)
	{
		printf("vertice %d : label %d\n", i, vLabel[i]);
	}
}


int changeOrderAtAdj(Graph *G, int *maxPath)
/* Returns the last sub-tree root */
{
	int i;
	Vertex *v;

	for(i = 1; maxPath[i] != -1; i++)
		for (v = G->adj[maxPath[i]]; v->next != NULL; v = v->next)
		{
			if(maxPath[i-1] == v->next->vertex)
			{
				Vertex *move;
				move = v->next;
				v->next = move->next;
				move->next = G->adj[maxPath[i]]->next;
				G->adj[maxPath[i]]->next = move;
				break;
			}
		}
	return maxPath[i-1];
}

int *label(Graph *G, int *maxPath, int max)
{
	int *vertLabel;
	vertLabel = malloc(G->V*sizeof(int));

	count = 0;
	depthFirst(G, max, max, vertLabel);
	return vertLabel;
}

void depthFirst(Graph *G, int vertex, int parent, int *vertLabel)
{
	Vertex *v;
	for(v = G->adj[vertex]->next; v!=NULL; v = v->next)
	{
		if(v->vertex!=parent)
			depthFirst(G, v->vertex, vertex, vertLabel);
	}
	vertLabel[vertex] = count ++;
} 