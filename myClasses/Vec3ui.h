#ifndef VEC3UI_H
#define VEC3UI_H

#include <iostream>

class Vec3ui
{
private:
    unsigned int x_, y_, z_, w_;

public:
    Vec3ui();
    Vec3ui(const Vec3ui & temp);
    Vec3ui(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w = 1.0f);

    // mb vectornoe ili skalyarnoe proizvedenie
    // Vec3ui Vec3ui::operator*(const Vec3ui & temp) const;
    Vec3ui operator+(const Vec3ui & temp) const;
    Vec3ui operator-(const Vec3ui & temp) const;

    // Assignment operator
    Vec3ui & operator=(const Vec3ui& temp);

    // check for explicit and implicit inline
    unsigned int getX() const { return x_; }
    unsigned int getY() const { return y_; }
    unsigned int getZ() const { return z_; }
    unsigned int getW() const { return w_; }

    void normalize() { x_ /= w_ , y_ /= w_, z_ /= w_, w_ = 1; }

    friend std::ostream & operator<<(std::ostream & os, const Vec3ui & v);
//    friend Vec3ui operator*(Vec3ui & v, Mat3f & m);
//    friend Vec3ui operator*(Mat3f & m, Vec3ui & v);
    ~Vec3ui();
};

#endif // VEC3UI_H
