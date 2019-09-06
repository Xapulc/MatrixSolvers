//
// Created by xapulc on 03.09.19.
//

#ifndef SEMINAR_VECTOR_H
#define SEMINAR_VECTOR_H


#include <vector>
#include <iostream>

template <typename T>
class Vector {
public:
    std::vector<T> elems;

    Vector<T>() = default;

    Vector<T>(int len) {
        if (len <= 0) {
            std::cout << "Wrong len: " << len << std::endl;
            exit(-1);
        }
        this->elems = std::vector<T>((unsigned long) len);
        for(int i = 0; i < len; i++) {
            this->elems[i] = 0;
        }
        this->len = len;
    }

    Vector<T>(std::vector<T> other, int len) {
        if (len <= 0) {
            std::cout << "Wrong len: " << len << std::endl;
            exit(-1);
        }
        this->elems = std::vector<T>((unsigned long) len);
        for(int i = 0; i < len; i++) {
            this->elems[i] = other[i];
        }
        this->len = len;
    }

    Vector<T>(const Vector<T> &other) {
        this->len = other.len;
        this->elems = std::vector<T>((unsigned long) len);
        for(int i = 0; i < len; i++) {
            this->elems[i] = other[i];
        }
    }

    T operator[](const int i) const { return elems[i]; }
    Vector<T>& operator=(const Vector<T> &other) {
        this->len = other.len;
        this->elems = std::vector<T>((unsigned long) len);
        for(int i = 0; i < len; i++) {
            this->elems[i] = other[i];
        }
        return *this;
    }

    Vector<T>& operator+=(const Vector<T> &other) {
        if (this->len != other.len) {
            std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
            exit(-1);
        }
        for(int i = 0; i < len; i++) {
            this->elems[i] += other[i];
        }
        return *this;
    }

    Vector<T> operator+(const Vector<T> &other) const {
        auto buf = Vector<T>(*this);
        buf += other;
        return buf;
    }

    Vector<T>& operator*=(const Vector<T> &other) {
        if (this->len != other.len) {
            std::cout << "Wrong sizes: " << this->len << " and " << other.len << std::endl;
            exit(-1);
        }
        for(int i = 0; i < len; i++) {
            this->elems[i] *= other[i];
        }
        return *this;
    }

    Vector<T> operator*(const Vector<T> &other) const {
        auto buf = Vector<T>(*this);
        buf *= other;
        return buf;
    }

    Vector<T>& operator*=(const T alpha) {
        for(int i = 0; i < len; i++) {
            this->elems[i] *= alpha;
        }
        return *this;
    }

    Vector<T> operator*(const T alpha) const {
        auto buf = Vector<T>(*this);
        buf *= alpha;
        return buf;
    }

    Vector<T>& operator-=(const Vector<T> &other) {
        (*this) += other * (-1);
        return *this;
    }

    Vector<T> operator-(const Vector<T> &other) const {
        auto buf = Vector<T>(*this);
        buf -= other;
        return buf;
    }

    const int getLen() const { return len; }

    void print() const {
        for(int i = 0; i < len; i++)
            std::cout << (*this)[i] << " ";
        std::cout << std::endl;
    }

    double residual() const {
        double sum = 0;
        for(int i = 0; i < len; i++)
            sum += (*this)[i] * (*this)[i];
        return sum;
    }

    ~Vector<T>() = default;
protected:
    int len{0};
};


#endif //SEMINAR_VECTOR_H
