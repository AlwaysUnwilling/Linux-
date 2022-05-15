bin=httpserver
cc=g++
cgi=test_cgi
curr=$(shell pwd)    #在Makefile中执行shell命令
LD_FLAGS=-std=c++11 -lpthread
src=main.cc 

All:$(bin) $(cgi)
.PHONY:All
$(bin):$(src)
	$(cc) -o $@ $^ $(LD_FLAGS)
$(cgi):cgi/test_cgi.cc 
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -f $(bin) $(cgi)
	rm -rf output 
.PHONY:output 
output:
	mkdir -p output 
	cp $(bin) output 
	cp -rf wwwroot output 
	cp $(cgi) output/wwwroot
