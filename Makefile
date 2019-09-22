CC=g++
ADD=-std=c++14
method=main
target=solve

all: $(method) clean

$(method): BoolVect Matrix LSolver
	$(CC) -pthread -o $(target) $(method).cpp BoolVector.o Matrix.o Solver.o $(ADD) -lm

BoolVect: Vectors/BoolVector.cpp
	$(CC) -c Vectors/BoolVector.cpp $(ADD)

Matrix: Vectors/Matrix.cpp
	$(CC) -c Vectors/Matrix.cpp $(ADD)

LSolver: Solver/Solver.cpp
	$(CC) -c Solver/Solver.cpp $(ADD)

clean:
	rm -f *.o

clean_target:
	rm $(target)
