bin=maze_gen

all: maze0 maze1 maze2 maze3

maze0: maze.c
	cc maze.c -o maze0

maze1.c: maze.c custom_size.patch
	patch maze.c -i custom_size.patch -o maze1.c

maze1: maze1.c
	cc maze1.c -o maze1

maze2.c: maze1.c custom_chars.patch
	patch maze1.c -i custom_chars.patch -o maze2.c

maze2: maze2.c
	cc maze2.c -o maze2

maze3.c: maze2.c custom_seed.patch
	patch maze2.c -i custom_seed.patch -o maze3.c

maze3: maze3.c
	cc maze3.c -o maze3

run: maze0 maze1 maze2 maze3
	./maze0
	./maze1 3
	./maze1 5
	./maze2 " *" 3
	./maze2 "_x" 6
	./maze3 464 "_x" 7
	./maze3 1568 " *" 10

clean:
	rm maze?
	rm maze?.c
