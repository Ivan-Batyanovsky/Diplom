#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-loop-convert"
//
// Created by ivanb on 2/24/2021.
//

#include "Mat44f.h"
#include "Vec4f.h"
#include <cmath>

#define PI 3.14159265358979323846f


// Constructors
Mat44f::Mat44f()
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            elements_[i][j] = 0;
    }
}

Mat44f::Mat44f(const Mat44f & temp)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            elements_[i][j] = temp.elements_[i][j];
    }
}

Mat44f::Mat44f(const std::vector<float> & temp)
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            elements_[i][j] = temp[i * 4 + j];
    }
}

// Class operators
Mat44f Mat44f::operator+(const Mat44f & temp) const
{
    Mat44f ret;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            ret.elements_[i][j] = elements_[i][j] + temp.elements_[i][j];
    }

    return ret;
}

Mat44f Mat44f::operator-(const Mat44f & temp) const
{
    Mat44f ret;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            ret.elements_[i][j] = elements_[i][j] - temp.elements_[i][j];
    }

    return ret;
}


Mat44f Mat44f::operator*(const Mat44f & temp) const
{
    Mat44f res;
    res.elements_[0][0] = elements_[0][0] * temp.elements_[0][0] + elements_[0][1] * temp.elements_[1][0] + elements_[0][2] * temp.elements_[2][0] + elements_[0][3] * temp.elements_[3][0];
    res.elements_[0][1] = elements_[0][0] * temp.elements_[0][1] + elements_[0][1] * temp.elements_[1][1] + elements_[0][2] * temp.elements_[2][1] + elements_[0][3] * temp.elements_[3][1];
    res.elements_[0][2] = elements_[0][0] * temp.elements_[0][2] + elements_[0][1] * temp.elements_[1][2] + elements_[0][2] * temp.elements_[2][2] + elements_[0][3] * temp.elements_[3][2];
    res.elements_[0][3] = elements_[0][0] * temp.elements_[0][3] + elements_[0][1] * temp.elements_[1][3] + elements_[0][2] * temp.elements_[2][3] + elements_[0][3] * temp.elements_[3][3];

    res.elements_[1][0] = elements_[1][0] * temp.elements_[0][0] + elements_[1][1] * temp.elements_[1][0] + elements_[1][2] * temp.elements_[2][0] + elements_[1][3] * temp.elements_[3][0];
    res.elements_[1][1] = elements_[1][0] * temp.elements_[0][1] + elements_[1][1] * temp.elements_[1][1] + elements_[1][2] * temp.elements_[2][1] + elements_[1][3] * temp.elements_[3][1];
    res.elements_[1][2] = elements_[1][0] * temp.elements_[0][2] + elements_[1][1] * temp.elements_[1][2] + elements_[1][2] * temp.elements_[2][2] + elements_[1][3] * temp.elements_[3][2];
    res.elements_[1][3] = elements_[1][0] * temp.elements_[0][3] + elements_[1][1] * temp.elements_[1][3] + elements_[1][2] * temp.elements_[2][3] + elements_[1][3] * temp.elements_[3][3];

    res.elements_[2][0] = elements_[2][0] * temp.elements_[0][0] + elements_[2][1] * temp.elements_[1][0] + elements_[2][2] * temp.elements_[2][0] + elements_[2][3] * temp.elements_[3][0];
    res.elements_[2][1] = elements_[2][0] * temp.elements_[0][1] + elements_[2][1] * temp.elements_[1][1] + elements_[2][2] * temp.elements_[2][1] + elements_[2][3] * temp.elements_[3][1];
    res.elements_[2][2] = elements_[2][0] * temp.elements_[0][2] + elements_[2][1] * temp.elements_[1][2] + elements_[2][2] * temp.elements_[2][2] + elements_[2][3] * temp.elements_[3][2];
    res.elements_[2][3] = elements_[2][0] * temp.elements_[0][3] + elements_[2][1] * temp.elements_[1][3] + elements_[2][2] * temp.elements_[2][3] + elements_[2][3] * temp.elements_[3][3];

    res.elements_[3][0] = elements_[3][0] * temp.elements_[0][0] + elements_[3][1] * temp.elements_[1][0] + elements_[3][2] * temp.elements_[2][0] + elements_[3][3] * temp.elements_[3][0];
    res.elements_[3][1] = elements_[3][0] * temp.elements_[0][1] + elements_[3][1] * temp.elements_[1][1] + elements_[3][2] * temp.elements_[2][1] + elements_[3][3] * temp.elements_[3][1];
    res.elements_[3][2] = elements_[3][0] * temp.elements_[0][2] + elements_[3][1] * temp.elements_[1][2] + elements_[3][2] * temp.elements_[2][2] + elements_[3][3] * temp.elements_[3][2];
    res.elements_[3][3] = elements_[3][0] * temp.elements_[0][3] + elements_[3][1] * temp.elements_[1][3] + elements_[3][2] * temp.elements_[2][3] + elements_[3][3] * temp.elements_[3][3];

    return res;
}

Mat44f Mat44f::operator*(const float & temp) const {
    Mat44f res;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            res.elements_[i][j] = elements_[i][j] * temp;
    }
    return res;
}

Mat44f operator*(const float multi, const Mat44f & mat)
{
    return mat * multi;
}
//    Vec3f Vec3f::operator*(const Vec3f & temp) const; // mb vectornoe ili skalyarnoe proizvedenie

std::ostream & operator<<(std::ostream & os, const Mat44f & v)
{
    os << "-------- Mat3f ----------\n";
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
            os << v.elements_[i][j] << ' ';
        os << std::endl;
    }
    os << "-------- Mat3f ----------\n";

    return os;
}

Mat44f::~Mat44f()
{
}
// Matrix that calls this function must be empty(every element == 0).
void Mat44f::setPerspective(const float & angleOfView, const float & near, const float & far)
{
    float scale = 1.0f / tanf(angleOfView * 0.5f * PI / 180.0f);

    elements_[0][0] = scale;
    elements_[1][1] = scale;
    elements_[2][2] = -far / (far - near);
    elements_[3][2] = -far * near / (far - near);
    elements_[2][3] = -1.0f;
    elements_[3][3] = 0.0f;
}

void Mat44f::setIdentity()
{
    elements_[0][0] = 1.0f;
    elements_[1][1] = 1.0f;
    elements_[2][2] = 1.0f;
    elements_[3][3] = 1.0f;
}
//Vec3f Mat3f::operator*(const Vec3f & temp) const
//{
//    float x = temp.getX(), y = temp.getY(), z = temp.getZ(), w = temp.getW();
//    Vec3f res(
//            elements_[0][0] * x + elements_[0][1] * y + elements_[0][2] * z + elements_[0][3] * w,
//            elements_[1][0] * x + elements_[1][1] * y + elements_[1][2] * z + elements_[1][3] * w,
//            elements_[2][0] * x + elements_[2][1] * y + elements_[2][2] * z + elements_[2][3] * w,
//            elements_[3][0] * x + elements_[3][1] * y + elements_[3][2] * z + elements_[3][3] * w
//            );
//
//    return res;
//}

Vec4f operator*(Mat44f &m, Vec4f &v) {
    Vec4f res(
        v.x_ * m.elements_[0][0] + v.y_ * m.elements_[0][1] + v.z_ * m.elements_[0][2] + v.w_ * m.elements_[0][3],
        v.x_ * m.elements_[1][0] + v.y_ * m.elements_[1][1] + v.z_ * m.elements_[1][2] + v.w_ * m.elements_[1][3],
        v.x_ * m.elements_[2][0] + v.y_ * m.elements_[2][1] + v.z_ * m.elements_[2][2] + v.w_ * m.elements_[2][3],
        v.x_ * m.elements_[3][0] + v.y_ * m.elements_[3][1] + v.z_ * m.elements_[3][2] + v.w_ * m.elements_[3][3]
        );

    return res;
}
// Matrix that calls this function must be empty(every element == 0).
// If needed check if that is correct matrix.
void Mat44f::setOrthographic(const float l, const float r, const float b, const float t, const float n, const float f)
{
    elements_[0][0] = 2 / (r - l);
    elements_[0][3] = - (r + l) / (r - l);

    elements_[1][1] = 2 / (t - b);
    elements_[1][3] = - (t + b) / (t - b);

    elements_[2][2] = -2 / (f - n);
    elements_[2][3] = - (f + n) / (f - n);
    
    elements_[3][3] = 1.0f;

}


#pragma clang diagnostic pop
