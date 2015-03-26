#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	Graph *G;
	int r;
	G = read(argv[1]);
	r = (int)(G->V*1.0*rand()/RAND_MAX);
	maximumPath(G, r);

	return 0;
}