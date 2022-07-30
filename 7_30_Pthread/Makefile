
.PHONY:ALL
ALL:GrabTicket PthreadCond
PthreadCond:PthreadCond.cc
	g++ -o $@ $^ -lpthread	
GrabTicket:GrabingTickets.c
	gcc -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f GrabTicket PthreadCond
