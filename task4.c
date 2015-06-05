#include "common/doubleDiam.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int root, elementOfS, max;
	int *maxPath, *labelVec, *r, *index;
	Graph *G;
	G = read(argv[1]);
	setBInit(G);
	seed = 1;
	DEBUG = 0;
	Blength = 0;

	root = (int)(G->V*1.0*rand()/RAND_MAX); 

	if(argc>=4)
	{
		DEBUG = atoi(argv[3]);
		if(argc>=5)
			seed = atoi(argv[4]);
	}	
	
	/* r shows the root (according to index) */
	r = malloc(G->V*sizeof(int));

	maxPath = maximumPath(G);

	/* Label */
	max = changeOrderAtAdj(G, maxPath, r);
	labelVec = label(G, maxPath, max, r);

	index = labelToIndex(G, labelVec);

	elementOfS = doubleDiam(G, atoi(argv[2]), root, labelVec, 
		index, maxPath, r);

	printf("element Of S: %d\n", elementOfS);
	freeGraph(G);
	free(r);
	free(maxPath);
	free(index);
	free(labelVec);
	free(setB);
	
	return 0;
}