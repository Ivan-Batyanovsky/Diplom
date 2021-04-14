#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-avoid-const-params-in-decls"
//
// Created by ivanb on 2/24/2021.
//

#ifndef DIPLOM_VEC3F_H
#define DIPLOM_VEC3F_H

#include <iostream>
#include "Mat44f.h"
class Mat44f;

class Vec4f {
private:
    float x_, y_, z_, w_;

public:
    Vec4f();
    Vec4f(const Vec4f & temp);
    Vec4f(const float x, const float y, const float z, const float w = 1.0f);

    // mb vectornoe ili skalyarnoe proizvedenie
    // Vec3f Vec3f::operator*(const Vec3f & temp) const;
    Vec4f operator+(const Vec4f & temp) const;
    Vec4f operator-(const Vec4f & temp) const;

    // Assignment operator
    Vec4f & operator=(const Vec4f& temp);

    // check for explicit and implicit inline
    float getX() const { return x_; }
    float getY() const { return y_; }
    float getZ() const { return z_; }
    float getW() const { return w_; }

    void normalize() { x_ /= w_ , y_ /= w_, z_ /= w_, w_ = 1.0f; }

    friend std::ostream & operator<<(std::ostream & os, const Vec4f & v);
    friend Vec4f operator*(Vec4f & v, Mat44f & m);
    friend Vec4f operator*(Mat44f & m, Vec4f & v);
    ~Vec4f();
};


#endif //DIPLOM_VEC3F_H

#pragma clang diagnostic pop
