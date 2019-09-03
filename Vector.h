//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_VECTOR_H
#define SEMINAR_VECTOR_H


#include <vector>
#include <iostream>

class Vector {
public:
    Vector() = default;
    Vector(int len);
    Vector(std::vector<double> other, int len);
    Vector(const Vector &other);

    double operator[](const int i) const { return elems[i]; }
    Vector& operator=(const Vector &other);
    Vector& operator+=(const Vector &other);
    Vector operator+(const Vector &other) const;
    Vector& operator*=(const Vector &other);
    Vector operator*(const Vector &other) const;
    Vector& operator*=(double alpha);
    Vector operator*(double alpha) const;
    Vector& operator-=(const Vector &other);
    Vector operator-(const Vector &other) const;
    Vector& operator/=(const Vector &other);
    Vector operator/(const Vector &other) const;
    Vector& operator/=(double alpha);
    Vector operator/(double alpha) const;

    ~Vector() = default;
protected:
    int len{0};
    std::vector<double> elems;
};


#endif //SEMINAR_VECTOR_H
