//
// Created by xapulc on 03.09.19.
//

#include <cmath>
#include "Matrix.h"
#include "../Solver/Solver.h"

Matrix::Matrix(const int n, const int m): DoubleVector(n * m) {
    this->n = n;
    this->m = m;
}

Matrix::Matrix(const Matrix &other): DoubleVector(other) {
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
                res.elems[i*m + j] += (*this)(i, k) * other(k, j);
    return res;
}

const int Matrix::arg_module_max_line(const int i, const int axis, const IntegerVector &free_elements) const {
    int arg = 0;
    double max_elem = 0;
    if (free_elements.getLen() > 0) {
        bool flag_free_exist = false;
        for (int j = 0; j < free_elements.getLen(); j++) {
            if (free_elements[j] == 0) {
                flag_free_exist = true;
                arg = j;
                break;
            }
        }
        if (!flag_free_exist) {
            std::cout << "There isn`t free element" << std::endl;
            exit(-1);
        }
    }

    if (axis == 0) {
        max_elem = fabs((*this)(arg, i));
        if (free_elements.getLen() == 0) {
            for (int j = arg + 1; j < n; j++)
                if (fabs((*this)(j, i)) > max_elem) {
                    arg = j;
                    max_elem = fabs((*this)(j, i));
                }
        } else {
            if (n != free_elements.getLen()) {
                std::cout << "Wrong shape in free_vector: (" << n << ", " << free_elements.getLen()
                          << ")" << std::endl;
                exit(-1);
            }
            for (int j = arg + 1; j < n; j++)
                if ((fabs((*this)(j, i)) > max_elem) && (free_elements[j] == 0)) {
                    arg = j;
                    max_elem = fabs((*this)(j, i));
                }
        }
    } else {
        max_elem = fabs((*this)(i, arg));
        if (free_elements.getLen() == 0) {
            for (int j = arg + 1; j < m; j++)
                if (fabs((*this)(i, j)) > max_elem) {
                    arg = j;
                    max_elem = fabs((*this)(i, j));
                }
        } else {
            if (m != free_elements.getLen()) {
                std::cout << "Wrong shape in free_vector: (" << m << ", " << free_elements.getLen()
                          << ")" << std::endl;
                exit(-1);
            }
            for (int j = arg + 1; j < m; j++)
                if ((fabs((*this)(i, j)) > max_elem) && (free_elements[j] == 0)) {
                    arg = j;
                    max_elem = fabs((*this)(i, j));
                }
        }
    }

    return arg;
}

Matrix& Matrix::inverse(const char* method) {
    const Matrix old = Matrix(*this);
    for(int j = 0; j < m; j++) {
        DoubleVector bias = DoubleVector(n);
        bias.elems[j] = 1;
        const DoubleVector result = Solver::solve(old, bias, method);
        for(int i = 0; i < n; i++) {
            this->elems[i*m + j] = result[i];
        }
    }
    return *this;
}

void Matrix::print() const {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            std::cout << (*this)(i, j) << " ";
        std::cout << std::endl;
    }
}

Matrix Matrix::eye(const int n) {
    Matrix E = Matrix(n, n);
    for(int i = 0; i < n; i++) {
        E.elems[i * (n+1)] = 1;
    }
    return E;
}