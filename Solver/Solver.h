//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_SOLVER_H
#define SEMINAR_SOLVER_H


#include <vector>
#include <cmath>
#include "../LinearEssences/Matrix.h"
#include <future>

class Solver {
public:
    Solver() = default;

    static DoubleVector solve(const Matrix &A, const DoubleVector &bias,
                              const char *method = "gaussMainElementColumn");
    static Matrix reduceToHessenbergForm(const Matrix &A, const char *method = "rotations");
    static void reduceQR(const Matrix &A, Matrix &Q, Matrix &R, const char *method = "reflection");
    static DoubleVector findEigenvalues(const Matrix &A, int max_iter = 1000);

    ~Solver() = default;
private:
    static DoubleVector gaussMainElementColumn(const Matrix &A, const DoubleVector &bias);
    static const int makeStepGaussColumn(Matrix &A, DoubleVector &bias, int column,
                                         IntegerVector &free_elements);
    static void subtractRows(Matrix &A, int subtrahend, int subtractor, double lambda=1);
    static Matrix rotationsMethodReductionToHessenbergFrom(const Matrix &A);
    static void getTransformToNorm(DoubleVector &b, Matrix &T, Matrix &InvertedT);
    static void reflectionMethodReduceQR(const Matrix &A, Matrix &Q, Matrix &R);
    static void getReflectionVectorAndTransformation(DoubleVector &b, Matrix &U);
};



#endif //SEMINAR_SOLVER_H
