TRASH = *.o *~ o.* *.so move file*
CFLAGS=-Wall

.SILENT: test1 test2 test3 test4 test5

all:	move remove.so

move:	move.o

remove.so:	remove.c
	cc -shared -o remove.so remove.c

test1:	move
	echo "Hello world!\n" > file1
	strace -e openat -e fault=openat:when=3:error=EACCES ./move file1 file2 2> /dev/null || (if [ $$? = 1 ] && [ -f file1 ]; then echo "Test 1 passed."; fi) || true

test2:	move
	echo "Hello world!\n" > file1
	strace -e openat -e fault=openat:when=4:error=EISDIR ./move file1 file2 2> /dev/null || (if [ $$? = 2 ] && [ -f file1 ]; then echo "Test 2 passed."; fi) || true

test3:	move
	echo "Hello world!\n" > file1
	strace -e newfstatat -e fault=newfstatat:when=3:error=ENAMETOOLONG ./move file1 file2 2> /dev/null || (if [ $$? = 3 ] && [ -f file1 ] && ! [ -f file2 ]; then echo "Test 3 passed."; fi) || true

test4:	move
	echo "Hello world!\n" > file1
	strace -e read -e fault=read:when=2:error=EFBIG ./move file1 file2 2> /dev/null || (if [ $$? = 6 ] && [ -f file1 ] && ! [ -f file2 ]; then echo "Test 4 passed."; fi) || true

test5:	move
	echo "Hello world!\n" > filePROTECT
	LD_PRELOAD=`pwd`/remove.so ./move filePROTECT file2 2> /dev/null
	if [ -f filePROTECT ]; then \
		echo "Test 5 passed."; \
	fi

test: test1 test2 test3 test4 test5

clean:
	rm -rf $(TRASH)