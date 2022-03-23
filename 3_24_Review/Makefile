FLAG=-std=c++11
.PHONY:all 
all:server client 
server:server.cc tcpServer.cc 
	g++ -o $@ $^ $(FLAG)
client:client.cc tcpClient.cc
	g++ -o $@ $^ $(FLAG)
.PHONY:clean
clean:
	rm -f server client 
