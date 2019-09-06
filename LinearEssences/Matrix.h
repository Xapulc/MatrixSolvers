//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_MATRIX_H
#define SEMINAR_MATRIX_H


#include "IntegerVector.h"
#include "DoubleVector.h"

class Matrix: public DoubleVector {
public:
    Matrix() = default;
    Matrix(int n, int m);
    Matrix(const Matrix &other);

    static Matrix eye(int n);
    const double operator()(const int i, const int j) const { return (*this)[i * m + j]; }
    Matrix dot(const Matrix &other);
    const int arg_module_max_line(int i, int axis=0, const IntegerVector &free_elements=IntegerVector()) const;
    const int getShape(const int axis) const { return (axis == 0) ? n : m; }
    Matrix& inverse(const char* method = "gaussMainElementColumn");
    void print() const;

    ~Matrix() = default;
protected:
    int n{0};
    int m{0};
private:
    using Vector::len;
    using Vector::operator[];
};


#endif //SEMINAR_MATRIX_H
