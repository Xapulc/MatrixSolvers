//
// Created by xapulc on 22.09.19.
//

#ifndef LINEARSOLVERS_BOOLVECTOR_H
#define LINEARSOLVERS_BOOLVECTOR_H

#include <deque>


class BoolVector {
public:
    void createElems(int len);

    BoolVector() = default;
    BoolVector(int len);

    bool& operator[](int i);
    bool operator[](int i) const;

    int getFirstTrue() const;
    int getFirstFalse() const;
    int getLength() const { return len; }
    void print() const;
private:
    int len{0};
    std::deque<bool> elems;
    static void checkSize(int size);
};


#endif //LINEARSOLVERS_BOOLVECTOR_H
