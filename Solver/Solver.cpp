//
// Created by xapulc on 03.09.19.
//

#include "Solver.h"

DoubleVector Solver::solve(const Matrix &A, const DoubleVector &bias, const char *method) {
    if (A.getShape(0) != bias.getLen()) {
        std::cout << "Wrong length of bias: " << A.getShape(0) << ", " << bias.getLen() << std::endl;
        exit(-1);
    }

    if (method == "gaussMainElementColumn")
        return gaussMainElementColumn(A, bias);
    else
        return gaussMainElementColumn(A, bias);
}

DoubleVector Solver::gaussMainElementColumn(const Matrix &givenA, const DoubleVector &givenBias) {
    Matrix A = Matrix(givenA);
    DoubleVector bias = DoubleVector(givenBias);
    int n = givenA.getShape(0);
    int m = givenA.getShape(1);
    if (n != m) {
        std::cout << "There is non-square matrix, shapes: (" << n << ", " << m << std::endl;
        exit(-1);
    }
    IntegerVector main_elements = IntegerVector(m);
    IntegerVector free_elements = IntegerVector(m);
    for(int col = 0; col < m; col++)
        main_elements.elems[col] = makeStepGaussColumn(A, bias, col, free_elements);

    DoubleVector result = DoubleVector(givenBias.getLen());
    for(int col = 0; col < m; col++)
        result.elems[col] = bias[main_elements[col]];
    return result;
}

const int Solver::makeStepGaussColumn(Matrix &A, DoubleVector &bias, const int column, IntegerVector &free_elements) {
    const int i_max = A.arg_module_max_line(column, 0, free_elements);
    const double main_elem = A(i_max, column);
    if (fabs(main_elem) < 1e-16) {
        std::cout << "Singular matrix" << std::endl;
        exit(-1);
    } else {
        const int n = A.getShape(0);
        const int m = A.getShape(1);
        free_elements.elems[i_max] = 1;
        for(int i = 0; i < m; i++)
            if (i != i_max) {
                bias.elems[i] -= A(i, column) * bias[i_max] / main_elem;
                subtractRows(A, i, i_max, A(i, column) / main_elem);
            }
        subtractRows(A, i_max, i_max, (main_elem - 1) / main_elem);
        bias.elems[i_max] /= main_elem;
        return i_max;
    }
}

void Solver::subtractRows(Matrix &A, const int subtrahend, const int subtractor, const double lambda) {
    int n = A.getShape(0);
    int m = A.getShape(1);
    for(int j = 0; j < m; j++)
        A.elems[subtrahend*m + j] -= lambda * A(subtractor, j);
}
