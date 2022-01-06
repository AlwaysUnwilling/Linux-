.PHONY:All
All:server client
server:server.c
	g++ -o $@ $^
client:client.c
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f server client
