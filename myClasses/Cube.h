//
// Created by ivanb on 2/26/2021.
//

#ifndef DIPLOM_CUBE_H
#define DIPLOM_CUBE_H

#include <iostream>
#include <vector>
class Vec4f;

class Cube {
private:
    float x_, y_, z_;
    float edge_;

public:

    Cube();
    Cube(float x, float y, float z, float len);
    Cube(Vec4f vec);

    void getVertices(std::vector<Vec4f> & v) const;
    void getIndexes(std::vector<Vec4f> & v) const;

    ~Cube();
};


#endif //DIPLOM_CUBE_H
