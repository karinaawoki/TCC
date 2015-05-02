#include "lemma3.h"

void Algorithm1(Graph *G, float c, int m, int root, int *B);


void lemma3(Graph *G, int m, float c, int root, int *B)
{
	srand(seed);
	/*TODO: is not countLabel*/
	if(m ==  countLabel || m == 0 || c <= 0.5)
		printf("\n%d \n", lemma2(G, m, root, B));
	else
		/* c >= m/2 */
		Algorithm1(G, c, m, root, B);
}

void Algorithm1(Graph *G, float c, int m, int root, int *B)
{
	int lenB = 0;
	int lenCut = 0;

	int *childs;
	childs = malloc(G->V*sizeof(int));
	
	printf("root : %d\n", root);

	while(lenB < c*m)
	{
		lenCut += lemma2(G, m - lenB, root, B);
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
		
		childNumber(G, root, childs, root);

		/*TODO: is not countLabel*/
		lenB = countLabel - childs[root];
		/*printf("\n");
		printf("lenB = %d\n", lenB);
		printf("lenCut = %d\n", lenCut);*/
	}

	free(childs);
	printf("\n%d \n", lenCut);

}