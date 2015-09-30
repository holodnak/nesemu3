# directory containing sources
SRCDIR = source

# compiler/linker names
CC = gcc
LD = gcc

# compiler defines
DEFS = -DPI

# compiler/linker flags
CDEBUG = -g -Isource -I/usr/local/include
CFLAGS = $(CDEBUG) $(DEFS) -Isource
LDFLAGS = -F/Library/Frameworks

SRCS = $(wildcard source/system/*.c)
SRCS += $(wildcard source/misc/*.c)
SRCS += $(wildcard source/gui/*.c)

#SRCS += source/nes/nes.c source/nes/cpu/cpu.c
#SRCS += source/system/video.c source/system/input.c source/system/sound.c

LIBS = -lm -framework SDL2 -framework SDL2_image

OBJS = $(SRCS:.c=.o)

.PHONY: all

all:	nesemu3

nesemu3:	$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

