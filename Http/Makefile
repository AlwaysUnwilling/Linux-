All:http tcp_cli
http:http_srv.cc
	g++ -o $@ $^
tcp_cli:tcp_cli.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f http tcp_cli
