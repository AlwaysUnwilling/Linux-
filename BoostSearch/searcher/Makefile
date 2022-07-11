FLAG=-std=c++11 -I /home/Lg/ThirdPart_jieba/include/  -I /home/Lg/ThirdPart_jieba/deps/ -lboost_filesystem -lboost_system -ljsoncpp

.PHONY:ALL
ALL:search libsearcher.so 
search:searcher.cpp test.cpp 
	g++ -o $@ $^ $(FLAG)

libsearcher.so:searcher.cpp searcher.h
	g++ -o $@ $^ -shared -fPIC $(FLAG)

.PHONY:clean;
clean:
	rm -f search libsearcher.so 
