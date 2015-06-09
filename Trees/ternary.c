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
	printf("%d\n", 
			(int)((pow(3, len)-1)/2) 
		  );

	/*estoura();*/
	create3Childs(0, 1);

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

void newChild(int parent)
{
	num++;
	printf("%d %d\n", parent, num);
}