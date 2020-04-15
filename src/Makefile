GCC=gcc

CFLAGS=-g3

OFLAGS=-O0

IN=main.c file.c enc.c ppm.c steg.c
OUT=../bin/ysteg

all:
	$(GCC) $(CFLAGS) $(OFLAGS) $(IN) -o $(OUT)

clean:
	rm -Rf *~ $(OUT)
