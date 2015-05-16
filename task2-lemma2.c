#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	int numEdges;
	Graph *G;
	int root;
	srand(seed);
	Blength = 0;
	G = read(argv[1]);
	setBInit(G);
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 6; /**/
	numEdges = lemma2(G, atoi(argv[2]), root, G->V);
	printf("\n%d \n", numEdges);

	freeGraph(G);
	free(setB);
	return 0;
}
