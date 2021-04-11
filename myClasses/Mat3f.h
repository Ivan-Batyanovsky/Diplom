#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-avoid-const-params-in-decls"
//
// Created by ivanb on 2/24/2021.
//

#ifndef DIPLOM_MAT3F_H
#define DIPLOM_MAT3F_H

#include <iostream>
#include <vector>
#include "Vec3f.h"

class Vec3f;

class Mat3f {
    friend class Vec3f;
private:
    float elements_[4][4] = {};

public:
    Mat3f();
    Mat3f(const Mat3f & temp);
    Mat3f(const std::vector<float> & temp);

    void setPerspective(const float & angleOfView, const float & near, const float & far);
    void setOrthographic(const float l, const float r, const float b, const float t, const float n, const float f);
    void setIdentity();

    Mat3f operator+(const Mat3f & temp) const;
    Mat3f operator-(const Mat3f & temp) const;
    Mat3f operator*(const Mat3f & temp) const;
    Mat3f operator*(const float & temp) const;
//    Vec3f operator*(const Vec3f & temp) const;

    friend Mat3f operator*(const float multi, const Mat3f & mat);
    friend std::ostream & operator<<(std::ostream & os, const Mat3f & v);
    friend Vec3f operator*(Vec3f & v, Mat3f & m);
    friend Vec3f operator*(Mat3f & m, Vec3f & v);
    ~Mat3f();
};


#endif //DIPLOM_MAT3F_H
