#include "common/maxPath-v1.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	Graph *G;
	int *maxPath;
	G = read(argv[1]);
	setBInit(G);
	DEBUG = 0;

	if(argc>=4)
	{
	  DEBUG = atoi(argv[3]);
	}
	
	maxPath = maximumPath(G, 0);
	free(maxPath);
	freeGraph(G);
	free(setB);

	return 0;
}
