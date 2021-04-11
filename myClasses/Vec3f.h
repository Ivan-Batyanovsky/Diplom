#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-avoid-const-params-in-decls"
//
// Created by ivanb on 2/24/2021.
//

#ifndef DIPLOM_VEC3F_H
#define DIPLOM_VEC3F_H

#include <iostream>
#include "Mat3f.h"
class Mat3f;

class Vec3f {
private:
    float x_, y_, z_, w_;

public:
    Vec3f();
    Vec3f(const Vec3f & temp);
    Vec3f(const float x, const float y, const float z, const float w = 1.0f);

    // mb vectornoe ili skalyarnoe proizvedenie
    // Vec3f Vec3f::operator*(const Vec3f & temp) const;
    Vec3f operator+(const Vec3f & temp) const;
    Vec3f operator-(const Vec3f & temp) const;

    // check for explicit and implicit inline
    float getX() const { return x_; }
    float getY() const { return y_; }
    float getZ() const { return z_; }
    float getW() const { return w_; }

    void normalize() { x_ /= w_ , y_ /= w_, z_ /= w_, w_ = 1.0f; }

    friend std::ostream & operator<<(std::ostream & os, const Vec3f & v);
    friend Vec3f operator*(Vec3f & v, Mat3f & m);
    friend Vec3f operator*(Mat3f & m, Vec3f & v);
    ~Vec3f();
};


#endif //DIPLOM_VEC3F_H

#pragma clang diagnostic pop