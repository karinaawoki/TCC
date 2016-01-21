#include "maxPath.h"

int fartherVertex(Graph *G, int vertex, int *parents, int* visited);
void printPath(int *parents, int init, int end, int *maxPath, int *i);

int *maximumPath(Graph *G)
{
    /* The result will be a vector with the maximum path - the number -1 indicate the end of the path */
    int *x, *y, tree, w, *parents, *visited, *maxPath, i, r;
  
    visited = malloc(G->V*sizeof(int));
    parents = malloc(G->V*sizeof(int));
    maxPath = malloc(G->V*sizeof(int));
    x = malloc(G->V*sizeof(int));
    y = malloc(G->V*sizeof(int));
    r = tree = w = 0; 
    
    for(i = 0; i<G->V; i++) visited[i] = 0;
    for(i = 0; i<G->V; i++) maxPath[i] = -1;
    
    while (r < G->V) {
        /*if(DEBUG_2)printf("root: %d \n", r); */
        /* defining the start and the end of the 
           maximumPath of the analized tree */
        x[tree] = fartherVertex(G, r, parents, visited);
        y[tree] = fartherVertex(G, x[tree], parents, visited);
        printPath(parents, x[tree], y[tree], maxPath, &w);
        tree++; 
    
        /* Will stop when ii find a vertex that 
           is not visited  -  save the vertex */
        for(r=0; r<G->V && visited[r]; r++);
        /* If all vertices was visited, r will be G->V (BREAK)*/
    }
  
    free(visited);
    free(parents); 
    for (i=1; i<tree; i++) includeBridgeEdges(G, y[i-1], x[i]);
    free(x); 
    free(y);
    /*if(DEBUG_2||STEP) printf("length: %d\n", maxPathLength);*/
    return maxPath;
}

void printPath(int *parents, int init, int end, int *maxPath, int *i)
{
    int vertex;
    
    /*if(DEBUG_2||STEP) printf("TASK 1 - The longest path in the tree is: \n");
    if(DEBUG_2||STEP) printf("%d  ", end);*/
    maxPath[*i] = end; 
    (*i)++;
    vertex = parents[end];
    while(vertex != init) 
    {
        /*if(DEBUG_2||STEP) printf("%d  ", vertex);*/
        maxPath[*i] = vertex;
        vertex = parents[vertex];
        (*i)++;
    }
    if(init!=end)
    {
        /*if(DEBUG_2||STEP) printf("%d\n", init);*/
        maxPath[*i] = init;
        (*i)++;
    }
    /*else if(DEBUG_2||STEP) printf("\n");*/
    
    maxPathLength = (*i);

}

int fartherVertex(Graph *G, int vertex, int *parents, int *visited)
{ /* QUEUE of vertex - farther at the end */
    Queue *q;
    int i, farther = -1;
    Vertex *aux;

    q = initQueue(vertex);
    for(i = 0; i<G->V; i++) parents[i] = -1;
    parents[vertex] = vertex;
    while(!emptyQueue(q)) 
    {
        for(aux = G->adj[q->init->num]->next; aux!=NULL; aux = aux->next) 
        {
            if (parents[aux->vertex]==-1 && aux->edge==1) 
            {
                insertQueue(q, aux->vertex);
                parents[aux->vertex] = q->init->num;
            }
        }
        farther = removeQueue(q);
    }

    for(i = 0; i<G->V; i++) 
        if (parents[i] != -1) 
            visited[i] = 1;

    freeQueue(q);
    return farther;
}
