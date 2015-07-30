#include <stdio.h>
#include <stdlib.h>

int *permutationVector(int size);
void printVector(int *v, int size);


int main (int argc, char *argv[])
{
	/* 
	   argv1 = seed */
	int seed = atoi(argv[1]);
	int *v;
	srand(seed);

	v = permutationVector(11);

	printVector(v, 11);

	return 0;
}

void insertTree(int num)
{
	
}



int *permutationVector(int size)
{
	int *vector, index;
	int i, aux;
	vector = malloc(size*sizeof(int));
	for (i = 0; i < size; i++)
		vector[i] = i;	

	for(i = size-1; i>0; i--)
	{
		/* [0 - size-1] */
		index = (int)(size*1.0*rand()/RAND_MAX);

		aux = vector[index];
		vector[index] = vector[i];
		vector[i] = aux;
	}

	return vector;
}

void printVector(int *v, int size)
{
	int i;
	for(i = 0; i<size; i++) printf("%d ", v[i]);
}