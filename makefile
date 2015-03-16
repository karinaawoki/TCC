#exec
t1: task1.o structure.o input.o queue.o
	gcc task1.o structure.o input.o queue.o -o t1
t2-lemma2: task2-lemma2.o structure.o input.o queue.o lemma2.o
	gcc task2-lemma2.o structure.o input.o queue.o lemma2.o -o t2-lemma2


# ROOT
task1.o: task1.c 
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task1.c -g
task2-lemma2.o: task2-lemma2.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-lemma2.c -g


# COMMON
lemma2.o: common/lemma2.c common/lemma2.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/lemma2.c -g
input.o: common/input.c common/input.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/input.c -g
structure.o: common/structure.c common/structure.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/structure.c -g


# LIST
queue.o: list/queue.c list/queue.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c list/queue.c -g