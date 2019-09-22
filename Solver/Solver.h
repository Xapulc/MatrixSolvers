//
// Created by xapulc on 22.09.19.
//

#ifndef LINEARSOLVERS_SOLVER_H
#define LINEARSOLVERS_SOLVER_H


#include "../Vectors/Matrix.h"

class Solver {
public:
    Solver() = default;

    static Matrix solve(const Matrix &A, const Matrix &bias,
                        const char *method = "gaussMainElementColumn");
    static Matrix reduceToHessenbergForm(const Matrix &A, const char *method = "rotations");
    static void reduceQR(const Matrix &A, Matrix &Q, Matrix &R, const char *method = "reflection");
    static Matrix findEigenvalues(const Matrix &A, int max_iter = 10000);

    ~Solver() = default;
private:
    static Matrix gaussMainElementColumn(const Matrix &A, const Matrix &bias);
    static const int makeStepGaussColumn(Matrix &A, Matrix &bias, int column,
                                         BoolVector &free_elements);
    static void subtractRows(Matrix &A, int subtrahend, int subtractor, double lambda=1);
    static Matrix rotationsMethodReductionToHessenbergFrom(const Matrix &A);
    static void getTransformToNorm(Matrix &b, Matrix &T, Matrix &InvertedT);
    static void reflectionMethodReduceQR(const Matrix &A, Matrix &Q, Matrix &R);
    static void getReflectionVectorAndTransformation(Matrix &b, Matrix &U);
};


#endif //LINEARSOLVERS_SOLVER_H
