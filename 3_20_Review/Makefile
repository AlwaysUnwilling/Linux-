.PHONY:all
all: server client pipe shmServer shmClient
client:fifoclient.c
	gcc -o $@ $^
server:fifoserver.c
	gcc -o $@ $^
pipe:pipe.c
	gcc -o $@ $^
shmServer:shmServer.c
	gcc -o $@ $^
shmClient:shmClient.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f client server pipe fifo shmServer shmClient
