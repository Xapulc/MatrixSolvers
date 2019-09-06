//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_SOLVER_H
#define SEMINAR_SOLVER_H


#include <vector>
#include <cmath>
#include "../LinearEssences/Matrix.h"
#include "../LinearEssences/Vector.h"

class Solver {
public:
    Solver() = default;

    static DoubleVector solve(const Matrix &A, const DoubleVector &bias,
                              const char *method = "gaussMainElementColumn");

    ~Solver() = default;
private:
    static DoubleVector gaussMainElementColumn(const Matrix &A, const DoubleVector &bias);
    static const int makeStepGaussColumn(Matrix &A, DoubleVector &bias, int column,
                                         IntegerVector &free_elements);
    static void subtractRows(Matrix &A, int subtrahend, int subtractor, double lambda=1);
};

#endif //SEMINAR_SOLVER_H
