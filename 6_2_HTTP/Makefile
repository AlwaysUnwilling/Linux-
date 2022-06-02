bin=httpserver
cc=g++
#cgi=test_cgi
curr=$(shell pwd)    #在Makefile中执行shell命令
LD_FLAGS=-std=c++11 -lpthread
src=main.cc 

.PHONY:All
All:$(bin) CGI
$(bin):$(src)
	$(cc) -o $@ $^ $(LD_FLAGS)

CGI:                   #进入cgi目录生成cgi目录下的Makefile
	cd $(curr)/cgi;\      
	make;\  
	cd -                #生成完成后再返回

#$(cgi):cgi/test_cgi.cc 
#	$(cc) -o $@ $^ $(LD_FLAGS)
.PHONY:clean
clean:
	rm -f $(bin) 
	rm -rf output
	cd $(curr)/cgi;\
	make clean;\
	cd -;

.PHONY:output 
output:
	mkdir -p output 
	cp $(bin) output 
	cp -rf wwwroot output 
	#cp $(cgi) output/wwwroot
	cp ./cgi/test_cgi output/wwwroot
	cp ./cgi/mysql_conn output/wwwroot
