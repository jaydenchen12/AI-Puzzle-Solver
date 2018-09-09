hw1:  AISolver.o PuzzleMove.o
	g++ AISolver.o PuzzleMove.o -o solver

AISolver.o: AISolver.cpp
	g++ -c -std=c++11  AISolver.cpp

PuzzleMove.o: PuzzleMove.cpp
	g++ -c PuzzleMove.cpp

clean:
	rm *.o solver
