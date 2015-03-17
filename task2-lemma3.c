#include "common/lemma2.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	/* argv[3] = c        */

	Graph *G;
	G = read(argv[1]);

	if(atoi(argv[2]) ==  G->V || atoi(argv[2]) == 0 || atof(argv[3]) <= 0.5)
	{
		lemma2(G, atoi(argv[2]));
	}
	else
	{
		/* c >= m/2 */
	}
	return 0;
}


void Algorithm1(Graph *G, float c, int m)
{
	/*int lenB = 0;
	while(lenB < c*m)
	{
		lemma2()
	}*/
}