#include "common/simpleApproxCut.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	int numEdges;
	Graph *G;
	int root;
	srand(seed);
	Blength = 0;
	seed = 1;
	DEBUG = 0;

	G = read(argv[1]);
	setBInit(G);
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 6; /**/

	if(argc>=4)
	{
		DEBUG = atoi(argv[3]);
		if(argc>=5)
			seed = atoi(argv[4]);
	}
	
	numEdges = simpleApproxCut(G, atoi(argv[2]), root, G->V, -1, -1);
	printf("\n%d \n", numEdges);

	freeGraph(G);
	free(setB);
	return 0;
}
