ALL:udp_cli udp_srv
udp_cli:udp_cli_c.c
	gcc -o $@ $^
udp_srv:udp_srv_c.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f All udp_cli udp_srv
