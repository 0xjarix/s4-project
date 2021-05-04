CC= gcc
CFLAGS= -Werror -Wall -std=c99

all: fixed_patterns
fixed_patterns: fixed_patterns.o
	$(CC) $^ -o $@
fixed_patterns.o: fixed_patterns.c fixed_patterns.h

.PHONY: clean

clean: 
	${RM} fixed_patterns *.d *.o
