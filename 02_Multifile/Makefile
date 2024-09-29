CFLAGS = -fPIC
TRASH = *.o *~ o.* *.a *.so  

BINARIES = prog prog-a prog-so

input = a
input3 = a b c

all: test

%.o:    %.c
	cc $< -c -o $@ $(CFLAGS)

liboutput_static.a: fun.o const.o
	ar rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@ 

prog: prog.o fun.o const.o
	cc -o $@ $^

prog-a: prog.o liboutput_static.a
	cc -o $@ $^

prog-so: prog.o liboutput.so
	cc -L./ -l output  prog.o -o $@  

test: prog prog-a prog-so
# 0
	./prog > prog0.txt 2>&1
	./prog-a > prog-a0.txt 2>&1
	LD_LIBRARY_PATH=$(shell pwd) ./prog-so > prog-so0.txt 2>&1
	cmp prog0.txt prog-a0.txt
	cmp prog0.txt prog-so0.txt
# 1
	./prog $(input) > prog1.txt 2>&1
	./prog-a $(input) > prog-a1.txt 2>&1
	LD_LIBRARY_PATH=$(shell pwd) ./prog-so $(input) > prog-so1.txt 2>&1
	cmp prog1.txt prog-a1.txt
	cmp prog1.txt prog-so1.txt
# 3
	./prog $(input3) > prog3.txt 2>&1
	./prog-a $(input3) > prog-a3.txt 2>&1
	LD_LIBRARY_PATH=$(shell pwd) ./prog-so $(input3) > prog-so3.txt 2>&1
	cmp prog3.txt prog-a3.txt
	cmp prog3.txt prog-so3.txt

clean:
	rm -f $(TRASH)
	rm -f $(BINARIES)
	rm prog*.txt