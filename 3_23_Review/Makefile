.PHONY:all
all:server client 
server:server.cc udpServer.cc 
	g++ -o $@ $^ -std=c++11
client:client.cc udpClient.cc 
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f server client


