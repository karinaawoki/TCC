#include "common/theorem4.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int root, S;
	Graph *G;
	G = read(argv[1]);
	setBInit(G);
	Blength = 0;

	root = (int)(G->V*1.0*rand()/RAND_MAX); 	

	/* TODO: take off */
	root = 21;

	S = theorem4(G, atoi(argv[2]), root);

	printf("///////--- %d\n", S);
	freeGraph(G);
	free(setB);
	
	return 0;
}


/* TODO: Fazer uma varredura na árvore e ir deletando as arestas de baixo para cima
- das raízes que não pertencem a P --  */
