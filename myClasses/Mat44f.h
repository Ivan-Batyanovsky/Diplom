#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-avoid-const-params-in-decls"
//
// Created by ivanb on 2/24/2021.
//

#ifndef DIPLOM_MAT3F_H
#define DIPLOM_MAT3F_H

#include <iostream>
#include <vector>
#include "Vec4f.h"

class Vec4f;
//ctrl shift r
class Mat44f {
    friend class Vec4f;
private:
    float elements_[4][4] = {};

public:
    Mat44f();
    Mat44f(const Mat44f & temp);
    Mat44f(const std::vector<float> & temp);

    void setPerspective(const float & angleOfView, const float & near, const float & far, const float & aspect);
    void setOrthographic(const float l, const float r, const float b, const float t, const float n, const float f);
    void setIdentity();

    Mat44f operator+(const Mat44f & temp) const;
    Mat44f operator-(const Mat44f & temp) const;
    Mat44f operator*(const Mat44f & temp) const;
    Mat44f operator*(const float & temp) const;
//    Vec3f operator*(const Vec3f & temp) const;

    friend Mat44f operator*(const float multi, const Mat44f & mat);
    friend std::ostream & operator<<(std::ostream & os, const Mat44f & v);
    friend Vec4f operator*(Vec4f & v, Mat44f & m);
    friend Vec4f operator*(Mat44f & m, Vec4f & v);
    ~Mat44f();
};


#endif //DIPLOM_MAT3F_H
