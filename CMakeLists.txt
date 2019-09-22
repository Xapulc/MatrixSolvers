cmake_minimum_required(VERSION 3.13)
project(LinearSolvers)

set(CMAKE_CXX_STANDARD 14)

add_executable(LinearSolvers main.cpp test.cpp Vectors/Matrix.cpp Vectors/Matrix.h Vectors/BoolVector.cpp Vectors/BoolVector.h Solver/Solver.cpp Solver/Solver.h)