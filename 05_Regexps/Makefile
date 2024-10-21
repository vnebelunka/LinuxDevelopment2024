FLAGS=-O0 -g
exe=gcc

all: esub test

esub: esub.c
	${exe} $^ ${FLAGS} -o $@

.PHONY: test
test: esub
	cal | ./esub "*" "1" > a.txt
	cal | sed -E "s/1/*/" > b.txt
	cmp a.txt b.txt
	cal | ./esub "*" "[0-9]" > a.txt
	cal | sed -E "s/[0-9]/*/" > b.txt
	cmp a.txt b.txt
	echo "_abcdef_" | ./esub "\3\2\1" "(a)b(c)d(e)" > a.txt
	echo "_abcdef_" | sed -E "s/(a)b(c)d(e)/\3\2\1/" > b.txt
	cmp a.txt b.txt
	echo "DabcE" | ./esub "\1_\1" "a(b)c" > a.txt
	echo "DabcE" | sed -E "s/a(b)c/\1_\1/" > b.txt
	cmp a.txt b.txt
	echo "_abcdef_" | ./esub "\3\3\3" "(a)b(c)d(e)" > a.txt
	echo "_abcdef_" | sed -E "s/(a)b(c)d(e)/\3\3\3/" > b.txt
	cmp a.txt b.txt

.PHONY: clean
clean:
	rm esub
	rm a.txt b.txt
