#include "common/lemma3.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */
	Graph *G;
	int root;
	int m = atoi(argv[2]);
	float c = atof(argv[3]);

	G = read(argv[1]);
	setBInit(G);
	root = (int)(G->V*1.0*rand()/RAND_MAX);

	Blength = 0;
	
	lemma3(G, m, c, root);

	freeGraph(G);
	free(setB);
	
	return 0;
}

