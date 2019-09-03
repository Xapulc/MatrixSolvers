//
// Created by xapulc on 03.09.19.
//

#include "Matrix.h"

Matrix::Matrix(const int n, const int m): Vector(n * m) {
    this->n = n;
    this->m = m;
}

Matrix::Matrix(const Matrix &other): Vector(other) {
    this->n = other.n;
    this->m = other.m;
}

Matrix Matrix::dot(const Matrix &other) {
    if (this->m != other.n) {
        std::cout << "Wrong shapes: (" << this->n << ", " << this->m << ") and (" <<
                     other.n << ", " << other.m << ")" << std::endl;
        exit(-1);
    }
    auto res = Matrix(this->n, other.m);

    for(int i = 0; i < this->n; i++)
        for(int j = 0; j < other.m; j++)
            for(int k = 0; k < this->m; k++)
                res.elems[i*n + j] += (*this)(i, k) * other(k, j);
    return res;
}
