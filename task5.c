#include "common/theorem4.h"

void theorem6(Graph *G, int *B, int m);
void countEdgesAtCut(Graph *G, int ver, int parent);
int numCut;

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B;
	Graph *G;
	Blength = 0;
	cut = 0;
	numCut = 0;

	G = read(argv[1]);
	setBInit(G);
	B = malloc(G->V*sizeof(int));
	theorem6(G, B, atoi(argv[2]));

	free(B);
	freeGraph(G);
	return 0;
}


void theorem6(Graph *G, int *B, int m)
{
	int root, Ssize, i;
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 1; 

	Ssize = theorem4(G, B, m, root);
	while(Blength < m)
	{
		printf("HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEY\n");
		if(Ssize<0)
			printf("ERROOOO\n");
		Ssize = theorem4(G, B, m-Blength, Ssize);
	}
	
	for(i = 0; i<G->V; i++)
	{
	if(setB[i] == 1)
	    printf("setB[%d] = %d\n", i, setB[i]);
	}
	printf("\n\n");
	for(i = 0; i<Blength; i++)
	{
	    printf("B[%d] = %d\n", i, B[i]);
	}
	
	countEdgesAtCut(G, 0, 0);
	printf("CORTE: %d", numCut);
}



void countEdgesAtCut(Graph *G, int ver, int parent)
{
    Vertex *v;
    for(v = G->adj[ver]->next; v!=NULL; v = v->next)
    {
        if(v->vertex!=parent)
        {
        	if(setB[ver]!=setB[v->vertex])
        	{
        		printf("%d -- %d\n", ver, v->vertex);
            	numCut++;
        	}
            countEdgesAtCut(G, v->vertex, ver);
        }   
    }
}
