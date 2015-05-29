#include "common/simpleApproxCut.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	Graph *G;
	int *maxPath;
	int r;
	G = read(argv[1]);
	setBInit(G);
	seed = 1;
	DEBUG = 0;

	r = (int)(G->V*1.0*rand()/RAND_MAX);

	if(argc>=4)
	{
		DEBUG = atoi(argv[3]);
		if(argc>=5)
			seed = atoi(argv[4]);
	}
	
	maxPath = maximumPath(G, r);
	free(maxPath);
	freeGraph(G);
	free(setB);

	return 0;
}
