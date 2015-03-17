#include "common/lemma2.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */

	Graph *G;
	int m = atoi(argv[2]);
	float c = atof(argv[3]);
	G = read(argv[1]);

	if(m ==  G->V || m == 0 || c <= 0.5)
		printf("\n%d \n", lemma2(G, m));
	/*else*/
		/* c >= m/2 */
		/*Algorithm1(G, c, m);*/
	return 0;
}


/*void Algorithm1(Graph *G, float c, int m)
{
	int lenB = 0;
	while(lenB < c*m)
	{
		lemma2(G, m);
	}
}*/