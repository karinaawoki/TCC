#include "common/theorem4.h"

void theorem6(Graph *G, int *B, int m);


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B;
	Graph *G;
	Blength = 0;
	cut = 0;

	G = read(argv[1]);
	B = malloc(G->V*sizeof(int));
	theorem6(G, B, atoi(argv[2]));

	free(B);
	freeGraph(G);
	return 0;
}


void theorem6(Graph *G, int *B, int m)
{
	int root, S;
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 1; 

	S = theorem4(G, B, m, root);
	while(Blength < m)
	{
		printf("HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEY\n");
		if(S<0)
			printf("ERROOOO\n");
		S = theorem4(G, B, m-Blength, S);
	}
	printf("oiee\n");
}