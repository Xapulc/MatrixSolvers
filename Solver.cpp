//
// Created by xapulc on 03.09.19.
//

#include "Solver.h"

Vector Solver::solve(const Matrix &A, const Vector &bias, const char *method) const {
    if (method == "gaussMainElementColumn")
        return gaussMainElementColumn(A, bias);
    else
        return gaussMainElementColumn(A, bias);
}

Vector Solver::gaussMainElementColumn(const Matrix &givenA, const Vector &givenBias) const {
    Matrix A = Matrix(givenA);
    Vector bias = Vector(givenBias);

    return Vector(0);
}
