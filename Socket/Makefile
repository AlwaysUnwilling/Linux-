All:udp_srv udp_cli
udp_srv:udp_srv.cc
	g++ -std=c++11 -o $@ $^
udp_cli:udp_cli.cc
	g++ -std=c++11 -o $@ $^
.PHONY:clean
clean:
	rm -f udp_srv udp_cli All
