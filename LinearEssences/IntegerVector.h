//
// Created by xapulc on 06.09.19.
//

#ifndef SEMINAR_INTEGERVECTOR_H
#define SEMINAR_INTEGERVECTOR_H


#include "Vector.h"

class IntegerVector: public Vector<int> {
    typedef Vector<int> Parent;
public:
    using Parent::Parent;
};


#endif //SEMINAR_INTEGERVECTOR_H
