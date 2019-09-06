//
// Created by xapulc on 06.09.19.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include "./Solver/Solver.h"

Matrix readMatrix(const int n, const char* path) {
    std::ifstream in(path);
    if (in.is_open()) {
        int n_file;
        in >> n_file;
        if (n != n_file) {
            std::cout << "Bad shape in file: " << n_file << std::endl;
            in.close();
            exit(-1);
        }

        Matrix A = Matrix(n, n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                in >> A.elems[i*n + j];
        in.close();
        return A;
    } else {
        std::cout << "File not exist" << std::endl;
        exit(-1);
    }
}

int main() {
    int n;
    std::cout << "Get shape of matrix" << std::endl;
    std::cin >> n;
    if (n <= 0) {
        std::cout << "There is bad shape: (" << n << ", " << n << ")" << std::endl;
        exit(-1);
    }
    std::cout << "What method of input do you want to use?" << std::endl;
    std::cout << "If you want to use file, then you should write 0" << std::endl;
    std::cout << "If you want to use function, then you should write 1" << std::endl;

    int variant;
    std::cin >> variant;
    Matrix A;

    if (variant == 0) {
        A = readMatrix(n, "../res/matrix.dat");
    } else if (variant == 1) {

    } else {
        std::cout << "Bad input" << std::endl;
        exit(-1);
    }
//    A.print();
    Matrix B = A;
    clock_t start_time =  clock();
    B.inverse();
    clock_t end_time =  clock();
    std::cout << "Inversed matrix: " << std::endl;
    B.print();
    std::cout << "Residual: " << (A.dot(B) - Matrix::eye(n)).residual() << std::endl;
    std::cout << "Time work: " << end_time - start_time << " ms" << std::endl;
}