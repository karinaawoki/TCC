#include "common/label.h"

int *decideCases(Graph *G, int *maxPath, int*label, int m, int *r);
void case1(Graph *G, int firstVertexB, int m, int *B, int *index);
void case2(Graph *G, int m, int *B, int *index, int *maxPath, int *rLabel, int *label);



int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	int *maxPath, *vLabel, max, *root, *B;
	Graph *G;
	int r, m;
	G = read(argv[1]);
	root = malloc(G->V*sizeof(int));

	m = atoi(argv[2]);
	r = (int)(G->V*1.0*rand()/RAND_MAX);

	maxPath = maximumPath(G, r);
	max = changeOrderAtAdj(G, maxPath, root);
	vLabel = label(G, maxPath, max, root);
	B = decideCases(G, maxPath, vLabel, m, root);


	free(maxPath);
	printLabel(G, vLabel, root);
	free(B);
	free(root);
	free(vLabel);
	freeGraph(G);
	return 0;
}


int *decideCases(Graph *G, int *maxPath, int*label, int m, int *r)
{
	/* Returntest the vector of the set B */
	int plusM, i;
	int *index, *B, *rLabel;

	B = malloc(G->V*sizeof(int));
	index = labelToIndex(G, label);
	rLabel = indexRbyLabel(G, r, label);

	for(i = 0; maxPath[i]!=-1; i++)
	{
		plusM = (label[maxPath[i]] + m)%G->V;
		if(DEBUG)
			printf("índice de um vertice Nm(root)%d\n", index[plusM]);
		/* the next vertex must belong to another vertex */
		if(rLabel[plusM] != rLabel[(plusM+1)%G->V])
		{
			case1(G, label[maxPath[i]]+1, m, B, index);
			free(rLabel);
			free(index);
			return B;
		}
	}
	case2(G, m, B, index, maxPath, rLabel, label);
	free(rLabel);
	free(index);
	return B;
}

void case1(Graph *G, int firstVertexB, int m, int *B, int *index)
{
	int i;
	/* B is all the vertex with label between firstVertexB and
	firstVertexB -m */
	for(i =firstVertexB; i!=(firstVertexB+m-1)%G->V; i = (i+1)%G->V)
	{
		printf("%d ", index[i]);
		B[(i-firstVertexB+G->V)%G->V] =  index[i];
	}
	printf("%d ", index[i]);
	B[(i-firstVertexB+m-1)%G->V] =  index[i];

	/* when B is at the border */
	if((firstVertexB-m+1)%G->V == 0 || firstVertexB == G->V-1)
		printf("\n%d\n", 1);
	else
		printf("\n%d\n", 2);
}

void case2(Graph *G, int m, int *B, int *index, int *maxPath, int *rLabel, int *label)
{
	int i, plusM;
	/*int *Pz;*/
	
	for(i = 0; maxPath[i]!=-1; i++)
	{
		plusM = (label[maxPath[i]] + m)%G->V;
		printf("%d\n", plusM);
	}
}