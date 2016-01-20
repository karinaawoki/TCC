#include "maxPath.h"

int Algorithm2(Graph *G, int m, int root, int NumVert, int leftNeighbor, int rightNeighbor);

int descendantsNumber(Graph *G, int root, int *childs, int leftNeighbor, int rightNeighbor);
/* Set the vector childs with the number of vertices at the tree rooted by the respective vertex */

int Blength;
