#include "common/theorem4.h"

void theorem6(Graph *G, int m);
void countEdgesAtCut(Graph *G, int ver, int parent);
int numCut;

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	Graph *G;
	Blength = 0;
	numCut = 0;

	G = read(argv[1]);
	if(G->V < atoi(argv[2]))
	{
		printf("m maior que o número de vértices!!\n");
		return 0;
	}
	setBInit(G);
	theorem6(G, atoi(argv[2]));

	freeGraph(G);
	return 0;
}


void theorem6(Graph *G, int m)
{
	int root, Ssize;
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 1; 

	Ssize = theorem4(G, m, root);
	while(Blength < m)
	{
		printf("kkkkk %d \n", Blength);
		if(Ssize<0)
			printf("ERROOOO\n");
		Ssize = theorem4(G, m-Blength, Ssize);
	}
	
	/*for(i = 0; i<G->V; i++)
	{
	if(setB[i] == 1)
	    printf("setB[%d] = %d\n", i, setB[i]);
	}
	printf("\n\n");
	for(i = 0; i<Blength; i++)
	{
	    printf("B[%d] = %d\n", i, B[i]);
	}*/
	
	countEdgesAtCut(G, 0, 0);
	printf("CORTE: %d\n", numCut);

}



void countEdgesAtCut(Graph *G, int ver, int parent)
{
    Vertex *v;
    for(v = G->adj[ver]->next; v!=NULL; v = v->next)
    {
        if(v->vertex!=parent && v->original==1)
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
