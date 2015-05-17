#include "common/theorem4.h"

void theorem6(Graph *G, int m);
void countEdgesAtCut(Graph *G, int ver, int parent);
void relabel(Graph *G, int *label, int *index);
void reMaxPath(Graph *G, int *maxPath, int *index);
void test(Graph *G, int *label, int *index, int *maxPath);


int numCut;

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	Graph *G;
	Blength = 0;
	numCut  = 0;
	maxPathInit = -1;
	maxPathEnd  = -1;

	G = read(argv[1]);
	if(G->V < atoi(argv[2]))
	{
		freeGraph(G);
		printf("m maior que o número de vértices!!\n");
		return 0;
	}

	setBInit(G);
	theorem6(G, atoi(argv[2]));

	free(setB);
	freeGraph(G);
	return 0;
}


void theorem6(Graph *G, int m)
{
	int *maxPath, *labelVec, *r, *index;
	int root, Ssize, max;
	srand(seed);
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	root = 1;
	r = malloc(G->V*sizeof(int));

	maxPath = maximumPath(G, root);

	/* Labeling */
	max = changeOrderAtAdj(G, maxPath, r);
	labelVec = label(G, maxPath, max, r);

	index = labelToIndex(G, labelVec);


	Ssize = theorem4(G, m, root, labelVec, index, maxPath, r);
	while(Blength < m)
	{
		if(Ssize<0)
			printf("ERROOOO\n");

		reMaxPath(G, maxPath, index);
		relabel(G, labelVec, index);
		Ssize = theorem4(G, m-Blength, Ssize, labelVec, index, maxPath, r);
	}
	
	countEdgesAtCut(G, 0, 0);
	printf("CORTE: %d\n", numCut);

	free(maxPath);
	/*printLabel(G, labelVec, r);*/
	free(r);
	free(labelVec);
	free(index);
}



void countEdgesAtCut(Graph *G, int ver, int parent)
{
    Vertex *v;
    for(v = G->adj[ver]->next; v!=NULL; v = v->next)
    {
        if(v->vertex!=parent && v->original==1)
        {
        	if(setB[ver]!=setB[v->vertex])
        	{
        		printf("%d -- %d\n", ver, v->vertex);
            	numCut++;
        	}
            countEdgesAtCut(G, v->vertex, ver);
        }   
    }
}





/* Both, first and last elemments of NEW label are at maxPath  */
void reMaxPath(Graph *G, int *maxPath, int *index)
{
	int *auxMaxPath;
	int init, end, i, j = 0;

	init = index[maxPathInit];
	end = index[maxPathEnd];
 
    auxMaxPath = malloc((1+G->V)*sizeof(int));

	for(i = 0; i<G->V; i++)
	{
		auxMaxPath[i] = maxPath[i];
		maxPath[i] = -1;
	}

	for (i = 0; i<G->V ; i++)
	{
		if(auxMaxPath[i] == init)
		{
			while(auxMaxPath[i] != end)
			{
				maxPath[j++] = auxMaxPath[i];
				i = (i+1)%maxPathLength;
			}
			maxPath[j++] = auxMaxPath[i];
			maxPath[j] = -1;
			maxPathLength = j;
			break;
		}
	}

	free(auxMaxPath);
}


void relabel(Graph *G, int *label, int *index)
{
	int *auxLabel, *auxIndex, i;

	auxLabel = malloc(G->V*sizeof(int));
	auxIndex = malloc(G->V*sizeof(int));
	for (i = 0; i < G->V; i++)
	{
		auxIndex[i] = index[i];
		auxLabel[i] = label[i];
		index[i] =-1;
		label[i] = -1;
	}
	for(i = maxPathInit; i!=maxPathEnd; i = (i+1)%countLabel)
	{
		index[(i-maxPathInit + countLabel)%countLabel] = auxIndex[i];
		label[auxIndex[i]] = (i-maxPathInit+countLabel)%countLabel;
	}
	index[(i-maxPathInit + countLabel)%countLabel] = auxIndex[i];
	label[auxIndex[i]] = (i-maxPathInit+countLabel)%countLabel;

	countLabel = (maxPathEnd-maxPathInit + countLabel)%countLabel;

	free(auxLabel);
	free(auxIndex);
}


void test(Graph *G, int *label, int *index, int *maxPath)
{
	int i;
	for(i = 0; i<G->V; i++)
	{
		printf("label[%d] = %d\n", i, label[i]);
	}
	printf("\n\n\n");

	for(i = 0; i<G->V; i++)
	{
		printf("index[%d] = %d\n", i, index[i]);
	}
	printf("\n\n\n");

	printf("%d\n", maxPathLength);

	for(i = 0; i<G->V; i++)
	{
		printf("maxPath[%d] = %d\n", i, maxPath[i]);
	}
}