COMPILER_FLAGS= -std=c++11 

all:
	g++ $(COMPILER_FLAGS) kruskal.cpp -o graph

test: all
	sh tests/testall.sh	

test_random: all
	python tests/test_maker.py $(TESTS)
	sh random_tests/testall.sh
	mv random_tests/results.txt analysis/results.txt

clean:
	rm -f graph 
	rm -f random_tests/*.in 
