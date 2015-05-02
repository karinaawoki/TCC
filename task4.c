#include "common/theorem4.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *B, root, S;
	Graph *G;
	G = read(argv[1]);
	cut = 0;
	Blength = 0;

	root = (int)(G->V*1.0*rand()/RAND_MAX); 	
	B = malloc(G->V*sizeof(int));

	/* TODO: take off */
	root = 21;

	S = theorem4(G, B, atoi(argv[2]), root);

	printf("///////--- %d\n", S);
	free(B);
	freeGraph(G);
	return 0;
}


/* TODO: Fazer uma varredura na árvore e ir deletando as arestas de baixo para cima
- das raízes que não pertencem a P --  */