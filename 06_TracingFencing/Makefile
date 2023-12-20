TRASH = *.o *~ o.* *.so move file*
CFLAGS=-Wall

.SILENT: test1 test2 test3 test4

all:	move remove.so

move:	move.o

remove.so:	remove.c
	cc -shared -o remove.so remove.c

test1:	move
	echo -e "Hello world!\n" > file1
	strace -e openat -e fault=openat:when=3:error=EACCES ./move file1 file2 2> /dev/null || (if [ $$? = 1 ]; then echo "Test 1 passed."; fi) || true

test2:	move
	echo -e "Hello world!\n" > file1
	strace -e openat -e fault=openat:when=4:error=EACCES ./move file1 file2 2> /dev/null || (if [ $$? = 2 ]; then echo "Test 2 passed."; fi) || true

test3:	move
	echo -e "Hello world!\n" > file1
	strace -e read -e fault=read:when=2:error=EIO ./move file1 file2 2> /dev/null || (if [ $$? = 6 ]; then echo "Test 3 passed."; fi) || true

test4:	move
	echo -e "Hello world!\n" > filePROTECT
	LD_PRELOAD=`pwd`/remove.so ./move filePROTECT file2 2> /dev/null
	if [ -f filePROTECT ]; then \
		echo "Test 4 passed."; \
	fi

test: test1 test2 test3 test4

clean:
	rm -rf $(TRASH)