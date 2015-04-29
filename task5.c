#include "common/theorem4.h"

void theorem6(Graph *G, int *B, int m);


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B;
	Graph *G;
	G = read(argv[1]);
	B = malloc(G->V*sizeof(int));
	theorem6(G, B, atoi(argv[2]));

	return 0;
}


void theorem6(Graph *G, int *B, int m)
{
	while(Blength < m)
	{
		theorem4(G, B, m);
	}
}