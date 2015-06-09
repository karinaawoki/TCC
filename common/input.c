#include "input.h"

/* - LEITURA DE ENTRADA - */

Graph *read(char *file_name)
{
	char line[1000];
	FILE *file;
	int lineCount = 0;
	Graph *G;
	G = malloc(sizeof(Graph));
	file = fopen(file_name , "r");

	while((fgets(line, sizeof(line), file)) != NULL)
	{
	    char *aux;
		if (lineCount == 0)
		{ /* First line contains number of vertex */
			initGraph(G, atoi(line));
			lineCount = 1;	
		}

		else
		{
		    float weight = 1;
			char space[2] = " ";
			int v1 = atoi(strtok(line, space));
			int v2 = atoi(strtok(NULL, space));
			aux = strtok(NULL, space);
			if(aux!=NULL && aux[0]!='\n') weight = atof(aux);
			
			includeEdges(G, v1, v2, weight);
		}
	}
	fclose(file);
	return G;
}
