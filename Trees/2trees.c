#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void create3Childs(int i, int height);
void newChild(int parent);

int num;
int len;

int main (int argc, char *argv[])
{
	len = atoi(argv[1]);
	num = 0;
	/*printf("%d\n", 
			(int)((pow(3, len)-1)/2) 
		  );
*/
	create3Childs(0, 1);
	create3Childs2(num++, 1);

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

void create3Childs2(int i, int height)
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
	else if(height == len)
	{
		newChild(i)
	}
}

void newChild(int parent)
{
	num++;
	printf("%d %d\n", parent, num);
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
	int next;
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
	size = pow(3, h-1);
	rest = (pow(3, h) -1)/2;
	v= malloc(size*sizeof(int));

	for(i = 0; i<size; i++)
	{
		v[i] = (int)rest/size;
	}
	rest = rest%size;

	space = (size-1)/(rest-1);

	for (i = 0; i < size && j<rest;)
	{
		v[i]++;
		j++;
		i+=space;
	}
}