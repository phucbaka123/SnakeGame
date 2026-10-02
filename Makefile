snakegame: main.o SnakeGame.o LinkedList.o ArrayList.o Node.o
	g++ -std=c++17 main.o SnakeGame.o LinkedList.o ArrayList.o Node.o -o snakegame

main.o: main.cpp SnakeGame.h LinkedList.h ArrayList.h Position.h
	g++ -std=c++17 -c main.cpp

SnakeGame.o: SnakeGame.cpp SnakeGame.h LinkedList.h ArrayList.h Position.h
	g++ -std=c++17 -c SnakeGame.cpp

LinkedList.o: LinkedList.cpp LinkedList.h Node.h
	g++ -std=c++17 -c LinkedList.cpp

ArrayList.o: ArrayList.cpp ArrayList.h
	g++ -std=c++17 -c ArrayList.cpp

Node.o: Node.cpp Node.h
	g++ -std=c++17 -c Node.cpp

tests: tests.o LinkedList.o ArrayList.o Node.o
	g++ -std=c++17 tests.o LinkedList.o ArrayList.o Node.o -o run_tests

tests.o: tests.cpp LinkedList.h ArrayList.h
	g++ -std=c++17 -c tests.cpp

clean:
	rm -f *.o snakegame run_tests