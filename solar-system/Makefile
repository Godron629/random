INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/lib/

COMPILERFLAGS = -Wall
CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm

All: control

control: solar.o
	$(CC) $(CFLAGS) -o a.out $(LIBDIR) $< $(LIBRARIES)
