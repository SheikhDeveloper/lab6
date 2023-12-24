CFLAGS = -Wall -Wextra -Werror -g 
ASAN = -fsanitize=address,undefined
EXEC = lab6 debug
SRCS = $(shell find . -type f -name '*.c' -print)
HEADERS = $(shell find . -name 'lib' -type d -prune -o -type f -name '*.h' -print)
STATIC = --analyze -Xanalyzer -analyzer-output=html
 
CC = clang

lab6: lists.o queue.o main.o 
	${CC} ${ASAN} *.o -o $@

lists.o: lib/lists.c lib/lists.h
	${CC} ${CFLAGS} ${ASAN} -c lib/lists.c -o $@

queue.o: lib/queue.h lib/queue.c
	${CC} ${CFLAGS} ${ASAN} -c lib/queue.c -o $@

main.o : main.c errors.h
	${CC} ${CFLAGS} ${ASAN} -c main.c -o $@

debug: $(SRCS) $(HEADERS) 
	${CC} ${CFLAGS} -c lib/lists.c -o lists.o
	${CC} ${CFLAGS} -c main.c -o main.o
	${CC} ${CFLAGS} -c lib/queue.c -o queue.o
	${CC} *.o -o $@

.PHONY : lab6 clean static debug

static:
	${CC} lib/lists.c ${STATIC} -o lists
	${CC} main.c ${STATIC} -o main

clean: 
	rm -rf ${EXEC}
	rm -rf *.o
