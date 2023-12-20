TRASH = *.o *~ o.* *.so move file*
CFLAGS=-Wall

all:	move remove.so

move:	move.o

remove.so:	remove.c
	cc -shared -o remove.so remove.c

clean:
	rm -rf $(TRASH)