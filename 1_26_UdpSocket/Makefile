
.PHONY:all
all:udpserver udpclient
udpserver:udpserver.cc
	g++ -o $@ $^ -std=c++11;
udpclient:udpclient.cc
	g++ -o $@ $^ -std=c++11;
.PHONY:clean
clean:
	rm -f udpserver udpclient
