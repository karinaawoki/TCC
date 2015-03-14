t1: task1.o task2.o structure.o input.o queue.o
	gcc task1.o task2.o structure.o input.o queue.o -o t1
t2: task2.o structure.o input.o queue.o
	gcc task2.o structure.o input.o queue.o -o t2

task1.o: task1.c 
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task1.c -g
task2.o: task2.c 
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2.c -g

input.o: input.c input.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c input.c -g
	
structure.o: structure.c structure.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c structure.c -g

queue.o: list/queue.c list/queue.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c list/queue.c -g
