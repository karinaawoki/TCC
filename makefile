t1: task1.o structure.o input.o queue.o
	gcc task1.o structure.o input.o queue.o -o t1
#t2: task2.o structure.o input.o queue.o
#	gcc task2.o structure.o input.o queue.o -o t2

task1.o: task1.c 
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task1.c -g


lemma2.o: lemma2.c lemma2.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c lemma2.c -g
input.o: common/input.c common/input.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/input.c -g
	
structure.o: common/structure.c common/structure.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/structure.c -g


queue.o: list/queue.c list/queue.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c list/queue.c -g
