//
// Created by xapulc on 03.09.19.
//

#include <tgmath.h>
#include "Vector.h"

Vector::Vector(const int len) {
    if (len <= 0) {
        std::cout << "Wrong len: " << len << std::endl;
        exit(-1);
    }
    this->elems = std::vector<double>((unsigned long) len);
    for(int i = 0; i < len; i++) {
        this->elems[i] = 0;
    }
    this->len = len;
}

Vector::Vector(const std::vector<double> other, const int len) {
    if (len <= 0) {
        std::cout << "Wrong len: " << len << std::endl;
        exit(-1);
    }
    this->elems = std::vector<double>((unsigned long) len);
    for(int i = 0; i < len; i++) {
        this->elems[i] = other[i];
    }
    this->len = len;
}

Vector::Vector(const Vector &other) {
    this->len = other.len;
    this->elems = std::vector<double>((unsigned long) len);
    for(int i = 0; i < len; i++) {
        this->elems[i] = other[i];
    }
}

Vector& Vector::operator=(const Vector &other) {
    this->len = other.len;
    this->elems = std::vector<double>((unsigned long) len);
    for(int i = 0; i < len; i++) {
        this->elems[i] = other[i];
    }
    return *this;
}

Vector& Vector::operator+=(const Vector &other) {
    if (this->len != other.len) {
        std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++) {
        this->elems[i] += other[i];
    }
    return *this;
}

Vector Vector::operator+(const Vector &other) const {
    auto buf = Vector(*this);
    buf += other;
    return buf;
}

Vector& Vector::operator*=(const Vector &other) {
    if (this->len != other.len) {
        std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++) {
        this->elems[i] *= other[i];
    }
    return *this;
}

Vector Vector::operator*(const Vector &other) const {
    auto buf = Vector(*this);
    buf *= other;
    return buf;
}

Vector& Vector::operator*=(const double alpha) {
    for(int i = 0; i < len; i++) {
        this->elems[i] *= alpha;
    }
    return *this;
}

Vector Vector::operator*(double alpha) const {
    auto buf = Vector(*this);
    buf *= alpha;
    return buf;
}

Vector& Vector::operator-=(const Vector &other) {
    (*this) += other * (-1);
    return *this;
}

Vector Vector::operator-(const Vector &other) const {
    auto buf = Vector(*this);
    buf -= other;
    return buf;
}

Vector& Vector::operator/=(const Vector &other) {
    if (this->len != other.len) {
        std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
        exit(-1);
    }
    for(int i = 0; i < len; i++) {
        this->elems[i] *= other[i];
    }
    return *this;
}

Vector Vector::operator/(const Vector &other) const {
    auto buf = Vector(*this);
    buf /= other;
    return buf;
}

Vector& Vector::operator/=(const double alpha) {
    for(int i = 0; i < len; i++) {
        this->elems[i] /= alpha;
    }
    return *this;
}

Vector Vector::operator/(double alpha) const {
    auto buf = Vector(*this);
    buf /= alpha;
    return buf;
}
