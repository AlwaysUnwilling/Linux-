.PHONY:all
all:main main1

main:VarTempParameters.cc
	g++ -o $@ $^
main1:STL_emplace_back.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f main main1
