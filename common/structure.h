#include <stdio.h>
#include <stdlib.h>

#define seed 0
#define DEBUG 0

typedef struct vertex Vertex;
struct vertex
{
	int vertex;
	Vertex *next;
	int edge; /*0: false   1:true*/
	int original; /*0:not-original   1:original */
};

typedef struct graph Graph;
struct graph
{
	int V;      /* Number of vertex */
	Vertex** adj;
};


void initGraph(Graph *G, int V);
void includeEdges(Graph *G, int vertex1, int vertex2);
void includeNotOriginalEdges(Graph *G, int vertex1, int vertex2);

void printGraph(Graph *G);
void freeGraph(Graph *G);
void deleteEdge(Graph *G, int parent, int vertex);
void setBInit(Graph *G);
void eraseEdge(Graph *G, int parent, int vertex);
void setOriginal(Graph *G, int v1, int v2, int original);


int maxPathLength;
int *setB; /* Vetor binário (pertence ou não a B) */

int maxPathInit;
int maxPathEnd;