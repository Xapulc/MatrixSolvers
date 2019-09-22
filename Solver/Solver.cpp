//
// Created by xapulc on 22.09.19.
//

#include "Solver.h"

Matrix Solver::solve(const Matrix &A, const Matrix &bias, const char *method) {
    if (A.getShape(0) != bias.getShape(0)) {
        std::cout << "Wrong length of bias: " << A.getShape(0) << ", " << bias.getShape(0) << std::endl;
        exit(-1);
    }

    if (method == "gaussMainElementColumn")
        return gaussMainElementColumn(A, bias);
    else
        return gaussMainElementColumn(A, bias);
}

Matrix Solver::gaussMainElementColumn(const Matrix &givenA, const Matrix &givenBias) {
    Matrix A = Matrix(givenA);
    Matrix bias = Matrix(givenBias);
    int n = givenA.getShape(0);
    int m = givenA.getShape(1);
    if (n != m) {
        std::cout << "There is non-square matrix, shapes: (" << n << ", " << m << std::endl;
        exit(-1);
    }
    std::vector<int> main_elements = std::vector<int>(static_cast<unsigned long>(m));
    BoolVector free_elements = BoolVector(m);
    for(int col = 0; col < m; col++) {
        main_elements[col] = makeStepGaussColumn(A, bias, col, free_elements);
    }

    Matrix result = Matrix(givenBias.getShape(0));
    for(int col = 0; col < m; col++)
        result[col] = bias[main_elements[col]];
    return result;
}

const int Solver::makeStepGaussColumn(Matrix &A, Matrix &bias, const int column, BoolVector &free_elements) {
    const int i_max = A.arg_module_max_line(column, 0, free_elements);
    const double main_elem = A(i_max, column);
    if (fabs(main_elem) < 1e-16) {
        std::cout << "Singular matrix" << std::endl;
        exit(-1);
    } else {
        const int n = A.getShape(0);
        const int m = A.getShape(1);
        free_elements[i_max] = true;
        for(int i = 0; i < n; i++)
            if (i != i_max) {
                bias[i] -= A(i, column) * bias[i_max] / main_elem;
                subtractRows(A, i, i_max, A(i, column) / main_elem);
            }
        subtractRows(A, i_max, i_max, (main_elem - 1) / main_elem);
        bias[i_max] /= main_elem;
        return i_max;
    }
}

void Solver::subtractRows(Matrix &A, const int subtrahend, const int subtractor, const double lambda) {
    int n = A.getShape(0);
    int m = A.getShape(1);
    for(int j = 0; j < m; j++)
        A(subtrahend, j) -= lambda * A(subtractor, j);
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
            Matrix b = Matrix(n - i);
            for(int j = i; j < n; j++)
                b[j - i] = Res(j, i - 1);
            Matrix T = Matrix::eye(n - i);
            Matrix InvertedT = Matrix::eye(n - i);
            getTransformToNorm(b, T, InvertedT);

            Matrix Old = Matrix(Res);
            for(int j = 0; j < n; j++)
                for(int k = i; k < n; k++) {
                    Res(j, k) = 0;
                    for(int l = i; l < n; l++)
                        Res(j, k) += Old(j, l) * InvertedT(l - i, k - i);
                }

            Old = Matrix(Res);
            for(int j = i; j < n; j++)
                for(int k = 0; k < n; k++) {
                    Res(j, k) = 0;
                    for(int l = i; l < n; l++)
                        Res(j, k) += T(j - i, l - i) * Old(l, k);
                }
        }
    }
    return Res;
}

void Solver::getTransformToNorm(Matrix &b, Matrix &T, Matrix &InvertedT) {
    int n = b.getShape(0);

    if (n < 2) {
        if (b[0] < 0) {
            T(0, 0) = -1;
            InvertedT(0, 0) = -1;
        }
    } else {
        for(int i = 1; i < n; i++) {
            if ((fabs(b[0]) > 1e-16) || (fabs(b[i]) > 1e-16)) {
                double denom = sqrt(b[0] * b[0] + b[i] * b[i]);
                double cos_t = b[0] / denom;
                double sin_t = -b[i] / denom;

                auto TOld = Matrix(T);
                auto InversedTOld = Matrix(InvertedT);
                for(int j = 0; j < n; j++) {
                    T(0, j) = cos_t * TOld(0, j) - sin_t * TOld(i, j);
                    T(i, j) = sin_t * TOld(0, j) + cos_t * TOld(i, j);

                    InvertedT(j, 0) = cos_t * InversedTOld(j, 0) - sin_t * InversedTOld(j, i);
                    InvertedT(j, i) = sin_t * InversedTOld(j, 0) + cos_t * InversedTOld(j, i);
                }

                b[0] = denom;
                b[i] = 0;
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
        auto b = Matrix(n - i);
        Matrix U_small;
        auto U = Matrix::eye(n);

        for(int j = 0; j < n-i; j++)
            b[j] = R(j+i, i);
        getReflectionVectorAndTransformation(b, U_small);
        for(int j = i; j < n; j++)
            for(int k = i; k < n; k++)
                U(j, k) = U_small(j-i, k-i);
        Q = U.dot(Q);
        R = U.dot(R);
    }
    Q = Q.t();
}

void Solver::getReflectionVectorAndTransformation(Matrix &b, Matrix &U) {
    auto e_i = Matrix(b.getShape(0));
    e_i[0] = 1;

    double denom = sqrt((b - e_i * sqrt(b.residual())).residual());
    if (fabs(denom) > 1e-16) {
        b = (b - e_i * sqrt(b.residual())) / denom;
        Matrix b_matr = Matrix(b);
        U = Matrix::eye(b.getShape(0)) - (b_matr.dot(b_matr.t()) * 2);
    } else {
        U = Matrix::eye(b.getShape(0));
    }
}

Matrix Solver::findEigenvalues(const Matrix &A, const int max_iter) {
    auto eigenvalues = Matrix(A.getShape(0));
    Matrix reducedA = reduceToHessenbergForm(A);
    Matrix Q;
    Matrix R;

    for(int i = 0; i < max_iter; i++) {
        reduceQR(reducedA, Q, R);
        reducedA = R.dot(Q);
    }
    for(int i = 0; i < A.getShape(0); i++) {
        eigenvalues[i] = reducedA(i, i);
    }
    return eigenvalues;
}
