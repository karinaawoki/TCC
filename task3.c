#include "common/label.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */

	int *maxPath, *vLabel, max, *root;
	Graph *G;
	int r;
	G = read(argv[1]);
	setBInit(G);
	root = malloc(G->V*sizeof(int));

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
