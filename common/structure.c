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


void includeBridgeEdges(Graph *G, int vertex1, int vertex2)
{
	Vertex *newVertex1, *newVertex2;
	newVertex1 = malloc(sizeof(Vertex));
	newVertex2 = malloc(sizeof(Vertex));

	newVertex1->vertex = vertex1;
	newVertex2->vertex = vertex2;

	newVertex1->edge = 1;
	newVertex2->edge = 1;

	newVertex1->original = 1;
	newVertex2->original = 1;

	newVertex1->bridge = 1;
	newVertex2->bridge = 1;
    
    newVertex1->weight = 0;
	newVertex2->weight = 0;
	
	/*newVertex1->next = G->adj[vertex2];*/
	newVertex1->next = G->adj[vertex2]->next;

	G->adj[vertex2]->next = newVertex1; 

	newVertex2->next = G->adj[vertex1]->next;
	G->adj[vertex1]->next = newVertex2;
}


void includeEdges(Graph *G, int vertex1, int vertex2, float weight)
{
	Vertex *newVertex1, *newVertex2;
	newVertex1 = malloc(sizeof(Vertex));
	newVertex2 = malloc(sizeof(Vertex));

	newVertex1->vertex = vertex1;
	newVertex2->vertex = vertex2;

	newVertex1->edge = 1;
	newVertex2->edge = 1;

	newVertex1->original = 1;
	newVertex2->original = 1;

	newVertex1->bridge = 0;
	newVertex2->bridge = 0;
	
	newVertex1->weight = weight;
	newVertex2->weight = weight;

	/*newVertex1->next = G->adj[vertex2];*/
	newVertex1->next = G->adj[vertex2]->next;

	G->adj[vertex2]->next = newVertex1; 

	newVertex2->next = G->adj[vertex1]->next;
	G->adj[vertex1]->next = newVertex2;
}

void includeNotOriginalEdges(Graph *G, int vertex1, int vertex2)
{
	Vertex *newVertex1, *newVertex2;
	newVertex1 = malloc(sizeof(Vertex));
	newVertex2 = malloc(sizeof(Vertex));

	newVertex1->vertex = vertex1;
	newVertex2->vertex = vertex2;

	newVertex1->edge = 1;
	newVertex2->edge = 1;

	newVertex1->original = 0;
	newVertex2->original = 0;

	newVertex1->bridge = 0;
	newVertex2->bridge = 0;
	
	newVertex1->weight = 0;
	newVertex2->weight = 0;

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
			printf("%d %d    |    edge: %d    |   original: %d\n", i, aux->vertex, 
				aux->edge, aux->original);
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
void eraseEdge(Graph *G, int parent, int vertex)
/* Delete the edge that connect the childTree with the tree */
{	
	Vertex *v;
	for(v = G->adj[parent]; v->next!=NULL; v = v->next)
		if (v->next->vertex == vertex)
		{
			v->next->edge = 0;
			break;
		}

	for(v = G->adj[vertex]; v->next!=NULL; v = v->next)
		if(v->next->vertex == parent)
		{
			v->next->edge = 0;
			break;
		}
}


void setOriginal(Graph *G, int v1, int v2, int original)
{
	Vertex *v;
	for(v = G->adj[v1]->next; v!=NULL; v=v->next)
	{
		if(v->vertex == v2)
		{
			v->original = original;
			break;
		}
	}

	for(v = G->adj[v2]->next; v!=NULL; v=v->next)
	{
		if(v->vertex == v1)
		{
			v->original = original;
			break;
		}
	}
}
