.PHONY:all
all:tcpserver tcpclient
tcpserver:tcpserver.cc
	g++ -o $@ $^
tcpclient:tcpclient.cc
	g++ -o $@ $^
.PHONY: clean
clean:
	rm -f tcpserver tcpclient
