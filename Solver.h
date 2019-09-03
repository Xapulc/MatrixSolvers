//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_SOLVER_H
#define SEMINAR_SOLVER_H


#include <vector>
#include "Matrix.h"
#include "Vector.h"

class Solver {
public:
    Solver() = default;

    Vector solve(const Matrix &A, const Vector &bias, const char *method = "gaussMainElementColumn") const;

    ~Solver() = default;
private:
    Vector gaussMainElementColumn(const Matrix &A, const Vector &bias) const;
};

#endif //SEMINAR_SOLVER_H
