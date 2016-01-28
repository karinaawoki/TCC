## Programs ############################################################
#CC      := gcc
#RM      := rm -f

## Flags ###############################################################
#CFLAGS  := -ansi -Wall -pedantic -Wno-unused-result -g
#LDFLAGS := -g

## Objects #############################################################
#COMMON  := common/structure.o common/input.o common/simpleApproxCut.o

#t1_obj  	  := task0.o        $(COMMON) list/queue.o
#t2_simpleApproxCut_obj := task2-simpleApproxCut.o $(COMMON)
#t2_approxCut_obj := task2-approxCut.o $(COMMON) list/queue.o
#t3_obj        := task3.o        $(COMMON) 

## Rules ###############################################################

.PHONY: all
all: t0 t1 t2-simpleApproxCut t2-approxCut t3 t4 t5 gen

## Linkage #############################################################
#t1: $(t1_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

#t2-simpleApproxCut: $(t2_simpleApproxCut_obj)
#	$(CC) $^ -o $@ $(LDFLAGS)

#t2-approxCut: $(t2_approxCut_obj)
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
	$(RM) common/*.o common/list/*.o *.o _* *~ common/*~ common/list/*~ 
	$(RM) tests/*~ doc/monografia/*.log doc/monografia/*.toc doc/monografia/*.aux 
	$(RM) doc/monografia/*.bbl doc/monografia/*.blg




#exec
t0: task0.o structure.o input.o queue.o simpleApproxCut.o maxPath-v1.o
	gcc task0.o structure.o input.o queue.o simpleApproxCut.o maxPath-v1.o -o _t0
t1: task1.o structure.o input.o queue.o simpleApproxCut.o maxPath.o
	gcc task1.o structure.o input.o queue.o simpleApproxCut.o maxPath.o -o _t1
t2-simpleApproxCut: task2-simpleApproxCut.o structure.o input.o simpleApproxCut.o
	gcc task2-simpleApproxCut.o structure.o input.o simpleApproxCut.o -o _t2-simpleApproxCut
t2-approxCut: task2-approxCut.o structure.o input.o queue.o simpleApproxCut.o approxCut.o
	gcc task2-approxCut.o structure.o input.o queue.o simpleApproxCut.o approxCut.o -o _t2-approxCut
t3: task3.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o
	gcc task3.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o -o _t3
t4: task4.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o approxCut.o doubleDiam.o
	gcc task4.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o approxCut.o doubleDiam.o -o _t4
t5: task5.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o approxCut.o doubleDiam.o
	gcc task5.o structure.o input.o queue.o simpleApproxCut.o maxPath.o label.o approxCut.o doubleDiam.o -o _t5
gen: randomBinaryTreeGenerator.o
	gcc randomBinaryTreeGenerator.o -o _gen

# ROOT
task0.o: task0.c
	gcc -Wall -ansi -pedantic -Wno-unused-result 	 -c task0.c -g
task1.o: task1.c
	gcc -Wall -ansi -pedantic -Wno-unused-result 	 -c task1.c -g
task2-simpleApproxCut.o: task2-simpleApproxCut.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-simpleApproxCut.c -g
task2-approxCut.o: task2-approxCut.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-approxCut.c -g
task3.o: task3.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task3.c -g
task4.o: task4.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task4.c -g
task5.o: task5.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c task5.c -g 
randomBinaryTreeGenerator.o: randomBinaryTreeGenerator.c
	gcc -Wall -ansi -pedantic -Wno-unused-result -c randomBinaryTreeGenerator.c -g 


# COMMON
simpleApproxCut.o: common/simpleApproxCut.c common/simpleApproxCut.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/simpleApproxCut.c -g
input.o: common/input.c common/input.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/input.c -g
structure.o: common/structure.c common/structure.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/structure.c -g
maxPath.o: common/maxPath.c common/maxPath.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/maxPath.c -g
maxPath-v1.o: common/maxPath-v1.c common/maxPath-v1.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/maxPath-v1.c -g
label.o: common/label.c common/label.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/label.c -g
approxCut.o: common/approxCut.c common/approxCut.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/approxCut.c -g
doubleDiam.o: common/doubleDiam.c common/doubleDiam.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/doubleDiam.c -g



# LIST
queue.o: common/list/queue.c common/list/queue.h
	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/list/queue.c -g
