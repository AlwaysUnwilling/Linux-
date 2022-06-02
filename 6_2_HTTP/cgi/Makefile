
.PHONY:all
all:test_cgi mysql_conn 

test_cgi:test_cgi.cc 
	g++ -o $@ $^ -std=c++11
mysql_conn:mysql_conn.cc 
	g++ -o $@ $^ -std=c++11 -I include -L lib -lmysqlclient -lpthread -ldl -static

.PHONY:clean
clean:
	rm -f mysql_conn test_cgi 

