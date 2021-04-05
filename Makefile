CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDLIBS = `pkg-config --libs sdl2` -lsdl2_image
LDFLAGS=

all: processing

processing: processing.c SDL_tools.c 
#processing.o: SDL_tools.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} processing
