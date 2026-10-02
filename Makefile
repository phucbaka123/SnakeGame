CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Template classes: their .cpp files are #included by the headers,
# so they are NOT compiled separately (only listed as dependencies).
LIST_FILES = ArrayList.h ArrayList.cpp LinkedList.h LinkedList.cpp Node.h Node.cpp Position.h

all: snakegame run_tests

snakegame: main.o SnakeGame.o
	$(CXX) $(CXXFLAGS) main.o SnakeGame.o -o snakegame

main.o: main.cpp SnakeGame.h $(LIST_FILES)
	$(CXX) $(CXXFLAGS) -c main.cpp

SnakeGame.o: SnakeGame.cpp SnakeGame.h $(LIST_FILES)
	$(CXX) $(CXXFLAGS) -c SnakeGame.cpp

run_tests: tests.o
	$(CXX) $(CXXFLAGS) tests.o -o run_tests

tests.o: tests.cpp $(LIST_FILES)
	$(CXX) $(CXXFLAGS) -c tests.cpp

clean:
	rm -f *.o snakegame run_tests snakegame.exe run_tests.exe

tests: run_tests

.PHONY: all tests clean