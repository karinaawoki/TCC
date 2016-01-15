#include "label.h"

void printLabel(Graph *G, int *vLabel, int *r)
{
	int i;
	for (i = 0; i < G->V; ++i)
	{
		printf("vertice %d : label %d   - raiz %d \n", i, vLabel[i], r[i]);
	}
}

int *indexRbyLabel(Graph *G, int *r, int *vLabel)
{
	int i, *rLabel;
	rLabel = malloc(G->V*sizeof(int));

	for (i = 0; i < G->V; i++)
		rLabel[i] = -1;

	for(i = 0; i<G->V; i++)
	{
		if(vLabel[i]!=-1)
			rLabel[vLabel[i]] = vLabel[r[i]];
	}
	return rLabel;
}

int *labelToIndex(Graph *G, int *label)
{
	int i, *index;
	index = malloc(G->V*sizeof(int));

	for (i = 0; i < G->V; i++)
		index[i] = -1;

	for (i = 0; i<G->V; i++)
	{
		if(label[i]!=-1)
			index[label[i]] = i;
	}
	return index;
}

int changeOrderAtAdj(Graph *G, int *maxPath, int *r)
/* Returns the last sub-tree root */
{
	int i;
	Vertex *v;
	for (i = 0; i < G->V; ++i)
		r[i] = -1;

	/* Starts with 1 because each MaxPath vertex looks to its previous */
	for(i = 1; i<maxPathLength; i++)
	{
		r[maxPath[i]] = maxPath[i];
		for (v = G->adj[maxPath[i]]; v->next != NULL; v = v->next)
		{
			if(maxPath[i-1] == v->next->vertex && v->next->edge==1)
			{
				Vertex *move;
				move = v->next;
				v->next = move->next;
				move->next = G->adj[maxPath[i]]->next;
				G->adj[maxPath[i]]->next = move;
				break;
			}
			
		}
	}
	r[maxPath[0]] = maxPath[0];
	return maxPath[i-1];
}

int *label(Graph *G, int *maxPath, int max, int *r)
{
	/* max is the last MaxPath vertex  */
	int *vertLabel, i;
	vertLabel = malloc(G->V*sizeof(int));

	for (i = 0; i < G->V; i++)
	{
		vertLabel[i] = -1;
	}

	countLabel = 0;
	depthFirst(G, max, max, vertLabel, r);
	return vertLabel;
}

void depthFirst(Graph *G, int vertex, int parent, int *vertLabel, int *r)
{
	Vertex *v;
	for(v = G->adj[vertex]->next; v!=NULL; v = v->next)
	{
		if(v->vertex!=parent && v->edge==1)
		{
			if (r[v->vertex]==-1)
				r[v->vertex] = r[vertex];
			depthFirst(G, v->vertex, vertex, vertLabel, r);
		}
	}
	vertLabel[vertex] = countLabel ++;
} 