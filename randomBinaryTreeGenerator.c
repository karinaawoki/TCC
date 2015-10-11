#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct node Node;
struct node
{
	int num;
	Node *left;
	Node *right;
};


int *permutationVector(int size);
void printVector(int *v, int size);
void insertTree(int num, Node *root);
Node *newNode(int num, Node *left, Node*right);




int main (int argc, char *argv[])
{
	/* argv1 = size
	   argv2 = seed */
	int seed;
	int size;
	Node *root;
	int *v;
	int i;

	if(argc<=2) 
	{
		printf("Oops...\n ./(size, seed) \n");
		return 0;
	}

	seed = atoi(argv[2]);
	size = atoi(argv[1]);
	srand(seed);
	v = permutationVector(size);

	root = newNode(v[0], NULL, NULL);

	printf("%d\n", size);

	for(i = 1; i<size; i++)
	{
		insertTree(v[i], root);
	}

	if(DEBUG) printVector(v, size);

	return 0;
}

void insertTree(int num, Node *root)
{
	if(num > root->num)
	{
		if(root->right == NULL)
		{
			Node *new;
			new = newNode(num, NULL, NULL);
			root->right = new;
			printf("%d %d\n", root->num, num);
		}
		else
			insertTree(num, root->right);
	}
	else
	{
		if(root->left == NULL)
		{
			Node*new;
			new = newNode(num, NULL, NULL);
			root->left = new;
			printf("%d %d\n", root->num, num);
		}
		else
			insertTree(num, root->left);
	}
}

Node *newNode(int num, Node *left, Node*right)
{
	Node *node;
	node = malloc(sizeof(Node));

	node->num = num;
	node->left = left;
	node->right = right;
	return node;
}



int *permutationVector(int size)
{
	/* creates a vector [0,1,2,3...] and randomizes it*/
	int *vector, index;
	int i, aux;
	vector = malloc(size*sizeof(int));
	for (i = 0; i < size; i++)
		vector[i] = i;	

	for(i = size-1; i>0; i--)
	{
		/* [0 - i] */
		index = (int)((i+1)*1.0*rand()/RAND_MAX);

		aux = vector[index];
		vector[index] = vector[i];
		vector[i] = aux;
	}
	/* now, vector is a random vector */
	return vector;
}

void printVector(int *v, int size)
{
	int i;
	for(i = 0; i<size; i++) printf("%d ", v[i]);
}