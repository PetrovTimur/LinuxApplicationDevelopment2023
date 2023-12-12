TRASH = *.o file* *~ range
CFLAGS = -g -o0

.SILENT: test

all:	range

range:	range.o

gdb1:	range
	gdb --batch --quiet -x gdb-script1 --args ./$< | grep @@@ | cut -c 4- > file1

gdb2:	range
	gdb --batch --quiet -x gdb-script2 --args ./$< | grep @@@ | cut -c 4- > file2

test:	gdb1 gdb2
	echo "1, 12, 1\n5\n10" > file_ans1
	echo "-100, 100, 3" > file_ans2 && seq -19 3 2 >> file_ans2

	if cmp file1 file_ans1; then \
		echo "Test 1 passed."; \
	fi

	if cmp file2 file_ans2 ; then \
		echo "Test 2 passed."; \
	fi

clean:	
	rm -f $(TRASH)