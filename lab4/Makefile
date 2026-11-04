CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g

all: bilbao

bilbao: main.o location.o shortest_path.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: location.h shortest_path.h
location.o: location.h
shortest_path.o: shortest_path.h location.h

clean:
	rm -f *.o bilbao

.PHONY: all clean
