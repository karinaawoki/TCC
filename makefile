## Programs ############################################################
#CC      := gcc
#RM      := rm -f

## Flags ###############################################################
#CFLAGS  := -ansi -Wall -pedantic -Wno-unused-result -g
#LDFLAGS := -g

## Objects #############################################################
#COMMON  := common/structure.o common/input.o common/lemma2.o

#t1_obj  	  := task1.o        $(COMMON) list/queue.o
#t2_lemma2_obj := task2-lemma2.o $(COMMON)
#t2_lemma3_obj := task2-lemma3.o $(COMMON) list/queue.o
#t3_obj        := task3.o        $(COMMON) 

## Rules ###############################################################

.PHONY: all
all: t1 t2-lemma2 t2-lemma3 t3 t4 t5

## Linkage #############################################################
#t1: $(t1_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

#t2-lemma2: $(t2_lemma2_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

#t2-lemma3: $(t2_lemma3_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

#t3: $(t3_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

## Compilation #########################################################
#%.o: %.c root.h
#	$(CC) $(CFLAGS) -c $< -o $@

#common/%.o: common/%.c common/%.h
#	$(CC) $(CFLAGS) -c $< -o $@

#list/%.o: list/%.c list/%.h
#	$(CC) $(CFLAGS) -c $< -o $@

## Clean ###############################################################
.PHONY: clean
clean:
	$(RM) common/*.o list/*.o *.o




#exec
t1: task1.o structure.o input.o queue.o lemma2.o maxPath.o
	gcc task1.o structure.o input.o queue.o lemma2.o maxPath.o -o _t1
t2-lemma2: task2-lemma2.o structure.o input.o lemma2.o
	gcc task2-lemma2.o structure.o input.o lemma2.o -o _t2-lemma2
t2-lemma3: task2-lemma3.o structure.o input.o queue.o lemma2.o lemma3.o
	gcc task2-lemma3.o structure.o input.o queue.o lemma2.o lemma3.o -o _t2-lemma3
t3: task3.o structure.o input.o queue.o lemma2.o maxPath.o label.o
	gcc task3.o structure.o input.o queue.o lemma2.o maxPath.o label.o -o _t3
t4: task4.o structure.o input.o queue.o lemma2.o maxPath.o label.o lemma3.o theorem4.o
	gcc task4.o structure.o input.o queue.o lemma2.o maxPath.o label.o lemma3.o theorem4.o -o _t4
t5: task5.o structure.o input.o queue.o lemma2.o maxPath.o label.o lemma3.o theorem4.o
	gcc task5.o structure.o input.o queue.o lemma2.o maxPath.o label.o lemma3.o theorem4.o -o _t5


# ROOT
task1.o: task1.c
	gcc -Wall -ansi -pedantic -Wno-unused-result 	 -c task1.c -g
task2-lemma2.o: task2-lemma2.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-lemma2.c -g
task2-lemma3.o: task2-lemma3.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-lemma3.c -g
task3.o: task3.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task3.c -g
task4.o: task4.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task4.c -g
task5.o: task5.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task5.c -g 



# COMMON
lemma2.o: common/lemma2.c common/lemma2.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/lemma2.c -g
input.o: common/input.c common/input.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/input.c -g
structure.o: common/structure.c common/structure.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/structure.c -g
maxPath.o: common/maxPath.c 
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/maxPath.c -g
label.o: common/label.c common/label.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/label.c -g
lemma3.o: common/lemma3.c common/lemma3.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/lemma3.c -g
theorem4.o: common/theorem4.c common/theorem4.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/theorem4.c -g



# LIST
queue.o: common/list/queue.c common/list/queue.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/list/queue.c -g
