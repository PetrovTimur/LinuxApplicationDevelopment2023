TRASH = *.o *~ maze[1-3]* maze

all:	run

maze:	patch maze.c maze1.c maze2.c maze3.c
	cc -o maze maze.c
	cc -o maze1 maze1.c
	cc -o maze2 maze2.c
	cc -o maze3 maze3.c

copy:	maze.c
	cp maze.c maze1.c
	cp maze.c maze2.c
	cp maze.c maze3.c

patch:	copy
	patch maze1.c < patch1.diff
	patch maze2.c < patch2.diff
	patch maze3.c < patch3.diff

run:	maze
	./maze
	./maze1 8
	./maze2 ' @' 5
	./maze3 12 '.#' 4
	./maze3 11 '.#' 4
	./maze3 12 '.#' 4

clean:
	rm -f $(TRASH)