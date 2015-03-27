#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	int numEdges;
	Graph *G;
	int root;
	srand(seed);
	
	G = read(argv[1]);
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 0;
	numEdges = lemma2(G, atoi(argv[2]), root);
	printf("\n%d \n", numEdges);
	return 0;
}