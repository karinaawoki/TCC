#include <stdlib.h>

typedef struct number Num;
struct number
{
	int num;
	Num *next;
};
