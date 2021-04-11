//
// Created by ivanb on 2/24/2021.
//

#include "Vec3f.h"
#include "Mat3f.h"

// Constructors
Vec3f::Vec3f()
{
    x_ = 0, y_ = 0, z_ = 0, w_ = 1;
}

Vec3f::Vec3f(const Vec3f & temp)
{
    x_ = temp.x_, y_ = temp.y_, z_ = temp.z_, w_ = temp.w_;
}

Vec3f::Vec3f(const float x, const float y, const float z, const float w)
{
    x_ = x, y_ = y, z_ = z, w_ = w;
}

// Destructor
Vec3f::~Vec3f()
{
}

// Class operators
Vec3f Vec3f::operator+(const Vec3f & temp) const
{
    return Vec3f(x_ + temp.x_, y_ + temp.y_, z_ + temp.z_, w_ + temp.w_);
}

Vec3f Vec3f::operator-(const Vec3f & temp) const
{
    return Vec3f(x_ - temp.x_, y_ - temp.y_, z_ - temp.z_, w_ - temp.w_);
}

// Friends operators
std::ostream & operator<<(std::ostream & os, const Vec3f & v)
{
    os << "--------- Vec3f -----------\n";
    os << "x: " << v.x_ << ", y: " << v.y_ << ", z: " << v.z_ << ", w: " << v.w_ << std::endl;
    os << "--------- Vec3f -----------\n";
    return os;
}

Vec3f operator*(Vec3f & v, Mat3f & m) {
    Vec3f res(
            v.x_ * m.elements_[0][0] + v.y_ * m.elements_[1][0] + v.z_ * m.elements_[2][0] + v.w_ * m.elements_[3][0],
            v.x_ * m.elements_[0][1] + v.y_ * m.elements_[1][1] + v.z_ * m.elements_[2][1] + v.w_ * m.elements_[3][1],
            v.x_ * m.elements_[0][2] + v.y_ * m.elements_[1][2] + v.z_ * m.elements_[2][2] + v.w_ * m.elements_[3][2],
            v.x_ * m.elements_[0][3] + v.y_ * m.elements_[1][3] + v.z_ * m.elements_[2][3] + v.w_ * m.elements_[3][3]
            );

    return res;
}
