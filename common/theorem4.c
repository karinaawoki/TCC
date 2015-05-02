#include "theorem4.h"

int decideCases(Graph *G, int *maxPath, int*label, int m, int *r, int *B);
void case1(Graph *G, int firstVertexB, int m, int *index, int *B);
int case2(Graph *G, int m, int *index, int *maxPath, int *rLabel, int *label, int *B);
int *Pb(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPb);
int *Pf(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index, int *numPf);
int treeLength(Graph *G, int root, int left, int right);
int treeLengthB(Graph *G, int root, int left, int right, int *B);
float *roNumber(Graph *G, int *label, int*maxPath, int*p, int *numP);
int bSpecialTree(Graph *G, int m, int *maxPath, int z, int *rLabel, int *label, int *B);
int fSpecialTree(Graph *G, int m, int *maxPath, int z, int *rLabel, int *label, int *B);
void printB(int *B);
void deleteAllNeighborBut(Graph *G, int vertex, int keep);
int separateSBSpecial(Graph *G, int z, int *label, int *vLabel, int *maxPath, int m);
int separateSFSpecial(Graph *G, int z, int *label, int *vLabel, int *maxPath, int m);
int nextMaxPath(int vertex);
int previousMaxPath(int vertex);



/* root[i] = j    -   i and j  by index */
/* rLabel[i] = j  -   i and j  by label */

int theorem4(Graph *G, int *B, int m, int root)
{
	/* Return an element of S */
	/* argv[1] = filename */
	/* argv[2] = m        */

	int S;
	int *maxPath, *vLabel, max, *r;
	r = malloc(G->V*sizeof(int));
	
	maxPath = maximumPath(G, root);
	
	/* Labeling */
	max = changeOrderAtAdj(G, maxPath, r);
	vLabel = label(G, maxPath, max, r);

	S = decideCases(G, maxPath, vLabel, m, r, B);


	free(maxPath);
	/*printLabel(G, vLabel, root);*/
	free(r);
	free(vLabel);

	return S;
}


int decideCases(Graph *G, int *maxPath, int*label, int m, int *r, int *B)
{
	/* Returntest the vector of the set B */
	int plusM, i, S;
	int *index, *rLabel;

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
			case1(G, label[maxPath[i]]+1, m, index, B);
			free(rLabel);
			free(index);
			return -1;
		}
	}
	S =  case2(G, m, index, maxPath, rLabel, label, B);
	free(rLabel);
	free(index);
	return S;
}

void case1(Graph *G, int firstVertexB, int m, int *index, int *B)
{
	int i;
	/* B is all the vertex with label between firstVertexB and
	firstVertexB -m */
	printf("caso1\n\n");
	for(i =firstVertexB; i!=(firstVertexB+m-1)%G->V; i = (i+1)%G->V)
	{
		printf("%d ", index[i]);
		B[Blength++] =  index[i];
	}
	printf("%d ", index[i]);
	B[Blength++] =  index[i];

	/* when B is at the border */
	if((firstVertexB-m+1)%G->V == 0 || firstVertexB == G->V-1)
		printf("\n%d\n", 1);
	else
		printf("\n%d\n", 2);

	printB(B);
}

int case2(Graph *G, int m, int *index, int *maxPath, int *rLabel, int *label, int *B)
{
	/* maxPath[z] = vertex with minimum rô.. and bSpecial indicate if 
	z is bSpecial or fSpecial 
	and zVal is the ro[z] (can be roB[z] or roF[z])*/

	int i, *pb, *pf, *numPf, *numPb, bSpecial, z, S;
	float *roB, *roF, zVal;

	zVal = -1;
	numPb = malloc(G->V*sizeof(int));
	numPf = malloc(G->V*sizeof(int));
	for (i = 0; i < G->V; ++i)
	{
		numPf[i] = 0;
		numPb[i] = 0;
	}

	pb = Pb(G, maxPath, m, label, rLabel, index, numPb);
	roB = roNumber(G, label, maxPath, pb, numPb);

	pf = Pf(G, maxPath, m, label, rLabel, index, numPf);
	roF = roNumber(G, label, maxPath, pf, numPf);

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
	free(numPb);

	free(numPf);

	for (i = 0; maxPath[i]!=-1; ++i)
	{
		/* takes the minimum rô */
		if (roB[label[maxPath[i]]]!=-1 && 
			roB[label[maxPath[i]]] < roF[label[maxPath[i]]] &&
			(roB[label[maxPath[i]]] < zVal || zVal == -1))
		{
			z = i;
			zVal = roB[label[maxPath[i]]];
			bSpecial = 1;
		}
		else if (roF[label[maxPath[i]]]!=-1 && 
			(roF[label[maxPath[i]]] < zVal || zVal == -1))
		{
			z = i;
			zVal = roF[label[maxPath[i]]];
			bSpecial = 0;
		}
	}

	free(roB);
	free(roF);

	printf(" %d \n", maxPath[z]);
	printf(" %d \n", bSpecial);
	printf(" %f \n", zVal);
	if(bSpecial==1)
		S = bSpecialTree(G, m, maxPath, z, rLabel, label, B);
	else
		S = fSpecialTree(G, m, maxPath, z, rLabel, label, B);

	printB(B);
	free(pf);
	free(pb);
	return S;
}


int bSpecialTree(Graph *G, int m, int *maxPath, int z, int *rLabel, int *label, int *B)
{	
	/* j is the vertex before z on C */
	int i, j, jSize = 0, mPrime, S;
	float cPrime, d;

	printf("b-special\n");

	j = previousMaxPath(z);

	for (i = j; 
		rLabel[(label[maxPath[i]]+m)%G->V]!=label[maxPath[z]]; 
		i = previousMaxPath(i))
	{
		jSize += treeLengthB(G, maxPath[i], 
				maxPath[previousMaxPath(i)], 
				maxPath[nextMaxPath(i)], B);

	}
	
	
	d = maxPathLength*1.0/G->V;
	cPrime = 2-(1.0/(1-d));
	mPrime = m - jSize;
	printf("c %f \n", cPrime);
	printf("m %d \n", mPrime);
	/* Separate B */


	deleteEdge(G, maxPath[z], maxPath[nextMaxPath(z)]);
	deleteEdge(G, maxPath[z], maxPath[previousMaxPath(z)]);
	
	lemma3(G, mPrime, cPrime, maxPath[z], B);
	S = separateSBSpecial(G, z, label, rLabel, maxPath, m);
	return S;
}


int separateSBSpecial(Graph *G, int z, int *label, int *rLabel, int *maxPath, int m)
{
	/* Return an element of S */
	/* Delete all edges, but  */
	int S;
	int aux = previousMaxPath(z), divided = 0;
	printf("z %d \n", maxPath[z]);
	/* We jump the tree between z and TPz */
	while(rLabel[(label[maxPath[aux]] + m)%G->V] != label[maxPath[z]])
		aux = previousMaxPath(aux);


	S = maxPath[aux];
	printf("aux %d\n", maxPath[aux]);
	deleteEdge(G, maxPath[nextMaxPath(aux)], maxPath[aux]);


	while(rLabel[(label[maxPath[aux]] + m)%G->V] == label[maxPath[z]])
	{
		if(aux == 0)
			divided = 1;
		else if(aux == maxPathLength-1 && divided == 1)
			includeEdges(G, maxPath[0], maxPath[maxPathLength-1]);
		aux = previousMaxPath(aux);
	}
	aux = nextMaxPath(aux);

	deleteAllNeighborBut(G, maxPath[aux], maxPath[nextMaxPath(aux)]);
	return S;
}

int separateSFSpecial(Graph *G, int z, int *label, int *rLabel, int *maxPath, int m)
{
	/* Return an element of S */
	/* Delete all edges, but  */
	int S;
	int aux = nextMaxPath(z), divided = 0;

	while( rLabel[(label[maxPath[aux]]-m+G->V)%G->V] != label[maxPath[z]])
	{
		aux = nextMaxPath(aux);
	}
	S = maxPath[aux];
	deleteAllNeighborBut(G, maxPath[aux], maxPath[nextMaxPath(aux)]);
	while(rLabel[(label[maxPath[aux]] - m + G->V)%G->V] == label[maxPath[z]])
	{
		if(aux == maxPathLength-1)
			divided = 1;
		else if(aux == 0 && divided == 1)
			includeEdges(G, maxPath[0], maxPath[maxPathLength-1]);
		aux = nextMaxPath(aux);
	}
	deleteEdge(G, maxPath[previousMaxPath(aux)], maxPath[aux]);

	return S;
}

int nextMaxPath(int vertex)
{
	return (vertex + 1) %maxPathLength;
}

int previousMaxPath(int vertex)
{
	return (vertex - 1 + maxPathLength)%maxPathLength;
}


void deleteAllNeighborBut(Graph *G, int vertex, int keep)
{
	Vertex *v, *keepAux;
	keepAux = NULL;
	for (v = G->adj[vertex]; v->next!=NULL; )
	{
	  	if(v->next->vertex != keep)
		{
			deleteEdge(G, vertex, v->next->vertex);
		}
		else
		{
			keepAux = v->next;
			v->next = keepAux->next;
			keepAux->next = NULL;
		}
	}
	v->next = keepAux;
}

int fSpecialTree(Graph *G, int m, int *maxPath, int z, int *rLabel, int *label, int *B)
{
	/* j is the vertex before z on C */
	int i, j, jSize = 0, mPrime, S;
	float cPrime, d;
	Vertex *v;
	
	printf("f-special\n");
	j = nextMaxPath(z);

	if(rLabel[(label[maxPath[z]]-m+G->V)%G->V]==label[maxPath[z]] )
	{ /* If z is the first element of P */
		j = z;
	}

	for (i = j; 
		rLabel[(label[maxPath[i]]-m+G->V)%G->V]!=label[maxPath[z]]; 
		i = nextMaxPath(i))
	{
		jSize += treeLengthB(G, maxPath[i], maxPath[previousMaxPath(i)], 
			maxPath[nextMaxPath(i)], B);
	}

	/* maxPath[i] is zf now */
	/* We have to add all the tree maxPath[i] but the root */
	/* Count the number of all root's childs  */
	for (v = G->adj[maxPath[i]]->next; v!=NULL; v = v->next)
	{
		if(v->vertex != maxPath[previousMaxPath(i)] 
			&& v->vertex!= maxPath[nextMaxPath(i)])
		{
			jSize += treeLengthB(G, v->vertex, maxPath[i], -1, B);
		}
	}

	d = maxPathLength*1.0/G->V;
	cPrime = 2-(1.0/(1-d));
	mPrime = m - jSize;
	printf("c %f \n", cPrime);
	printf("m %d \n", mPrime);

	/* Separate B */
	deleteEdge(G, maxPath[z], maxPath[nextMaxPath(z)]);
	printf("%d - %d  %d\n", maxPath[previousMaxPath(z)], 
		maxPath[z], maxPath[nextMaxPath(z)]);
	deleteEdge(G, maxPath[z], maxPath[previousMaxPath(z)]);

	lemma3(G, mPrime, cPrime, maxPath[z], B);
	S = separateSFSpecial(G, z, label, rLabel, maxPath, m);

	return S;
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
		if(p[label[maxPath[i]]] == p[label[maxPath[previousMaxPath(i)]]])
			h[p[label[maxPath[i]]]] += treeLength(G, maxPath[i], 
				maxPath[previousMaxPath(i)], maxPath[nextMaxPath(i)])-1;

	/* Calculate rô of each vertex at C  */

	for (i = 0; maxPath[i]!=-1; ++i)
	{
		if(numP[label[maxPath[i]]]>0)
		{
			T = treeLength(G, maxPath[i], maxPath[previousMaxPath(i)], 
				maxPath[nextMaxPath(i)])-1;
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

int treeLengthB(Graph *G, int root, int left, int right, int *B)
{
	/* Include each descendant in B */
	/* This recursive function returns rhe number of descendant
	it is used to construct the descendant vector
	-- descendant number includes the own root */
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != left && i->vertex != right)
			sum += treeLengthB(G, i->vertex, root, -1, B);
	B[Blength++] = root;
	return ++sum;
}


/*void printDebug()
{
	if (DEBUG == 1)
	{
		
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

	}
}*/


void printB(int *B)
{
	int i;
	printf("-------- B --------\n");
	for (i = 0; i < Blength; ++i)
	{
		printf(" %d\n", B[i]);
	}
	printf("-------------------\n");
}			