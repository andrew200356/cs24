CXX=g++
CXXFLAGS=-g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
# CXXFLAGS support for -g debugging level, helpful for debugging
OPTFLAGS=-O3 -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
# OPTFLAGS support for -O3 optimization level which is required for the lab

# just change the $(OPTFLAGS) to $(CXXFLAGS) to compile with debugging flags

all: main

main: main.o Counter.o List.o Index.o Iterator.o
	$(CXX) $(OPTFLAGS) -o $@ $^

main.o: main.cpp Counter.h List.h
	$(CXX) $(OPTFLAGS) -c -o $@ $<

Counter.o: Counter.cpp Counter.h
	$(CXX) $(OPTFLAGS) -c -o $@ $<

List.o: List.cpp List.h
	$(CXX) $(OPTFLAGS) -c -o $@ $<

Index.o: Index.cpp Index.h
	$(CXX) $(OPTFLAGS) -c -o $@ $<

Iterator.o: Iterator.cpp
	$(CXX) $(OPTFLAGS) -c -o $@ $<

valgrind: main 
	valgrind --leak-check=full ./main

clean:
	rm -f main *.o
