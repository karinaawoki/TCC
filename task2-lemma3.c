#include "root.h"

void Algorithm1(Graph *G, float c, int m, int root);


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */

	Graph *G;
	int m = atoi(argv[2]);
	float c = atof(argv[3]);
	int root;
	G = read(argv[1]);
	srand(seed);
	
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 0;
	if(m ==  G->V || m == 0 || c <= 0.5)
		printf("\n%d \n", lemma2(G, m, root));
	else
		/* c >= m/2 */
		Algorithm1(G, c, m, root);
	return 0;
}


void Algorithm1(Graph *G, float c, int m, int root)
{
	int lenB = 0;
	int lenCut = 0;

	int *childs;
	childs = malloc(G->V*sizeof(int));
	
	printf("root : %d\n", root);

	while(lenB < c*m)
	{
		lenCut += lemma2(G, m - lenB, root);
		/* E se essa nova mini-árvore tiver um verice que é pai de algum dos vertices do conjunto B anterior?
		Nesse caso, o corte seria menor do que o proposto acima!

		Porem isso não pode acontecer, pois o conjunto W se mantem conexo o tempo todo, e sabemos que se não pegamos 
		o pai da raiz da mini arvore inclusa em B, é pq todo aquele conjunto tem mais que m vertices.
		e como W sempre se mantem conexo, se pegarmos algum pai do que já foi escolhido, o conjunto B terá mais que
		m elementos. */
		
		childNumber(G, root, childs, root);
		lenB = G->V - childs[root];
		/*printf("\n");
		printf("lenB = %d\n", lenB);
		printf("lenCut = %d\n", lenCut);*/
	}
	printf("\n%d \n", lenCut);

}