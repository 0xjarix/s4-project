CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDLIBS = `pkg-config --libs sdl` -lSDL_image
LDFLAGS=

all: processing custom

processing: processing.c SDL_tools.c 
custom:  custom.c processing.c SDL_tools.c 

clean:
	${RM} *.o
	${RM} *.d
	${RM} processing
	${RM} custom
