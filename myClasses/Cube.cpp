//
// Created by ivanb on 2/26/2021.
//
#include "Vec4f.h"
#include "Cube.h"
//#include <vector>
Cube::Cube()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
    edge_ = 1;
}

Cube::Cube(float x, float y, float z, float len)
{
    x_ = x;
    y_ = y;
    z_ = z;
    edge_ = len;
}
/*
 * Every element is Vec3f with following x_, y_, z_.
 * In total there are 8 elements.
 * Mb bugs about order. */
void Cube::getVertices(std::vector<Vec4f> & v) const {
    v.push_back(Vec4f(x_, y_, z_));
    v.push_back(Vec4f(x_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_, z_));

    v.push_back(Vec4f(x_, y_, z_ + edge_));
    v.push_back(Vec4f(x_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_, z_ + edge_));
}

/*
 * Every element is Vec3f with following x_, y_, z_.
 * In total there are 12 * 3 elements: triangles with clockwise vertices order.
 * Mb bugs about order. */
void Cube::getIndexes(std::vector<Vec4f> & v) const {
    v.push_back(Vec4f(x_ + edge_, y_, z_));
    v.push_back(Vec4f(x_ + edge_, y_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_));

    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));

    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_, y_ + edge_, z_));

    v.push_back(Vec4f(x_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_, y_ + edge_, z_ + edge_));

    v.push_back(Vec4f(x_ + edge_, y_, z_));
    v.push_back(Vec4f(x_, y_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_, z_ + edge_));

    v.push_back(Vec4f(x_, y_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_, z_));
    v.push_back(Vec4f(x_, y_, z_));
//
    v.push_back(Vec4f(x_, y_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_, z_ + edge_));

    v.push_back(Vec4f(x_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_, y_, z_ + edge_));
//
    v.push_back(Vec4f(x_, y_ + edge_, z_));
    v.push_back(Vec4f(x_ + edge_, y_, z_));
    v.push_back(Vec4f(x_ + edge_, y_ + edge_, z_));

    v.push_back(Vec4f(x_, y_, z_));
    v.push_back(Vec4f(x_ + edge_, y_, z_));
    v.push_back(Vec4f(x_, y_ + edge_, z_));

    v.push_back(Vec4f(x_, y_, z_));
    v.push_back(Vec4f(x_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_, y_, z_ + edge_));

    v.push_back(Vec4f(x_, y_ + edge_, z_));
    v.push_back(Vec4f(x_, y_ + edge_, z_ + edge_));
    v.push_back(Vec4f(x_, y_, z_));

}

Cube::~Cube() {

}
