#include <stdio.h>
#include <stdlib.h>

#define seed 0
#define DEBUG 0

typedef struct vertex Vertex;
struct vertex
{
	int vertex;
	Vertex *next;
};

typedef struct graph Graph;
struct graph
{
	int V;      /* Number of vertex */
	Vertex** adj;
};


void initGraph(Graph *G, int V);
void includeEdges(Graph *G, int vertex1, int vertex2);
void printGraph(Graph *G);
void freeGraph(Graph *G);
void deleteEdge(Graph *G, int parent, int vertex);
void setBInit(Graph *G);

int maxPathLength;
int *setB; /* Vetor binário (pertence ou não a B) */

int cut;
