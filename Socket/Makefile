Udp_Main:udp_srv udp_cli
udp_srv:udp_srv.cc
	g++ -o $@ $^
udp_cli:udp_cli.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f udp_srv udp_cli Udp_Main
