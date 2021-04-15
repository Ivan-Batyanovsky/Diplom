#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec4f.h"

#include <iostream>
#include <cmath>

bool edgeFunction(int ax, int ay, int bx, int by, int x, int y)
{
    return ((x - ax) * (by - ay) - (y - ay) * (bx - ax) >= 0); // std::numeric_limits<T>::epsilon
}

bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y)
{
    bool inside = true;

    inside &= edgeFunction(x0, y0, x1, y1, x, y);
    inside &= edgeFunction(x1, y1, x2, y2, x, y);
    inside &= edgeFunction(x2, y2, x0, y0, x, y);

    return inside;
}

void colorBackground(QPainter & painter, size_t w, size_t h)
{
    // not necessary but prefer dark background
    painter.setPen(QColor(0, 0, 0, 255));
    for(size_t i = 0; i < w; i++)
        for(size_t j = 0; j < h; j++)
                painter.drawPoint(i, j);
}

void loadPoints(std::vector<Vec4f> & trianglesPoints)
{
    // init objects to draw
    Cube testCube(-0.5, -0.5, -0.5, 1);
    testCube.getIndexes(trianglesPoints);
}

void initMVPmatrix(Mat44f & modelViewProjectMat)
{
//    modelViewProjectMat.setPerspective(45.0f, -1.0f, 10.0f);
    modelViewProjectMat.setIdentity();
    std::cout << modelViewProjectMat;
}

void findBoundingBox(int x0, int y0, int x1, int y1, int x2, int y2, int & xmin, int & ymin, int & xmax, int & ymax)
{
    if (x0 > xmax) xmax = x0;
    if (y0 > ymax) ymax = y0;
    if (x0 < xmin) xmin = x0;
    if (y0 < ymin) ymin = y0;
    if (x1 > xmax) xmax = x1;
    if (y1 > ymax) ymax = y1;
    if (x1 < xmin) xmin = x1;
    if (y1 < ymin) ymin = y1;
    if (x2 > xmax) xmax = x2;
    if (y2 > ymax) ymax = y2;
    if (x2 < xmin) xmin = x2;
    if (y2 < ymin) ymin = y2;
}

int convertToPixelX(Vec4f & x, const size_t w)
{
    return (x.getX() + 1) / 2 * w;
}
int convertToPixelY(Vec4f & y, const size_t h)
{
    return (1 - y.getY()) / 2 * h;
}

void renderScene(QPainter & painter, std::vector<Vec4f> & trianglesPoints, Mat44f & modelViewProjectMat, size_t w, size_t h)
{
    for (size_t i = 0; i != trianglesPoints.size(); i += 3)
    {
        // Triangle vertices
        Vec4f V0 = trianglesPoints[i] * modelViewProjectMat;
        Vec4f V1 = trianglesPoints[i + 1] * modelViewProjectMat;
        Vec4f V2 = trianglesPoints[i + 2] * modelViewProjectMat;

        // Computing raster space points of triangle vertices
        int x0 = convertToPixelX(V0, w);
        int y0 = convertToPixelY(V0, h);
        int x1 = convertToPixelX(V1, w);
        int y1 = convertToPixelY(V1, h);
        int x2 = convertToPixelX(V2, w);
        int y2 = convertToPixelY(V2, h);

        // Finding bounding box coords
        int xmax= INT_MIN, ymax= INT_MIN;
        int xmin = INT_MAX, ymin= INT_MAX;
        findBoundingBox(x0, y0, x1, y1, x2, y2, xmin, ymin, xmax, ymax);

        painter.setPen(QColor(0, 0, 255, 255));
        for (int y = ymin; y <= ymax; y++) {
            for (int x = xmin; x <= xmax; x++) {
                if (pixelOverlapsTriangle(x0, y0, x1, y1, x2, y2, x, y))
                {
//                    if (i == 21 || i == 18) // 18, 21 are bugged
//                    {
//                        std::cout << V0 << V1 << V2;
//                        std::cout << x0 << ' ' << y0 << ' ' <<   x1 << ' ' << y1 << ' '  << x2 << ' ' << y2 << std::endl;
                        painter.setPen(QColor(0, 0, 255, 255));
                        painter.drawPoint(x, y);
                        painter.setPen(QColor(255, 0, 0, 255));
//                    }
                }
            }
        }
    }
}


















