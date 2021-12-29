path=$(shell pwd)
mytest:mytest.c
	gcc -o $@ $^ -I$(path)/mylib/include/ -L$(path)/mylib/lib/ -lmymath
.PHONY:clean
clean:
	rm -f mytest
