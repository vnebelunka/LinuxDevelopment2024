FLAGS=-O0 -g
exe=gcc

all: range test

range: range.c
	${exe} $^ ${FLAGS} -o $@

res1="\
@@@ N=12, M=1, S=1, i=0\n\
@@@ N=12, M=1, S=1, i=5\n"

res2="\
@@@ N=100, M=-100, S=3, i=-19\n\
@@@ N=100, M=-100, S=3, i=-16\n\
@@@ N=100, M=-100, S=3, i=-13\n\
@@@ N=100, M=-100, S=3, i=-10\n\
@@@ N=100, M=-100, S=3, i=-7\n\
@@@ N=100, M=-100, S=3, i=-4\n\
@@@ N=100, M=-100, S=3, i=-1\n\
@@@ N=100, M=-100, S=3, i=2\n" 

.PHONY: test
test: range
	gdb --quiet --batch --command=test1.gdb range | grep @@@ > a1.txt
	printf ${res1} > b1.txt
	cmp a1.txt b1.txt
	gdb --quiet --batch --command=test2.gdb range | grep @@@ > a2.txt
	printf ${res2} > b2.txt
	cmp a2.txt b2.txt

.PHONY: clean
clean:
	rm range
	rm a1.txt a2.txt b1.txt b2.txt
