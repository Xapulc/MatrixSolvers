CC=g++
ADD=-std=c++14
target=solve

all: main clean

main: IntVect DoubleVect Matrix LSolver
	$(CC) -pthread -o $(target) main.cpp IntegerVector.o DoubleVector.o Matrix.o Solver.o $(ADD) -lm

IntVect: LinearEssences/IntegerVector.cpp
	$(CC) -c LinearEssences/IntegerVector.cpp $(ADD)

DoubleVect: LinearEssences/DoubleVector.cpp
	$(CC) -c LinearEssences/DoubleVector.cpp $(ADD)

Matrix: LinearEssences/Matrix.cpp
	$(CC) -c LinearEssences/Matrix.cpp $(ADD)

LSolver: Solver/Solver.cpp
	$(CC) -c Solver/Solver.cpp $(ADD)

clean:
	rm -f *.o

clean_target:
	rm $(target)
