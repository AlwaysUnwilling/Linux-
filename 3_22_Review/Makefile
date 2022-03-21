.PHONY:all
all:main thread 
thread:ThreadPool.cc 
	g++ -o $@ $^ -lpthread -std=c++11

main:main.cc
	g++ -o $@ $^ -lpthread -std=c++11
.PHONY:clean
clean:
	rm -f main thread
