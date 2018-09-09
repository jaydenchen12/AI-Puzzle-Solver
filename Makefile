hw1:  AIHW1.o PuzzleMove.o
	g++ AIHW1.o PuzzleMove.o -o hw1

AIHW1.o: AIHW1.cpp
	g++ -c -std=c++11  AIHW1.cpp

PuzzleMove.o: PuzzleMove.cpp
	g++ -c PuzzleMove.cpp

clean:
	rm *.o hw1
