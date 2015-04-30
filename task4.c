#include "common/theorem4.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B, root;
	Graph *G;
	G = read(argv[1]);

	root = (int)(G->V*1.0*rand()/RAND_MAX); 	
	B = malloc(G->V*sizeof(int));

	/* TODO: take off */
	root = 0;

	theorem4(G, B, atoi(argv[2]), root);

	return 0;
}


/* TODO: Fazer uma varredura na árvore e ir deletando as arestas de baixo para cima
- das raízes que não pertencem a P --  */