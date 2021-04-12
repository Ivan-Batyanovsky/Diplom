#include "Vec3ui.h"

// Constructors
Vec3ui::Vec3ui()
{
    x_ = 0, y_ = 0, z_ = 0, w_ = 1;
}

Vec3ui::Vec3ui(const Vec3ui & temp)
{
    x_ = temp.x_, y_ = temp.y_, z_ = temp.z_, w_ = temp.w_;
}

Vec3ui::Vec3ui(const unsigned int x, const unsigned int y, const unsigned int z, const unsigned int w)
{
    x_ = x, y_ = y, z_ = z, w_ = w;
}

// Destructor
Vec3ui::~Vec3ui()
{
}

// Class operators
Vec3ui Vec3ui::operator+(const Vec3ui & temp) const
{
    return Vec3ui(x_ + temp.x_, y_ + temp.y_, z_ + temp.z_, w_ + temp.w_);
}

Vec3ui Vec3ui::operator-(const Vec3ui & temp) const
{
    return Vec3ui(x_ - temp.x_, y_ - temp.y_, z_ - temp.z_, w_ - temp.w_);
}

// Assignment operator
Vec3ui & Vec3ui::operator=(const Vec3ui& temp)
{
    if (this == &temp)
        return *this;

    x_ = temp.x_;
    y_ = temp.y_;
    z_ = temp.z_;
    w_ = temp.w_;

    return *this;
}

// Friends operators
std::ostream & operator<<(std::ostream & os, const Vec3ui & v)
{
    os << "--------- Vec3ui -----------\n";
    os << "x: " << v.x_ << ", y: " << v.y_ << ", z: " << v.z_ << ", w: " << v.w_ << std::endl;
    os << "--------- Vec3ui -----------\n";
    return os;
}

//Vec3ui operator*(Vec3ui & v, Mat3f & m) {
//    Vec3ui res(
//            v.x_ * m.elements_[0][0] + v.y_ * m.elements_[1][0] + v.z_ * m.elements_[2][0] + v.w_ * m.elements_[3][0],
//            v.x_ * m.elements_[0][1] + v.y_ * m.elements_[1][1] + v.z_ * m.elements_[2][1] + v.w_ * m.elements_[3][1],
//            v.x_ * m.elements_[0][2] + v.y_ * m.elements_[1][2] + v.z_ * m.elements_[2][2] + v.w_ * m.elements_[3][2],
//            v.x_ * m.elements_[0][3] + v.y_ * m.elements_[1][3] + v.z_ * m.elements_[2][3] + v.w_ * m.elements_[3][3]
//            );

//    return res;
//}
