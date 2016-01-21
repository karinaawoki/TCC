#include "approxCut.h"

void approxCut(Graph *G, int m, float c, int root, int leftNeighbor, int rightNeighbor)
/* Adaptation of Algorithm 3. 
   Input: subtree of G rooted at root, ignoring leftNeighbor and rightNeighbor
   Corresponding input of Algorithm 3: forest consisting of the subtrees of root.
 */
{
	int edgesCut = 0, oldBLength = Blength;
	int NumVert, *childs;
	childs = malloc(G->V*sizeof(int));

	if(STEP) printf("  Approximate cut \n"); 
	if(STEP) printf("    r: %d\n", root);
	if(STEP) printf("    m: %d\n", m);
	if(STEP) printf("    c: %f\n", c);

	descendantsNumber(G, root, childs, leftNeighbor, rightNeighbor);
	NumVert = childs[root];
	free(childs);

	if(STEP) printf("    size of the tree rooted at r: %d\n\n", NumVert);
	

	/*if(STEP) printf("    Algorithm 3 - root: %d\n", root);*/
	if(STEP) printf("      Initial size of B: %d\n", Blength);

	if(m == 0);
	else if (m == NumVert || c <= 0.5)
	{
		printf("    Number of edges cut: %d\n", Algorithm2(G, m, root, NumVert, leftNeighbor, rightNeighbor));
	}
	
	/* c > 1/2 */
	else
	{
		int sizeB = 0;
		while(sizeB < c*m)
		{
			if (DEBUG||STEP) printf("      Inside the loop of Algorithm 3.\n");
			edgesCut += Algorithm2(G, m - sizeB, root, NumVert, leftNeighbor, rightNeighbor);
			sizeB = Blength - oldBLength;
		}
	}
	if(STEP) printf("      Final size of B: %d\n", Blength);
	if(STEP) printf("    Algorithm 3 - number of edges cut: %d\n", edgesCut);
}
