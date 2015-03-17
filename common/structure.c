#include "structure.h"

void initGraph(Graph *G, int V)
{
	int i;
	/*G = malloc(sizeof(Graph));*/
	G->V = V;
	G->adj = malloc(G->V*sizeof(Vertex*));
	for(i = 0; i<G->V; i++)
	{
		G->adj[i] = malloc(sizeof(Vertex));
		G->adj[i]->next = NULL;
	}
}

void includeEdges(Graph *G, int vertex1, int vertex2)
{
	Vertex *newVertex1, *newVertex2;
	newVertex1 = malloc(sizeof(Vertex));
	newVertex2 = malloc(sizeof(Vertex));

	newVertex1->vertex = vertex1;
	newVertex2->vertex = vertex2;

	/*newVertex1->next = G->adj[vertex2];*/
	newVertex1->next = G->adj[vertex2]->next;

	G->adj[vertex2]->next = newVertex1; 

	newVertex2->next = G->adj[vertex1]->next;
	G->adj[vertex1]->next = newVertex2;
}

void printGraph(Graph *G)
{
	int i;
	Vertex *aux;
	printf("GRAPH: \n");
	for(i = 0; i<G->V; i++)
	{
		aux = G->adj[i]->next;
		while(aux!=NULL)
		{
			printf("%d %d\n", i, aux->vertex);
			aux = aux->next;
		}
	}
	printf("---------------\n\n\n");
}