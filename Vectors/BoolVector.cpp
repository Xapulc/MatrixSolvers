//
// Created by xapulc on 22.09.19.
//

#include <iostream>
#include "BoolVector.h"

BoolVector::BoolVector(const int len) {
    checkSize(len);
    this->len = len;
    createElems(len);
}

void BoolVector::checkSize(const int size) {
    if (size <= 0) {
        std::cout << "Wrong size: " << size << std::endl;
        exit(-1);
    }
}

void BoolVector::createElems(const int len) {
    if ((this->elems = std::deque<bool>(static_cast<unsigned long>(len))).empty()) {
        std::cout << "Cannot allocate enough memory. Len: " << len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++)
        elems[i] = false;
}

bool &BoolVector::operator[](const int i) {
    return elems[i];
}

bool BoolVector::operator[](const int i) const {
    return elems[i];
}

int BoolVector::getFirstTrue() const {
    int i;
    for(i = 0; (i < len) && !(*this)[i]; i++);
    return (i == len) ? -1 : i;
}

int BoolVector::getFirstFalse() const {
    int i;
    for(i = 0; (i < len) && (*this)[i]; i++);
    return (i == len) ? -1 : i;
}

void BoolVector::print() const {
    for(int i = 0; i < len; i++)
        std::cout << (*this)[i] << " ";
    std::cout << std::endl;
}
