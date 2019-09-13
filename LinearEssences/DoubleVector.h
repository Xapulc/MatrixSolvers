//
// Created by xapulc on 06.09.19.
//

#ifndef SEMINAR_DOUBLEVECTOR_H
#define SEMINAR_DOUBLEVECTOR_H


#include "Vector.h"

class DoubleVector: public Vector<double> {
    typedef Vector<double> Parent;
public:
    using Parent::Parent;

    DoubleVector& operator/=(const DoubleVector &other);
    DoubleVector operator/(const DoubleVector &other) const;
    DoubleVector& operator/=(double alpha);
    DoubleVector operator/(double alpha) const;
    DoubleVector operator*(double alpha) const;
    DoubleVector operator*(const DoubleVector &other) const;
    DoubleVector operator-(const DoubleVector &other) const;
    using Parent::print;
    using Parent::residual;
};


#endif //SEMINAR_DOUBLEVECTOR_H
