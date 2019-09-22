//
// Created by xapulc on 22.09.19.
//

#include "Matrix.h"
#include "../Solver/Solver.h"

void Matrix::checkSize(const int size) {
    if (size <= 0) {
        std::cout << "Wrong size: " << size << std::endl;
        exit(-1);
    }
}

void Matrix::createElems(const int len) {
    if ((this->elems = DoubleVector(static_cast<unsigned long>(len))).empty()) {
        std::cout << "Cannot allocate enough memory. Len: " << len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++)
        elems[i] = 0;
}

Matrix::Matrix(const int len) {
    checkSize(len);
    this->h = len;
    this->w = 1;
    createElems(len);
}

Matrix::Matrix(const int h, const int w) {
    checkSize(h);
    checkSize(w);
    this->h = h;
    this->w = w;
    createElems(h*w);
}

Matrix &Matrix::operator=(const Matrix &other) {
    h = other.h;
    w = other.w;
    createElems(h*w);
    for(int i = 0; i < h * w; i++)
        elems[i] = other.elems[i];
    return *this;
}

double &Matrix::operator[](const int i) {
    return elems[i];
}

double Matrix::operator[](const int i) const {
    return elems[i];
}

double &Matrix::operator()(const int i, const int j) {
    return elems[i*w + j];
}

double Matrix::operator()(const int i, const int j) const {
    return elems[i*w + j];
}

void Matrix::checkShape(const Matrix& left, const Matrix& right) {
    if ((left.h != right.h) || (left.w != right.w)) {
        std::cout << "Wrong shapes: (" << left.h << ", " << left.w <<
                  ") and (" << right.h << ", " << right.w << ")" << std::endl;
        exit(-1);
    }
}

Matrix& Matrix::operator+=(const Matrix &other) {
    checkShape(*this, other);
    for(int i = 0; i < h*w; i++)
        elems[i] += other.elems[i];
    return *this;
}

Matrix Matrix::operator+(const Matrix &other) const {
    auto res = *this;
    res += other;
    return res;
}

Matrix& Matrix::operator-=(const Matrix &other) {
    checkShape(*this, other);
    for(int i = 0; i < h*w; i++)
        elems[i] -= other.elems[i];
    return *this;
}

Matrix Matrix::operator-(const Matrix &other) const {
    auto res = *this;
    res -= other;
    return res;
}

Matrix& Matrix::operator*=(const Matrix &other) {
    checkShape(*this, other);
    for(int i = 0; i < h*w; i++)
        elems[i] *= other.elems[i];
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    auto res = *this;
    res *= other;
    return res;
}

Matrix& Matrix::operator/=(const Matrix &other) {
    checkShape(*this, other);
    for(int i = 0; i < h*w; i++)
        elems[i] /= other.elems[i];
    return *this;
}

Matrix Matrix::operator/(const Matrix &other) const {
    auto res = *this;
    res /= other;
    return res;
}

Matrix& Matrix::operator*=(const double a) {
    for(int i = 0; i < h*w; i++)
        elems[i] *= a;
    return *this;
}

Matrix Matrix::operator*(const double a) const {
    auto res = *this;
    res *= a;
    return res;
}

Matrix& Matrix::operator/=(const double a) {
    for(int i = 0; i < h*w; i++)
        elems[i] /= a;
    return *this;
}

Matrix Matrix::operator/(const double a) const {
    auto res = *this;
    res /= a;
    return res;
}

Matrix Matrix::dot(const Matrix &other) const {
    if (this->w != other.h) {
        std::cout << "Wrong shapes: (" << this->h << ", " << this->w << ") and (" <<
                  other.h << ", " << other.w << ")" << std::endl;
        exit(-1);
    }
    auto res = Matrix(this->h, other.w);

    for(int i = 0; i < this->h; i++)
        for(int j = 0; j < other.w; j++)
            for(int k = 0; k < this->w; k++)
                res(i, j) += (*this)(i, k) * other(k, j);
    return res;
}

Matrix Matrix::eye(const int n) {
    auto res = Matrix(n, n);
    for(int i = 0; i < n; i++)
        res(i, i) = 1;
    return res;
}

const int Matrix::arg_module_max_line(int i, int axis, const BoolVector &freeElements) const {
    int arg = 0;
    double max_elem = 0;

    if (freeElements.getLength() > 0) {
        auto freeElem = freeElements.getFirstFalse();
        if (freeElem == -1) {
            std::cout << "There isn`t free element" << std::endl;
            exit(-1);
        }
        arg = freeElem;
    }

    if (axis == 0) {
        max_elem = fabs((*this)(arg, i));
        if (freeElements.getLength() == 0) {
            for (int j = arg + 1; j < h; j++)
                if (fabs((*this)(j, i)) > max_elem) {
                    arg = j;
                    max_elem = fabs((*this)(j, i));
                }
        } else {
            if (h != freeElements.getLength()) {
                std::cout << "Wrong shape in free_vector: (" << h << ", " << freeElements.getLength()
                          << ")" << std::endl;
                exit(-1);
            }
            for (int j = arg + 1; j < h; j++)
                if ((fabs((*this)(j, i)) > max_elem) && !freeElements[j]) {
                    arg = j;
                    max_elem = fabs((*this)(j, i));
                }
        }
    } else {
        max_elem = fabs((*this)(i, arg));
        if (freeElements.getLength() == 0) {
            for (int j = arg + 1; j < w; j++)
                if (fabs((*this)(i, j)) > max_elem) {
                    arg = j;
                    max_elem = fabs((*this)(i, j));
                }
        } else {
            if (w != freeElements.getLength()) {
                std::cout << "Wrong shape in free_vector: (" << w << ", " << freeElements.getLength()
                          << ")" << std::endl;
                exit(-1);
            }
            for (int j = arg + 1; j < w; j++)
                if ((fabs((*this)(i, j)) > max_elem) && !freeElements[j]) {
                    arg = j;
                    max_elem = fabs((*this)(i, j));
                }
        }
    }

    return arg;
}

void Matrix::print() const {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++)
            std::cout << (*this)(i, j) << " ";
        std::cout << std::endl;
    }
}

double Matrix::residual() const {
    double sum = 0;
    for(int i = 0; i < h*w; i++)
        sum += elems[i] * elems[i];
    return sum;
}

Matrix Matrix::t() const {
    Matrix res = Matrix(w, h);
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            res(j, i) = (*this)(i, j);
    return res;
}

double Matrix::trace() const {
    double trace = 0;
    for(int i = 0; i < ((h > w) ? w : h); i++)
        trace += (*this)(i, i);
    return trace;
}

Matrix Matrix::inverse(const int n_threads, const char *method) const {
    const Matrix old = Matrix(*this);
    auto res = Matrix(h, w);
    auto results = std::vector<Matrix>((unsigned long) w);
    auto futures = std::vector<std::future<Matrix>>((unsigned long) n_threads);

    for(int j = 0; j < w; j++) {
        Matrix bias = Matrix(h);
        bias[j] = 1;
        futures[j % n_threads] = std::async(std::launch::async, Solver::solve, old, bias, method);

        if ((j + 1) % n_threads == 0)
            for(int k = 0; k < n_threads; k++)
                results[j - (n_threads-1) + k] = futures[k].get();
        else if (j == w - 1)
            for(int k = 0; k < w % n_threads; k++)
                results[j - ((w - 1) % n_threads) + k] = futures[k].get();
    }

    for(int j = 0; j < w; j++) {
        auto bias = results[j];
        for(int i = 0; i < h; i++) {
            res(i, j) = bias[i];
        }
    }

    return res;
}
