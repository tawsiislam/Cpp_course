all:
	python $HOME/cxxtest-4.4/bin/cxxtestgen --error-printer -o mytest.cpp test_complex.h
	g++ -o mytest mytest.cpp -I $HOME/cxxtest-4.4
	
tests:
	./mytest