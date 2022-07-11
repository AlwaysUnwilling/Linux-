
FLAG=-std=c++11 -I /home/Lg/ThirdPart_jieba/include/ -I /home/Lg/ThirdPart_jieba/deps -I /home/Lg/ThirdPart_jieba/ -lpthread  -I ../searcher/ -L.  -lsearcher
 

http_server:http_server.cpp
	g++ -o $@ $^ $(FLAG)

.PHONY:clean
clean:
	rm -f http_server 
