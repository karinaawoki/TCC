#include "structure.h"

void initGraph(Graph *G, int V)
{
	/* WITH HEAD */
	int i;
	G->V = V;
	G->adj = malloc(G->V*sizeof(Vertex*));
	for(i = 0; i<G->V; i++)
	{
		G->adj[i] = malloc(sizeof(Vertex));
		G->adj[i]->next = NULL;
	}
}


void setBInit(Graph *G)
{
    int i;
    setB = malloc(G->V*sizeof(int));
    for(i = 0; i<G->V; i++)
    {
        setB[i] = 0;
    }
}


void freeGraph(Graph *G)
{
	int i = 0;
	for(i = 0; i< G->V; i++)
	{
		while(G->adj[i]->next!=NULL)
		{
			Vertex *rem = G->adj[i]->next;
			G->adj[i]->next = rem->next;
			free(rem);
		}
		free(G->adj[i]);
	}
	free(G->adj); 
	free(G);
}

void includeEdges(Graph *G, int vertex1, int vertex2)
{
	Vertex *newVertex1, *newVertex2;
	newVertex1 = malloc(sizeof(Vertex));
	newVertex2 = malloc(sizeof(Vertex));

	newVertex1->vertex = vertex1;
	newVertex2->vertex = vertex2;

	newVertex1->edge = 1;
	newVertex2->edge = 1;

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


void deleteEdge(Graph *G, int parent, int vertex)
/* Delete the edge that connect the childTree with the tree */
{	
	Vertex *v;
	for(v = G->adj[parent]; v->next!=NULL; v = v->next)
		if (v->next->vertex == vertex)
		{
			v->next->edge = 0;
			/*Vertex *rem;
			rem = v->next;
			v->next = rem->next;
			free(rem);*/
			break;
		}

	for(v = G->adj[vertex]; v->next!=NULL; v = v->next)
		if(v->next->vertex == parent)
		{
			v->next->edge = 0;
			/*Vertex *rem;
			rem = v->next;
			v->next = rem->next;
			free(rem);*/
			break;
		}
}
