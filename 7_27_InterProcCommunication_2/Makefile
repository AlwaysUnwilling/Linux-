.PHONY:all
all:client server 
server:server.c
	g++ -o $@ $^
client:client.c 
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -f server client 
