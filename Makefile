CC=clang
CFLAGS=-g

all: mxm_main.o mxm_funcs.o
	clang mxm_main.o mxm_funcs.o -o mxm

worker: mxw_main.o mxw_funcs.o
	clang mxw_main.o mxw_funcs.o -o mxw

clean:
	rm -rf *.o *~
