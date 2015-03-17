#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	int numEdges;

	Graph *G;
	G = read(argv[1]);
	numEdges = lemma2(G, atoi(argv[2]));
	printf("\n%d \n", numEdges);
	return 0;
}