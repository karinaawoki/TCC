#include "common/label.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */

	int *maxPath, *vLabel, max, *root;
	Graph *G;
	int r;
	seed = 1;
	DEBUG = 0;
	G = read(argv[1]);
	setBInit(G);
	root = malloc(G->V*sizeof(int));

	if(argc>=4)
	{
		DEBUG = atoi(argv[3]);
		if(argc>=5)
			seed = atoi(argv[4]);
	}

	r = (int)(G->V*1.0*rand()/RAND_MAX);
	maxPath = maximumPath(G, r);
	max = changeOrderAtAdj(G, maxPath, root);
	vLabel = label(G, maxPath, max, root);

	free(maxPath);
	printLabel(G, vLabel, root);
	free(root);
	free(vLabel);
	freeGraph(G);
	free(setB);
	
	return 0;
}
