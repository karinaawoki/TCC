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
		float weight;
		if (lineCount == 0)
		{ /* First line contains number of vertex */
			initGraph(G, atoi(line));
			lineCount = 1;	
		}

		else
		{
			char *aux;
			char space[2] = " ";
			int v1 = atoi(strtok(line, space));
			int v2 = atoi(strtok(NULL, space));
			aux = strtok(NULL, space);
			if(aux!=NULL && aux[0]!='\n')
				weight = atof(aux);
			else
				weight = 1;

			printf("-%f--\n", weight);

			includeEdges(G, v1, v2, weight);
		}
	}
	fclose(file);
	return G;
}