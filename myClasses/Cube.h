//
// Created by ivanb on 2/26/2021.
//

#ifndef DIPLOM_CUBE_H
#define DIPLOM_CUBE_H

#include <iostream>
#include <vector>
class Vec3f;

class Cube {
private:
    float x_, y_, z_;
    float edge_;

public:

    Cube();
    Cube(float x, float y, float z, float len);

    void getVertices(std::vector<Vec3f> & v) const;
    void getIndexes(std::vector<Vec3f> & v) const;

    ~Cube();
};


#endif //DIPLOM_CUBE_H
