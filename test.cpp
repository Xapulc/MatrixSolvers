//
// Created by xapulc on 13.09.19.
//

#include <iostream>
#include <fstream>
#include "./Solver/Solver.h"

Matrix readMatrix(const char* path) {
    std::ifstream in(path);
    if (in.is_open()) {
        int n_file;
        in >> n_file;

        Matrix A = Matrix(n_file, n_file);
        for(int i = 0; i < n_file; i++)
            for(int j = 0; j < n_file; j++)
                in >> A(i, j);
        in.close();
        return A;
    } else {
        std::cout << "File not exist" << std::endl;
        exit(-1);
    }
}

Matrix generateMatrix(const int n) {
    Matrix A = Matrix(n, n);
    A(0, 0) = -1;
    for(int i = 1; i < n-1; i++)
        A(i, i) = -2;
    A(n-1, n-1) = - (n-1) * 1.0 / n;
    for(int i = 0; i < n-1; i++) {
        A(i, i+1) = 1;
        A(i+1, i) = 1;
    }
    return A;
}

Matrix generateMatrixHilbert(const int n) {
    Matrix A  = Matrix(n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            A(i, j) = 1.0 / (i + j + 1);
        }
    }
    return A;
}

int main() {
    int n_threads;
    int n;

    std::cout << "What method of input do you want to use?" << std::endl;
    std::cout << "If you want to use file, then you should write 0" << std::endl;
    std::cout << "If you want to use function, then you should write 1" << std::endl;

    int variant;
    std::cin >> variant;
    Matrix A;

    int max_iter = 1000;
    std::cout << "Enter max_iters" << std::endl;
    std::cin >> max_iter;


    if (variant == 0) {
        A = readMatrix("./res/matrix.dat");
    } else if (variant == 1) {
        std::cout << "Get order of matrix" << std::endl;
        std::cin >> n;
        if (n <= 0) {
            std::cout << "There is bad shape: (" << n << ", " << n << ")" << std::endl;
            exit(-1);
        }
        A = generateMatrix(n);
    } else {
        std::cout << "Bad input" << std::endl;
        exit(-1);
    }

    std::cout << "Eigenvalues: " << std::endl;
    (Solver::findEigenvalues(A, max_iter)).print();
    std::cout << "Trace: " << A.trace() << std::endl;
    std::cout << "Residual: " << A.residual() << std::endl;
}