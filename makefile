## Programs ############################################################
CC      := gcc
RM      := rm -f

## Flags ###############################################################
CFLAGS  := -ansi -Wall -pedantic -Wno-unused-result -g
LDFLAGS := -g

## Objects #############################################################
COMMON  := common/structure.o common/input.o common/lemma2.o

t1_obj  	  := task1.o        $(COMMON) list/queue.o
t2_lemma2_obj := task2-lemma2.o $(COMMON)
t2_lemma3_obj := task2-lemma3.o $(COMMON) list/queue.o

## Rules ###############################################################

.PHONY: all
all: t1 t2-lemma2 t2-lemma3

## Linkage #############################################################
t1: $(t1_obj)
	$(CC) $^ -o $@ $(LDFLAGS)

t2-lemma2: $(t2_lemma2_obj)
	$(CC) $^ -o $@ $(LDFLAGS)

t2-lemma3: $(t2_lemma3_obj)
	$(CC) $^ -o $@ $(LDFLAGS)

## Compilation #########################################################
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

common/%.o: common/%.c common/%.h
	$(CC) $(CFLAGS) -c $< -o $@

list/%.o: list/%.c list/%.h
	$(CC) $(CFLAGS) -c $< -o $@

## Clean ###############################################################
.PHONY: clean
clean:
	$(RM) common/*.o list/*.o *.o

# ROOT
# task1.o: task1.c 
# 	gcc -Wall -ansi -pedantic -Wno-unused-result 	 -c task1.c -g
# task2-lemma2.o: task2-lemma2.c
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-lemma2.c -g
# task2-lemma3.o: task2-lemma3.c
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c task2-lemma3.c -g


# COMMON
# lemma2.o: common/lemma2.c common/lemma2.h
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/lemma2.c -g
# input.o: common/input.c common/input.h
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/input.c -g
# structure.o: common/structure.c common/structure.h
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c common/structure.c -g


# LIST
# queue.o: list/queue.c list/queue.h
# 	gcc -Wall -ansi -pedantic -Wno-unused-result -c list/queue.c -g
