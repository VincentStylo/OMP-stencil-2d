CC=gcc
CFLAGS=-g -Wall -Wstrict-prototypes -std=gnu99
LFLAGS=-lm
all:	print-2d make-2d stencil-2d stencil-2d-stack
print-2d: print-2d.o
	$(CC) $(LFLAGS) -o print-2d print-2d.o
make-2d: make-2d.o
	$(CC) $(LFLAGS) -o make-2d make-2d.o
stencil-2d: stencil-2d.o
	$(CC) $(LFLAGS) -o stencil-2d stencil-2d.o
stencil-2d-stack: stencil-2d-stack.o
	$(CC) $(LFLAGS) -o stencil-2d-stack stencil-2d-stack.o
clean:
	rm -f *.o *.exe core* print-2d make-2d stencil-2d stencil-2d-stack

