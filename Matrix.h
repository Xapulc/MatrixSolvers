//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_MATRIX_H
#define SEMINAR_MATRIX_H


#include "Vector.h"

class Matrix: public Vector {
public:
    Matrix() = default;
    Matrix(int n, int m);
    Matrix(const Matrix &other);

    double operator()(const int i, const int j) const { return (*this)[i * m + j]; }
    Matrix dot(const Matrix &other);

    ~Matrix() = default;
protected:
    int n{0};
    int m{0};
private:
    using Vector::len;
    using Vector::operator[];
};


#endif //SEMINAR_MATRIX_H
