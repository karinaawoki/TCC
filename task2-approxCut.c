#include "common/approxCut.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */
	Graph *G;
	int root;
	int m = atoi(argv[2]);
	float c = atof(argv[3]);
	seed = 1;
	DEBUG = 0;

	G = read(argv[1]);
	setBInit(G);
	root = (int)(G->V*1.0*rand()/RAND_MAX);

	Blength = 0;
	
	if(argc>=4)
	{
		DEBUG = atoi(argv[3]);
		if(argc>=5)
			seed = atoi(argv[4]);
	}
	
	approxCut(G, m, c, root);

	freeGraph(G);
	free(setB);
	
	return 0;
}

