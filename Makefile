CC= gcc
CFLAGS= -Werror -Wall -std=c99

all: demo
demo: demo.o
	$(CC) $^ -o $@
demo.o: demo.c demo.h

.PHONY: clean

clean: 
	${RM} demo *.d *.o
