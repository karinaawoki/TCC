#include "common/lemma2.h"

int main(int argc, char *argv[])
{
	/* argv[1] = filename */
	/* argv[2] = m        */
	
	lemma2_(argv[1], atoi(argv[2]));
	return 0;
}