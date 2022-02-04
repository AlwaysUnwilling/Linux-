.PHONY:all
all:tcpserverMp tcpclientMp
tcpserverMp:tcpserverMp.cc
	g++ -o $@ $^
tcpclientMp:tcpclientMp.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f tcpserverMp tcpclientMp
