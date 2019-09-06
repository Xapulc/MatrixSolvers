//
// Created by xapulc on 06.09.19.
//

#include "DoubleVector.h"

DoubleVector& DoubleVector::operator/=(const DoubleVector &other) {
    if (this->len != other.len) {
        std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++) {
        this->elems[i] *= other[i];
    }
    return *this;
}

DoubleVector DoubleVector::operator/(const DoubleVector &other) const {
    auto buf = DoubleVector(*this);
    buf /= other;
    return buf;
}

DoubleVector& DoubleVector::operator/=(const double alpha) {
    for(int i = 0; i < len; i++) {
        this->elems[i] /= alpha;
    }
    return *this;
}

DoubleVector DoubleVector::operator/(double alpha) const {
    auto buf = DoubleVector(*this);
    buf /= alpha;
    return buf;
}
