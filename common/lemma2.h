
#include "input.h"

int lemma2(Graph *G, int m, int root, int NumVert);

int childNumber(Graph *G, int root, int *childs, int parent);
/* Set the vector childs with the number of vertices at the tree rooted by the respective vertex */

int *maximumPath(Graph *G, int r);

int Blength;