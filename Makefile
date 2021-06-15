# Makefile

CC= gcc #-fsanitize=address
CPPFLAGS= `pkg-config --cflags sdl2 sdl gtk+-3.0` -lSDL2_image -lSDL_image -MMD
CFLAGS= -Wall -Wextra -std=c99 -O2 -g
LDFLAGS=
LDLIBS=`pkg-config --libs sdl2 sdl gtk+-3.0` -lSDL2_image -lSDL_image -lm

DMSRC= src/decode/d_main.c src/decode/freect.c

# Encoding and Decoding code
ASRC= src/decode/analysis/analysis.c
MESRC= src/decode/msg_encoding/encode.c src/decode/msg_encoding/encode_message.c src/decode/msg_encoding/weaver.c
DSRC= src/decode/draw/draw.c src/decode/draw/fill_mat.c src/decode/draw/mask.c
GSRC= src/decode/gen_img/gen_img.c
RSSRC= src/decode/error_cor/RS/array.c src/decode/error_cor/RS/op.c src/decode/error_cor/RS/encode_RS.c src/decode/error_cor/RS/decode_RS.c
SSRC= src/sdl/mysdl.c
MDSRC= src/decode/msg_decoding/decode.c src/decode/msg_decoding/unweaver.c src/decode/msg_decoding/decode_message.c

# Segmentation code
IPSRC= src/preprocessing/preprocessing.c
SGSRC= src/segmentation/fpfind.c src/segmentation/FPValid.c src/segmentation/geotrans.c src/segmentation/aploc.c src/segmentation/apsamp.c src/segmentation/extcode.c src/segmentation/surfdraw.c
BSSRC= src/segmentation/proc_code.c src/segmentation/color_mat.c src/segmentation/demask.c src/segmentation/bit_ext.c
MSSRC= src/segmentation/segmentation.c

GUISRC = src/gui/main.c src/custom/custom.c src/custom/SDL_tools.c
DECSRC = src/decode/main.c
# Decoding objects
GUIOBJ=${GUISRC:.c=.o}
DECOBJ=${DECSRC:.c=.o}
DOBJ=${DMSRC:.c=.o} ${MSRC:.c=.o} ${ASRC:.c=.o} ${MESRC:.c=.o} ${DSRC:.c=.o} ${GSRC:.c=.o} ${RSSRC:.c=.o} ${SSRC:.c=.o} ${MDSRC:.c=.o} ${IPSRC:.c=.o} ${SGSRC:.c=.o} ${BSSRC:.c=.o} ${MSSRC:.c=.o}
DDEP=${DMSRC:.c=.d} ${MSRC:.c=.d} ${ASRC:.c=.d} ${MESRC:.c=.d} ${DSRC:.c=.d} ${GSRC:.c=.d} ${RSSRC:.c=.d} ${SSRC:.c=.d} ${MDSRC:.c=.d} ${IPSRC:.c=.d} ${SGSRC:.c=.d} ${BSSRC:.c=.d} ${MSSRC:.c=.d}


all: decode gui

decode: ${DOBJ} ${DECOBJ}
	${CC} ${CFLAGS} ${CPPFLAGS} ${DOBJ} ${DECOBJ} ${LDLIBS} -o decode

gui: ${DOBJ} ${GUIOBJ}
	${CC} ${CFLAGS} ${CPPFLAGS} ${DOBJ} ${GUIOBJ} ${LDLIBS} -o gui



.PHONY: clean

clean:
	${RM} ${OBJ} ${DEP} *~	
	${RM} ${DOBJ} ${GUIOBJ} ${DECOBJ} ${DDEP} *-
	${RM} decode gui
	${RM} *.d
	${RM} src/gui/*.o src/gui/*.d

-include ${DEP} ${DDEP}

# End
