#include "common/label.h"

int *decideCases(Graph *G, int *maxPath, int*label, int m, int *r);
void case1(Graph *G, int firstVertexB, int m, int *B, int *index);
void case2(Graph *G, int m, int *B, int *index, int *maxPath, int *rLabel, int *label);
int *Pb(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index);
int *Pf(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index);
int treeLength(Graph *G, int root, int left, int right);
int *HbNumber(Graph *G, int *label, int*maxPath, int*p);



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
	int i, *pb;
	/*int *Pz;*/
	printf("oiee :*\n");
	pb = Pb(G, maxPath, m, label, rLabel, index);
	HbNumber(G, label, maxPath, pb);
	for (i = 0; maxPath[i]!=-1; ++i)
	{
		printf("%d -->  num: %d\n", label[maxPath[i]], pb[label[maxPath[i]]]);
	}

	for (i = 0; i < G->V; ++i)
	{
		printf("%d\n",pb[i]);
	}
	printf("\n\n\n");


}

int *Pb(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index)
{
	int i;
	/* p[Pb(label)] is the root of Tz(label)*/
	int *p, rootLabel;

	p = malloc(G->V*sizeof(int));
	/*firstPb = malloc(G->V*sizeof(int));
	lastPb  = malloc(G->V*sizeof(int));*/

	for(i = 0; i<G->V; i++)
	{
		p[i] = -1;
		/*firstPb[i] = G->V + 1;
		lastPb [i] = -1;*/
	}
	for(i = 0; maxPath[i]!=-1; i++)
	{
		rootLabel = rLabel[(label[maxPath[i]] + m)%G->V];
		p[label[maxPath[i]]] = rootLabel;
		if(DEBUG)
			printf("%d\n", p[label[maxPath[i]]]);
	}
	return p;
}


int *Pf(Graph *G, int *maxPath, int m, int *label, int *rLabel, int *index)
{
	int i;
	/* pf number by index(original) */
	int *p, rootLabel;
	p = malloc(G->V*sizeof(int));

	for(i = 0; i<G->V; i++)
	{
		p[i] = -1;
	}
	for(i = 0; maxPath[i]!=-1; i++)
	{
		rootLabel = rLabel[(label[maxPath[i]] - m + G->V)%G->V];
		p[label[maxPath[i]]] = rootLabel;;
		if(DEBUG)
			printf("%d\n", p[label[maxPath[i]]]);
	}
	return p;
}

int *HbNumber(Graph *G, int *label, int*maxPath, int*p)
{
	int *hp;
	int i;
	hp = malloc(G->V*sizeof(int));

	for (i = 0; maxPath[i]!=-1; ++i)
	{
		if(p[label[maxPath[i]]] == p[label[maxPath[(i-1 + maxPathLength)%maxPathLength]]])
		{
			hp[p[label[maxPath[i]]]] += treeLength(G, maxPath[i], maxPath[(i-1 + maxPathLength)%maxPathLength], maxPath[(i+1)%maxPathLength]);
		}
	}

	return hp;
}



int treeLength(Graph *G, int root, int left, int right)
{
	/* This recursive function return rhe number of descendant
	it is used to construct the descendant vector
	-- descendant number includes the own root */
	Vertex *i;
	int sum = 0;
	for (i = G->adj[root]->next; i!= NULL; i = i->next)
		if (i->vertex != left && i->vertex != right)
			sum += treeLength(G, i->vertex, root, -1);
	return sum;
}