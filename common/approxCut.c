#include "approxCut.h"

void Algorithm1(Graph *G, float c, int m, int root, int NumVert);


void approxCut(Graph *G, int m, float c, int root)
{
	int NumVert;

	int *childs;
	childs = malloc(G->V*sizeof(int));

	srand(seed);
	childNumber(G, root, childs, root);
	NumVert = childs[root];

	if(m ==  NumVert || m == 0 || c <= 0.5)
		printf("\n%d \n", simpleApproxCut(G, m, root, NumVert));
	else
		/* c >= m/2 */
		Algorithm1(G, c, m, root, NumVert);
	

	free(childs);

}

void Algorithm1(Graph *G, float c, int m, int root, int NumVert)
{
	int lenB = 0;
	int lenCut = 0, oldBLength = Blength;

	
	
	printf("root : %d\n", root);

	while(lenB < c*m)
	{
		lenCut += simpleApproxCut(G, m - lenB, root, NumVert);
		/* E se essa nova mini-árvore tiver um verice que 
		é pai de algum dos vertices do conjunto B anterior?
		Nesse caso, o corte seria menor do que o proposto acima!

		Porem isso não pode acontecer, pois o conjunto W se 
		mantem conexo o tempo todo, e sabemos que se não pegamos 
		o pai da raiz da mini arvore inclusa em B, é pq todo 
		aquele conjunto tem mais que m vertices.
		e como W sempre se mantem conexo, se pegarmos algum 
		pai do que já foi escolhido, o conjunto B terá mais que
		m elementos. */
		lenB = Blength - oldBLength;
		/*printf("\n");
		printf("lenB = %d\n", lenB);
		printf("lenCut = %d\n", lenCut);*/
	}

	printf("\n%d \n", lenCut);

}