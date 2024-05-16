CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
OPTFLAGS=-O3 -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter

all: main

main: main.o Counter.o List.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Counter.h List.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Counter.o: Counter.cpp Counter.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

List.o: List.cpp List.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f main *.o
