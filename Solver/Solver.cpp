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

Matrix Solver::reduceToHessenbergForm(const Matrix &A, const char *method) {
    if (A.getShape(0) != A.getShape(1)) {
        std::cout << "Wrong shape: " << A.getShape(0) << ", " << A.getShape(1) << std::endl;
        exit(-1);
    }

    if (method == "rotations")
        return rotationsMethodReductionToHessenbergFrom(A);
    else
        return rotationsMethodReductionToHessenbergFrom(A);
}

Matrix Solver::rotationsMethodReductionToHessenbergFrom(const Matrix &A) {
    Matrix Res = Matrix(A);

    int n = Res.getShape(0);
    if (n > 1) {
        for(int i = 1; i < n; i++) {
            DoubleVector b = DoubleVector(n - i);
            for(int j = i; j < n; j++)
                b.elems[j - i] = Res(j, i - 1);
            Matrix T = Matrix::eye(n - i);
            Matrix InvertedT = Matrix::eye(n - i);
            getTransformToNorm(b, T, InvertedT);

            Matrix Old = Matrix(Res);
            for(int j = i; j < n; j++)
                for(int k = i; k < n; k++) {
                    Res.elems[j * n + k] = 0;
                    for(int l = i; l < n; l++)
                        Res.elems[j * n + k] += Old(j, l) * InvertedT(l - i, k - i);
                }

            Old = Matrix(Res);
            for(int j = i; j < n; j++)
                for(int k = i; k < n; k++) {
                    Res.elems[j * n + k] = 0;
                    for(int l = i; l < n; l++)
                        Res.elems[j * n + k] += T(j - i, l - i) * Old(l, k);
                }
        }
    }
    return Res;
}

void Solver::getTransformToNorm(DoubleVector &b, Matrix &T, Matrix &InvertedT) {
    int n = b.getLen();

    if (n < 2) {
        if (b[0] < 0) {
            T.elems[0] = -1;
            InvertedT.elems[0] = -1;
        }
    } else {
        for(int i = 1; i < n; i++) {
            if ((fabs(b[0]) > 1e-16) || (fabs(b[i]) > 1e-16)) {
                double denom = sqrt(b[0] * b[0] + b[i] * b[i]);
                double cos_t = b[0] / denom;
                double sin_t = b[i] / denom;

                int k = i * n;
                for(int j = 0; j < n; j++) {
                    T.elems[j] = cos_t * T.elems[j] - sin_t * T.elems[k + j];
                    T.elems[k + j] = sin_t * T.elems[j] + cos_t * T.elems[k + j];

                    InvertedT.elems[j*n] = cos_t * T.elems[j*n] - sin_t * T.elems[j*n + i];
                    InvertedT.elems[j*n + i] = sin_t * T.elems[j*n] + cos_t * T.elems[j*n + i];
                }

                b.elems[0] = denom;
                b.elems[i] = 0;
            }
        }
    }
}

void Solver::reduceQR(const Matrix &A, Matrix &Q, Matrix &R, const char *method) {
    if (A.getShape(0) != A.getShape(1)) {
        std::cout << "Wrong shape: " << A.getShape(0) << ", " << A.getShape(1) << std::endl;
        exit(-1);
    }

    if (method == "reflection")
        reflectionMethodReduceQR(A, Q, R);
    else
        reflectionMethodReduceQR(A, Q, R);
}

void Solver::reflectionMethodReduceQR(const Matrix &A, Matrix &Q, Matrix &R) {
    int n = A.getShape(0);
    Q = Matrix::eye(n);
    R = Matrix(A);

    for(int i = 0; i < n; i++) {
        auto b = DoubleVector(n - i);
        Matrix U_small;
        auto U = Matrix::eye(n);

        for(int j = 0; j < n-i; j++)
            b.elems[j] = R(i, j+i);
        getReflectionVectorAndTransformation(b, U_small);
        for(int j = i; j < n; j++)
            for(int k = i; k < n; k++)
                U.elems[j*n + k] = U_small.elems[(j-i) * (n-i) + k-i];
        Q = Q.dot(U);
        R = U.dot(R);
    }
    Q = Q.t();
}

void Solver::getReflectionVectorAndTransformation(DoubleVector &b, Matrix &U) {
    auto e_i = DoubleVector(b.getLen());
    e_i.elems[0] = 1;

    double denom = sqrt((b - e_i * sqrt(b.residual())).residual());
    if (fabs(denom) > 1e-16) {
        b = (b - e_i * sqrt(b.residual())) / denom;
        Matrix b_matr = Matrix(b);
        U = Matrix::eye(b.getLen()) - (b_matr.dot(b_matr.t()) * 2);
    } else {
        U = Matrix::eye(b.getLen());
    }
}

DoubleVector Solver::findEigenvalues(const Matrix &A, const int max_iter) {
    auto eigenvalues = DoubleVector(A.getShape(0));
    Matrix reducedA = reduceToHessenbergForm(A);
    Matrix Q;
    Matrix R;

    for(int i = 0; i < max_iter; i++) {
        reduceQR(reducedA, Q, R);
        reducedA = R.dot(Q);
    }
    for(int i = 0; i < A.getShape(0); i++) {
        eigenvalues.elems[i] = reducedA(i, i);
    }
    return eigenvalues;
}
