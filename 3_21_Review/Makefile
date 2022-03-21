.PHONY:all
all:sigset main  
main:main.cc
	g++ -o $@ $^  -lpthread -std=c++11
sigset:sigset.c
	gcc -o $@ $^  -std=gnu99
.PHONY:clean
clean:
	rm -f sigset main
