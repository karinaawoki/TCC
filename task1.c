#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	Graph *G;
	int *maxPath;
	int r;
	G = read(argv[1]);
	r = (int)(G->V*1.0*rand()/RAND_MAX);
	maxPath = maximumPath(G, r);
	free(maxPath);
	freeGraph(G);

	return 0;
}