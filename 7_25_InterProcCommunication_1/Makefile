
.PHONY:all
all:anoPipe pipClient pipServer 
anoPipe:anonymoPipe.c
	gcc -o $@ $^
pipClient: pipclient.c
	gcc -o $@ $^
pipServer:pipserver.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f anoPipe pipClient pipServer myfifo
