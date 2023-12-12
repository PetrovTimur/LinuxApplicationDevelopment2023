GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.a *.so file*
CFLAGS=-fPIC

PARAMS0 = ""
PARAMS1 = "abc"
PARAMS2 = "abc def ghi"
PARAMS =  $(PARAMS0) $(PARAMS1) $(PARAMS2)

.SILENT: test

all:    README prog prog-a prog-so

prog:   const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	cc -L . $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L . $< -loutput -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $?

liboutput.so: fun.o const.o
	cc -shared $? -o $@

README: prog
	./$< 2> $@

fun.o:  outlib.h

test:	prog prog-a prog-so
	for param in $(PARAMS); do \
		./$(word 1, $^) $$param >> file1 2>&1; \
		./$(word 2, $^) $$param >> file2 2>&1; \
		LD_LIBRARY_PATH=`pwd` ./$(word 3, $^) $$param >> file3 2>&1; \
	done

	sed -i "s/$(word 2, $^)/$</g" file2
	sed -i "s/$(word 3, $^)/$</g" file3

	if cmp file1 file2; then \
		echo "Files 1 and 2 are identical"; \
	fi
	if cmp file2 file3; then \
		echo "Files 2 and 3 are identical"; \
	fi
	if cmp file1 file3; then \
		echo "Files 1 and 3 are identical"; \
	fi

clean:	distclean
	rm -f $(TRASH)

distclean:
	rm -rf $(GENERATES)