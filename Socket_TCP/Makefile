All:tcp_srv tcp_cli
tcp_srv:tcpprocess_srv.cc
	g++ -std=c++11 -o $@ $^
tcp_cli:tcp_cli.cc
	g++ -std=c++11 -o $@ $^
.PHONY:clean
clean:
	rm -f tcp_srv tcp_cli
