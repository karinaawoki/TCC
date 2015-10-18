#include "common/doubleDiam.h"
#include <time.h>

void exactCut(Graph *G, int m);
void countEdgesAtCut(Graph *G, int ver, int parent);
void relabel(Graph *G, int *label, int *index);
void reMaxPath(Graph *G, int *maxPath, int *index);
void test(Graph *G, int *label, int *index, int *maxPath);


int numCut;
float numCutWeight;
clock_t tempoInicial, tempoFinal;
double tempoGasto;
int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	float bound;

	int maxDegree = -1;

  	Graph *G; int m, max = 0, i;
  	Vertex *v;
  	Blength = 0;
  	numCut  = 0;
  	numCutWeight = 0;
  	maxPathInit = -1;
  	maxPathEnd  = -1;
  	seed = 1;
  	DEBUG = 0;
  	STEP = 0;
  	DEBUG_2 = 1;


  	if(argc>=4)
    {
    	DEBUG = atoi(argv[3]);
      	if(DEBUG == 2) DEBUG_2 = 0;
      	if(DEBUG == 3) {STEP = 1; DEBUG = 0; DEBUG_2 = 0;}
      	if(argc>=5) seed = atoi(argv[4]);
    }
  
  	G = read(argv[1]);

  	for(i=0; i<G->V; i++)
  	{
  		int degree = 0;
  		for (v = G->adj[i]->next; v!=NULL; v = v->next)
  		{
  			degree++;
  		}
  		if(degree>maxDegree)
  		{
  			maxDegree = degree;
  		}
  	}

  	tempoInicial = clock();

  	if(argc > 2 && argv[2][0]=='n')
  	{
  		for (m=0; m<G->V; m++) 
	  	{
	  		Blength = 0;
		  	numCut  = 0;
		  	maxPathInit = -1;
		  	maxPathEnd  = -1;
	    	setBInit(G);
	    	exactCut(G, m);
		    if (numCut > max) max = numCut;
		    free(setB);
  			freeGraph(G);
	  		G = read(argv[1]);
	  }
	  	printf("Max cut found: %d\n", max);
  	}
  	else if(argc > 2 && G->V < atoi(argv[2]))
        printf("Input error: m is greater than the number of vertices in the graph!!!\n");

    else if (argc > 2)
    {
    	setBInit(G);
	  	exactCut(G, atoi(argv[2]));
	  
	  	free(setB);
    }
  
  /* setB is a bit vector - a vertex is or not at B */


    tempoFinal = clock();

  	
	printf(" MaxDegree: %d\n", maxDegree);
  	bound = maxDegree*8.0*G->V/maxPathLength;
    printf("Bound: %f\n", bound);

 
  	freeGraph(G);
  	tempoGasto = (tempoFinal-tempoInicial)*1.0/CLOCKS_PER_SEC;
    printf("TEMPO: %f\n seg", tempoGasto);
  	return 0;
}



void exactCut(Graph *G, int m)
{
	int *maxPath, *labelVec, *r, *index;
	int root, elemmentOfS, max;
	srand(seed);
	root = (int)(G->V*1.0*rand()/RAND_MAX);
	
	/* r shows the root (according to index) */
	r = malloc(G->V*sizeof(int));

	/* maxPath = maximumPath(G, root); */
	maxPath = maximumPath(G);


	/* Labeling */
	max = changeOrderAtAdj(G, maxPath, r);
	labelVec = label(G, maxPath, max, r);

	index = labelToIndex(G, labelVec);

	elemmentOfS = doubleDiam(G, m, root, labelVec, index, maxPath, r);
	while(Blength < m)
	{
		if(DEBUG==1){
			test(G, labelVec, index ,maxPath);
			printGraph(G); }

		if(elemmentOfS<0)
			printf("ERROR\n");

		reMaxPath(G, maxPath, index);
		relabel(G, labelVec, index);
		elemmentOfS = doubleDiam(G, m-Blength, elemmentOfS, labelVec, index, maxPath, r);
	}
	if(DEBUG == 1) printGraph(G);
		
	countEdgesAtCut(G, 0, 0);
	printf("**** Cut **** : %d\n", numCut);
    printf("Cut-weight: %f \n", numCutWeight);
    
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
        	if(setB[ver]!=setB[v->vertex] && v->bridge==0)
        	{
        		if(DEBUG_2) printf("%d -- %d\n", ver, v->vertex);
            	numCut++;
            	numCutWeight+= v->weight;
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
