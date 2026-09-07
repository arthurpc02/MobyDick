.PHONY: all clean

CXX = g++
CXX_FLAGS = -std=c++17 -Wall

ifdef DEBUG
	CXX_FLAGS += -g
endif

main: main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp -o main

clean:
	rm -f main
