cmake_minimum_required(VERSION 3.13)
project(Seminar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Seminar Solver/Solver.cpp Solver/Solver.h LinearEssences/Vector.h LinearEssences/Matrix.cpp LinearEssences/Matrix.h LinearEssences/DoubleVector.cpp LinearEssences/DoubleVector.h LinearEssences/IntegerVector.cpp LinearEssences/IntegerVector.h main.cpp Threads/Threads.cpp Threads/Threads.h)