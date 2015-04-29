#include "common/theorem4.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B;
	Graph *G;
	G = read(argv[1]);
	B = malloc(G->V*sizeof(int));
	theorem4(G, B, atoi(argv[2]));

	return 0;
}


/* TODO: Fazer uma varredura na árvore e ir deletando as arestas de baixo para cima
- das raízes que não pertencem a P --  */