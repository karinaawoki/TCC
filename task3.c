#include "root.h"


void changeOrderAtAdj(Graph *G, int *maxPath);


int main(int argc, char *argv[])
{
	int *maxPath;
	Graph *G;
	int r;
	G = read(argv[1]);
	r = (int)(G->V*1.0*rand()/RAND_MAX);

	maxPath = maximunPath(G, r);
	changeOrderAtAdj(G, maxPath);
	return 0;
}



void changeOrderAtAdj(Graph *G, int *maxPath)
{
	int i;
	Vertex *v;
	for(i = 1; maxPath[i] != -1; i++)
		for (v = G->adj[i]; v->next != NULL; v = v->next)
		{
			if(maxPath[i-1] == v->next->vertex)
			{
				Vertex *move;
				move = v->next;
				v->next = move->next;
				move->next = G->adj[i]->next;
				G->adj[i]->next = move;
				break;
			}
		}
}

void label(Graph *G)
{

}