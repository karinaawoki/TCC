#include "common/theorem4.h"


int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int root, S, max;
	int *maxPath, *labelVec, *r, *index;
	Graph *G;
	G = read(argv[1]);
	setBInit(G);
	Blength = 0;

	root = (int)(G->V*1.0*rand()/RAND_MAX); 	
	
	r = malloc(G->V*sizeof(int));
	maxPath = maximumPath(G, root);


	/* Label */
	max = changeOrderAtAdj(G, maxPath, r);
	labelVec = label(G, maxPath, max, r);

	index = labelToIndex(G, labelVec);

	S = theorem4(G, atoi(argv[2]), root, labelVec, 
		index, maxPath, r);

	printf("///////--- %d\n", S);
	freeGraph(G);
	free(r);
	free(maxPath);
	free(index);
	free(labelVec);
	free(setB);
	
	return 0;
}