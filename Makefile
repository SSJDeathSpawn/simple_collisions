#A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc
#CC := x86_64-w64-mingw32-gcc

# set the compiler flags
CFLAGS := -W -Wall --std=c99 -lSDL2 -lm -lGL -lGLEW
#CFLAGS = --static -Wl,--no-undefined -static-libgcc -static-libstdc++ -L/usr/local/cross-tools/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lglew32 -lopengl32 -lm
# add header files here
HDRS := lib/glew/include/GL/glew.h
#HDRS := -I/usr/local/cross-tools/x86_64-w64-mingw32/include/
# add source files here
SRCS := $(wildcard src/**/*.c) $(wildcard src/*.c) $(wildcard src/**/**/*.c) $(wildcard src/**/**/**/*.c)

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := bin/app

# default recipe
all: $(EXEC)

#showfont: showfont.c Makefile
    #$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

#glfont: glfont.c Makefile
    #$(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(OBJS)

.PHONY: all clean win