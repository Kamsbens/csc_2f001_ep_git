CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

all: ast

ast: main.o ast.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o ast.o: ast.h

clean:
	rm -f *.o ast

.PHONY: all clean
