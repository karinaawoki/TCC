#include "common/lemma3.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */
	Graph *G;
	int *B;
	int m = atoi(argv[2]);
	float c = atof(argv[3]);
	
	G = read(argv[1]);
	B = lemma3(G, m, c);

	free(B);
	freeGraph(G);
	
	return 0;
}

