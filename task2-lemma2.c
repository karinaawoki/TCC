#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	int numEdges, *B;
	Graph *G;
	int root;
	srand(seed);
	Blength = 0;
	cut = 0;
	G = read(argv[1]);
	setBInit(G);
	B = malloc(G->V*sizeof(int));
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 6; /**/
	numEdges = lemma2(G, atoi(argv[2]), root, B, G->V);
	printf("\n%d \n", numEdges);

	free(B);
	freeGraph(G);
	free(setB);
	return 0;
}
