CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter

all: test main

test: test.o AST.o Node.o Stack.o
	${CXX} $(CXXFLAGS) -o $@ $+

main: main.o AST.o Node.o Stack.o
	${CXX} $(CXXFLAGS) -o $@ $+

test.o: test.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

AST.o: AST.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

Node.o: Nodes.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

Stack.o: Stack.cpp
	${CXX} $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o test main