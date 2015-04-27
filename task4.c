#include "common/lemma3.h"

int *decideCases(Graph *G, int *maxPath, int*label, int m, int *r);
void case1(Graph *G, int firstVertexB, int m, int *B, int *index);
void case2(Graph *G, int m, int *B, int *index, int *maxPath, int *rLabel, int *label);
int *Pb(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPb);
int *Pf(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPf);
int treeLength(Graph *G, int root, int left, int right);
float *roNumber(Graph *G, int *label, int*maxPath, int*p, int *numP);
void bSpecialTree(Graph *G, int m, int *maxPath, int *B, int z, int *rLabel, int *label);
void fSpecialTree(Graph *G, int m, int *maxPath, int *B, int z, int *rLabel, int *label);



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
	r = 2;
	maxPath = maximumPath(G, r);
	max = changeOrderAtAdj(G, maxPath, root);
	vLabel = label(G, maxPath, max, root);
	B = decideCases(G, maxPath, vLabel, m, root);


	free(maxPath);
	/*printLabel(G, vLabel, root);*/
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
		if(DEBUG==1)
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
printf("caso1\n\n");

	for(i =firstVertexB; i!=(firstVertexB+m-1)%G->V; i = (i+1)%G->V)
	{
		printf("%d ", index[i]);
		B[(i-firstVertexB+G->V)%G->V] =  index[i];
	}
	printf("%d ", index[i]);
	B[(i-firstVertexB + G->V)%G->V] =  index[i];

	/* when B is at the border */
	if((firstVertexB-m+1)%G->V == 0 || firstVertexB == G->V-1)
		printf("\n%d\n", 1);
	else
		printf("\n%d\n", 2);
}

void case2(Graph *G, int m, int *B, int *index, int *maxPath, int *rLabel, int *label)
{
	/* maxPath[z] = vertex with minimum rô.. and bSpecial indicate if z is bSpecial or fSpecial 
	and zVal is the ro[z] (can be roB[z] or roF[z])*/

	int i, *pb, *pf, *numPf, *numPb, bSpecial, z;
	float *roB, *roF, zVal;

	zVal = -1;
	numPb = malloc(G->V*sizeof(int));
	numPf = malloc(G->V*sizeof(int));
	for (i = 0; i < G->V; ++i)
	{
		numPf[i] = 0;
		numPb[i] = 0;
	}
/*
	pb = Pb(G, maxPath, m, label, rLabel, index, numPb);
	roB = roNumber(G, label, maxPath, pb, numPb);
	free(pb);
	free(numPb);

	pf = Pf(G, maxPath, m, label, rLabel, index, numPf);
	roF = roNumber(G, label, maxPath, pf, numPf);
	free(pf);
	free(numPf);*/


	pf = Pf(G, maxPath, m, label, rLabel, index, numPf);
	roF = roNumber(G, label, maxPath, pf, numPf);

	pb = Pb(G, maxPath, m, label, rLabel, index, numPb);
	roB = roNumber(G, label, maxPath, pb, numPb);


	for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  rob: %f\n", maxPath[i], roB[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  rof: %f\n", maxPath[i], roF[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Pb: %d\n", maxPath[i], index[pb[label[maxPath[i]]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Pf: %d\n", maxPath[i], index[pf[label[maxPath[i]]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  numPb: %d\n", maxPath[i], numPb[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  numPf: %d\n", maxPath[i], numPf[label[maxPath[i]]]);
		printf("\n\n\n");


	for (i = 0; maxPath[i]!=-1; ++i)
	{
		/* takes the minimum rô */
		if (roB[label[maxPath[i]]]!=-1 && roB[label[maxPath[i]]] < roF[label[maxPath[i]]] &&
			(roB[label[maxPath[i]]] < zVal || zVal == -1))
		{
			z = i;
			zVal = roB[label[maxPath[i]]];
			bSpecial = 1;
		}
		else if (roF[label[maxPath[i]]]!=-1 && (roF[label[maxPath[i]]] < zVal || zVal == -1))
		{
			z = i;
			zVal = roF[label[maxPath[i]]];
			bSpecial = 0;
		}
	}

	free(roB);
	free(roF);

	printf(" %d \n", z);
	printf(" %d \n", bSpecial);
	printf(" %f \n", zVal);
	if(bSpecial==1)
		bSpecialTree(G, m, maxPath, B, z, rLabel, label);
	else
		fSpecialTree(G, m, maxPath, B, z, rLabel, label);
}

void bSpecialTree(Graph *G, int m, int *maxPath, int *B, int z, int *rLabel, int *label)
{	
	/* j is the vertex before z on C */
	int i, j, jSize = 0, mPrime;
	float cPrime, d;
	printf("b-special\n");

	j = (z-1+maxPathLength)%maxPathLength;

	for (i = j; 
		rLabel[(label[maxPath[i]]+m)%G->V]!=label[maxPath[z]]; 
		i = (i-1+maxPathLength)%maxPathLength)
	{
		jSize += treeLength(G, maxPath[i], 
				maxPath[(i-1 + maxPathLength)%maxPathLength], 
				maxPath[(i+1)%maxPathLength]);
	}
	
	
	d = maxPathLength*1.0/G->V;
	cPrime = 2-(1.0/(1-d));
	mPrime = m - jSize;
	printf("c %f \n", cPrime);
	printf("m %d \n", mPrime);
	deleteChildTree(G, maxPath[z], maxPath[(z+1)%maxPathLength]);
	deleteChildTree(G, maxPath[z], maxPath[(z-1+maxPathLength)%maxPathLength]);
	B = lemma3(G, mPrime, cPrime, maxPath[z]);
}


void fSpecialTree(Graph *G, int m, int *maxPath, int *B, int z, int *rLabel, int *label)
{
	/* j is the vertex before z on C */
	int i, j, jSize = 0, mPrime;
	float cPrime, d;
	
	printf("f-special\n");
	j = (z+1)%maxPathLength;

	for (i = j; 
		rLabel[(label[maxPath[i]]-m+G->V)%G->V]!=label[maxPath[z]]; 
		i = (i+1)%maxPathLength)
	{
		jSize += treeLength(G, maxPath[i], 
				maxPath[(i-1 + maxPathLength)%maxPathLength], 
				maxPath[(i+1)%maxPathLength]);
	}

	
	d = maxPathLength*1.0/G->V;
	cPrime = 2-(1.0/(1-d));
	mPrime = m - jSize;
	printf("c %f \n", cPrime);
	printf("m %d \n", mPrime);
	deleteChildTree(G, maxPath[z], maxPath[(z+1)%maxPathLength]);
	printf("%d - %d  %d\n", maxPath[(z-1+maxPathLength)%maxPathLength], 
		maxPath[z], maxPath[(z+1)%maxPathLength]);
	deleteChildTree(G, maxPath[z], maxPath[(z-1+maxPathLength)%maxPathLength]);
	B = lemma3(G, mPrime, cPrime, maxPath[z]);	 
}


int *Pb(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPb)
{
	/* label to label */
	int i, *p, rootLabel;
	p = malloc(G->V*sizeof(int));
	
	for(i = 0; i<G->V; i++)
		p[i] = -1;

	for(i = 0; maxPath[i]!=-1; i++)
	{
		rootLabel = rLabel[(label[maxPath[i]] + m)%G->V];
		p[label[maxPath[i]]] = rootLabel;
		numPb[rootLabel]++;
		if(DEBUG)
			printf("%d\n", p[label[maxPath[i]]]);
	}
	return p;
}

int *Pf(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPf)
{
	int i, *p, rootLabel;
	p = malloc(G->V*sizeof(int));

	for(i = 0; i<G->V; i++)
		p[i] = -1;

	/* For each vertex in C: take its label and map to back.. and take the root */
	for(i = 0; maxPath[i]!=-1; i++)
	{
		rootLabel = rLabel[(label[maxPath[i]] - m + G->V)%G->V];
		p[label[maxPath[i]]] = rootLabel;
		numPf[rootLabel]++;
		if(DEBUG == 1)
			printf("%d\n", p[label[maxPath[i]]]);
	}
	return p;
}

float *roNumber(Graph *G, int *label, int*maxPath, int*p, int *numP)
{
	/* This function calculate both the Hb and the Hf... what differs is the vector p
	    * if p == pf... the return will be Hf 
	    * if p == pb... the return will be Hb*/ 
	int *h, i, T;
	float *ro;
	h = malloc(G->V*sizeof(int));
	ro = malloc(G->V*sizeof(float));

	for (i = 0; i < G->V; ++i)
	{
		ro[i] = -1.0;
		h[i] = 0;
	}

	for (i = 0; maxPath[i]!=-1; ++i)
		if(p[label[maxPath[i]]] == p[label[maxPath[(i-1 + maxPathLength)%maxPathLength]]])
			h[p[label[maxPath[i]]]] += treeLength(G, maxPath[i], 
				maxPath[(i-1 + maxPathLength)%maxPathLength], maxPath[(i+1)%maxPathLength])-1;

	/* Calculate rô of each vertex at C  */

	for (i = 0; maxPath[i]!=-1; ++i)
	{
		if(numP[label[maxPath[i]]]>0)
		{
			T = treeLength(G, maxPath[i], maxPath[(i-1 + maxPathLength)%maxPathLength], 
				maxPath[(i+1)%maxPathLength])-1;
			ro[label[maxPath[i]]] = 1.0*(h[label[maxPath[i]]] + T)/numP[label[maxPath[i]]];
		}
	}
	free(h);
	return ro;
}


int treeLength(Graph *G, int root, int left, int right)
{
	/* This recursive function returns rhe number of descendant
	it is used to construct the descendant vector
	-- descendant number includes the own root */
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != left && i->vertex != right)
			sum += treeLength(G, i->vertex, root, -1);
	return ++sum;
}


/*void printDebug()
{
	if (DEBUG == 1)
	{
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Hb: %f\n", maxPath[i], hb[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Hf: %f\n", maxPath[i], hf[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Pb: %d\n", maxPath[i], pb[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  Pf: %d\n", maxPath[i], pf[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  numPb: %d\n", maxPath[i], numPb[label[maxPath[i]]]);
		printf("\n");
		for (i = 0; maxPath[i]!=-1; ++i)
			printf("%d -->  numPf: %d\n", maxPath[i], numPf[label[maxPath[i]]]);
		printf("\n\n\n");
	}
}*/