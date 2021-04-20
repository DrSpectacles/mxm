CC=clang
CFLAGS=-g

all: mxm_main.o
	clang mxm_main.o -o mxm

clean:
	rm -rf *.o *~
