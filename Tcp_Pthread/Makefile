ALL:tcp_pthread_srv tcp_pthread_cli
tcp_pthread_srv:tcp_pthread_srv.cc
	g++ -o $@ $^ -lpthread
tcp_pthread_cli:tcp_pthread_cli.cc
	g++ -o $@ $^ -lpthread
.PHONY:clean
clean:
	rm -f tcp_pthread_srv tcp_pthread_cli
