#include "common/theorem4.h"

void theorem6(Graph *G, int m);
void countEdgesAtCut(Graph *G, int ver, int parent);
void relabel(Graph *G, int *label, int *index);
void reMaxPath(Graph *G, int *maxPath, int *index);


int numCut;

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */

	Graph *G;
	Blength = 0;
	numCut = 0;

	G = read(argv[1]);
	if(G->V < atoi(argv[2]))
	{
		printf("m maior que o número de vértices!!\n");
		return 0;
	}

	setBInit(G);
	theorem6(G, atoi(argv[2]));

	freeGraph(G);
	return 0;
}


void theorem6(Graph *G, int m)
{
	int *maxPath, *labelVec, *r, *index;
	int root, Ssize, max;

	root = (int)(G->V*1.0*rand()/RAND_MAX);

	r = malloc(G->V*sizeof(int));

	maxPath = maximumPath(G, root);

	/* Labeling */
	max = changeOrderAtAdj(G, maxPath, r);
	labelVec = label(G, maxPath, max, r);

	index = labelToIndex(G, labelVec);



	Ssize = theorem4(G, m, root, labelVec, index, maxPath, r);
	while(Blength < m)
	{
		printf("kkkkk %d \n", Blength);
		if(Ssize<0)
			printf("ERROOOO\n");
		Ssize = theorem4(G, m-Blength, Ssize, labelVec, index, maxPath, r);
	}
	
	/*for(i = 0; i<G->V; i++)
	{
	if(setB[i] == 1)
	    printf("setB[%d] = %d\n", i, setB[i]);
	}
	printf("\n\n");
	for(i = 0; i<Blength; i++)
	{
	    printf("B[%d] = %d\n", i, B[i]);
	}*/
	
	countEdgesAtCut(G, 0, 0);
	printf("CORTE: %d\n", numCut);

	free(maxPath);
	printLabel(G, labelVec, r);
	free(r);
	free(labelVec);

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

	for (i = 0; i<maxPathLength ; i++)
	{
		if(maxPath[i] == init)
		{
			while(maxPath[i] != end)
			{
				auxMaxPath[j++] = maxPath[i];
				i = (i+1)%maxPathLength;
			}
			auxMaxPath[j++] = maxPath[i];
			auxMaxPath[j] = -1;
			maxPathLength = j;
			break;
		}
	}

	free(maxPath);
	maxPath = auxMaxPath;
}


void relabel(Graph *G, int *label, int *index)
{
	int *auxLabel, *auxIndex, i;
	
	auxLabel = malloc(G->V*sizeof(int));
	auxIndex = malloc(G->V*sizeof(int));
	for (i = 0; i < G->V; i++)
	{
		auxIndex[i] = -1;
		auxLabel[i] = -1;
	}
	for(i = maxPathInit; i!=maxPathEnd; i = (i+1)%maxPathLength)
	{
		auxIndex[(i-maxPathInit + maxPathLength)%maxPathLength] = index[i];
		auxLabel[index[i]] = (i-maxPathInit+maxPathLength)%maxPathLength;
	}

	free(label);
	free(index);

	label = auxLabel;
	index = auxIndex;
}