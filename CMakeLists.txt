cmake_minimum_required(VERSION 3.13)
project(Seminar)

set(CMAKE_CXX_STANDARD 14)

add_executable(Seminar Solver.cpp Solver.h Vector.cpp Vector.h Matrix.cpp Matrix.h)