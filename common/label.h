#include "lemma2.h"

int changeOrderAtAdj(Graph *G, int *maxPath, int *r);
int *label(Graph *G, int *maxPath, int max, int *r);
void depthFirst(Graph *G, int vertex, int parent, int *vertLabel, int *r);
void printLabel(Graph *G, int *vLabel, int *r);
int *indexRbyLabel(Graph *G, int *r, int *vLabel);
int *labelToIndex(Graph *G, int *label);


int count;