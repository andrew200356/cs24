CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

.PHONY: all clean

all: Tree test

# Node
Node.o: Node.cpp Node.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

# Tree
Tree.o: Tree.cpp Tree.h Node.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Tree: Tree.o Node.o
	${CXX} $(CXXFLAGS) -o $@ $+

# test
test.o: test.cpp Tree.h Node.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

test: test.o Tree.o Node.o
	${CXX} $(CXXFLAGS) -o $@ $+


clean:
	rm -f Node.o Tree.o Tree test.o test
