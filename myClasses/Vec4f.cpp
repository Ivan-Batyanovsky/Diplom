//
// Created by ivanb on 2/24/2021.
//

#include "Vec4f.h"
#include "Mat44f.h"

// Constructors
Vec4f::Vec4f()
{
    x_ = 0, y_ = 0, z_ = 0, w_ = 1;
}

Vec4f::Vec4f(const Vec4f & temp)
{
    x_ = temp.x_, y_ = temp.y_, z_ = temp.z_, w_ = temp.w_;
}

Vec4f::Vec4f(const float x, const float y, const float z, const float w)
{
    x_ = x, y_ = y, z_ = z, w_ = w;
}

// Destructor
Vec4f::~Vec4f()
{
}

// Class operators
Vec4f Vec4f::operator+(const Vec4f & temp) const
{
    return Vec4f(x_ + temp.x_, y_ + temp.y_, z_ + temp.z_, w_ + temp.w_);
}

Vec4f Vec4f::operator-(const Vec4f & temp) const
{
    return Vec4f(x_ - temp.x_, y_ - temp.y_, z_ - temp.z_, w_ - temp.w_);
}

// Assignment operator
Vec4f & Vec4f::operator=(const Vec4f& temp)
{
    if (this == &temp)
        return *this;

    x_ = temp.x_;
    y_ = temp.y_;
    z_ = temp.z_;
    w_ = temp.w_;

    return *this;
}

Vec4f Vec4f::normalize() const
{
    float len = this->getLength();

    return Vec4f(x_ / len, y_ / len, z_ / len);
}

// Class methods


// Friends operators
std::ostream & operator<<(std::ostream & os, const Vec4f & v)
{
    os << "--------- Vec3f -----------\n";
    os << "x: " << v.x_ << ", y: " << v.y_ << ", z: " << v.z_ << ", w: " << v.w_ << std::endl;
    os << "--------- Vec3fEnd ------\n";
    return os;
}

Vec4f operator*(Vec4f & v, Mat44f & m) {
    Vec4f res(
            v.x_ * m.elements_[0][0] + v.y_ * m.elements_[1][0] + v.z_ * m.elements_[2][0] + v.w_ * m.elements_[3][0],
            v.x_ * m.elements_[0][1] + v.y_ * m.elements_[1][1] + v.z_ * m.elements_[2][1] + v.w_ * m.elements_[3][1],
            v.x_ * m.elements_[0][2] + v.y_ * m.elements_[1][2] + v.z_ * m.elements_[2][2] + v.w_ * m.elements_[3][2],
            v.x_ * m.elements_[0][3] + v.y_ * m.elements_[1][3] + v.z_ * m.elements_[2][3] + v.w_ * m.elements_[3][3]
            );

    return res;
}

Vec4f vecMul(const Vec4f & f, const Vec4f & s)
{
    return Vec4f(f.y_ * s.z_ - f.z_ * s.y_, f.z_ * s.x_ - f.x_ * s.z_, f.x_ * s.y_ - f.y_ * s.x_);
}

float skalMul(const Vec4f & f, const Vec4f & s)
{
    return (f.x_ * s.x_ + f.y_ * s.y_ + f.z_ * s.z_);
}
