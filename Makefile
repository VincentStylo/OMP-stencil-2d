CC=gcc
CFLAGS=-g -Wall -Wstrict-prototypes -std=gnu99
LFLAGS=-lm
all:	print-2d make-2d stencil-2d
print-2d: print-2d.o
	$(CC) $(LFLAGS) -o print-2d print-2d.o
make-2d: make-2d.o
	$(CC) $(LFLAGS) -o make-2d make-2d.o
stencil-2d: stencil-2d.o
	$(CC) $(LFLAGS) -o stencil-2d stencil-2d.o
clean:
	rm -f *.o *.exe core* print-2d make-2d stencil-2d

