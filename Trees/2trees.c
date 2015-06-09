#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void create3Childs(int i, int height);
void newChild(int parent);
void create3ChildsBigTree(int i, int height, int *aux);
int *vec(int h);
void newEdge(int vertex1, int vertex2);


int num;
int len;
int auxNum;

int main (int argc, char *argv[])
{
	int *aux, root2, i, j, distT1T2, end;
	auxNum = 0;
	len = atoi(argv[1]);  distT1T2 = atoi(argv[2])--;
	num = 0;
	/*printf("%d\n", 
			(int)((pow(3, len)-1)/2) 
		  );
*/
	/* creating T1 (small tree) */
	create3Childs(0, 1);
	aux = vec(len);
	root2 = ++num;
	/* creating T2 (big tree) */
	create3ChildsBigTree(root2, 1, aux);

	printf("------------------\n");
	

	/* Edges next to T2 (big tree) */
	num++;
	end = num;
	for (i = 0; i < len; ++i)
	{
		newChild(num);
	}
	newEdge(num, root2);


	/* Edges next to T1 (small tree) */
	num++;
	for (i = 0; i < len-1; i++)
	{
		newChild(num);
	}
	newEdge(num, 0);


	/* Edges between T1 and T2(big tree) */
	j = 0;
	i = (int)((pow(3, len)-1)/6) - 2*len+1;
	if(distT1T2>i) distT1T2 = i;

	for (i = 0; i < distT1T2; ++i)
	{
		newChild(j);
		j = num;
		i--;
	}
	newEdge(j, root2);

	/*  */
	printf("%s\n", );
	while(i>0)
	{
		newChild(j);
		i--;
		j = num;
	}

	return 0;
}



void create3Childs(int i, int height)
{
	int n;
	
	if(height<len)
	{
		newChild(i);
		newChild(i);
		newChild(i);
		n = num;
		create3Childs(n-2, height+1);
		create3Childs(n-1, height+1);
		create3Childs(n, height+1);
	}
}

void create3ChildsBigTree(int i, int height, int *aux)
{
	int n;
	
	if(height<len)
	{
		newChild(i);
		newChild(i);
		newChild(i);
		n = num;
		create3ChildsBigTree(n-2, height+1, aux);
		create3ChildsBigTree(n-1, height+1, aux);
		create3ChildsBigTree(n, height+1, aux);
	}
	else if(height == len)
	{
		int k;
		printf("---------\n");
		for(k=0; k<aux[auxNum]; k++)
			newChild(i);
		auxNum++;
	}

}

void newChild(int parent)
{
	num++;
	printf("%d %d\n", parent, num);
}

void newEdge(int vertex1, int vertex2)
{
	printf("%d %d\n", vertex2, vertex1);
}

int nextPosition(int position, int size) 
{
	/*  This funtion will give the position in this order
		 + - - - - -
		 + - - - - +
		 + + - - - +
		 + + - - + +
		 + + + - + +
		 + + + + + +
	*/
	if(position == size/2)
		return -1;
	if(position < size/2)
		return size- position-1;
	else
		return size- position;


}

int *vec(int h)
{
	int *v, i, space, j = 0;
	int size = (int)(pow(3, h-1));
	int rest = (int)((pow(3, h) -1))/2;
	v= malloc(size*sizeof(int));

	for(i = 0; i<size; i++)
	{
		v[i] = (int)(rest/size);
	}
	rest = rest%size;
	if(rest == 1)
	{
		v[0]++;
		return v;
	}
	space = (size-1)/(rest-1);

	for (i = 0; i < size && j<rest;)
	{
		v[i]++;
		j++;
		i+=space;
	}

	return v;
}