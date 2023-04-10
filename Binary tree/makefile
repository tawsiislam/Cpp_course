make bintree:
	g++ bintree.cpp
make all:
	python $HOME/cxxtest-4.4/bin/cxxtestgen --error-printer -o testtree.cpp testtree.h
	g++ -o mytest_runner testtree.cpp -I $HOME/cxxtest-4.4
	g++ -o testBalance.exe testbalance.cpp
make tests:
	./mytest_runner
	./testBalance.exe
make unittest:
	./mytest_runner
make testbalance:
	./testBalance.exe