#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec3f.h"
#include "myClasses/Vec3ui.h"

#include <QPaintEvent>
#include <QPixmap>
#include <iostream>
#include <cmath>

bool edgeFunction(int ax, int ay, int bx, int by, int x, int y)
{
    return ((x - ax) * (by - ay) - (y - ay) * (bx - ax) >= 0);
}

bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y)
{
    bool inside = true;

    inside &= edgeFunction(x0, y0, x1, y1, x, y);
    inside &= edgeFunction(x1, y1, x2, y2, x, y);
    inside &= edgeFunction(x2, y2, x0, y0, x, y);

    return inside;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    size_t w = static_cast<size_t>(geometry().width());
    size_t h = static_cast<size_t>(geometry().height());

    QPainter painter(this);

    // init objects to draw
    Cube testCube(-0.5, -0.5, -0.5, 1);

    // Getting triangles(3 consecutive points from 0, 3, 6 ... vector.size() - 4 make triangle) of objects
    std::vector<Vec3f> trianglesPoints;
    testCube.getIndexes(trianglesPoints);

    // actly do not know wtf is this so stay commented
//    double x = 255.0 / w;
//    double y = 255.0 / h;

    // for now it's an identity matrix
    Mat3f modelViewProjectMat;
    modelViewProjectMat.setIdentity();

    // not necessary but prefer dark background
    painter.setPen(QColor(0, 0, 0, 255));
    for(size_t i = 0; i < w; i++)
        for(size_t j = 0; j < h; j++)
                painter.drawPoint(i, j);

    // getting points from model coordinates to canvas
    painter.setPen(QColor(255, 0, 0, 255));
    for (size_t i = 0; i != trianglesPoints.size(); i += 3)
    {
        // Be careful type of points(mb ask pro for help)
        Vec3f V0 = trianglesPoints[i] * modelViewProjectMat;
        V0.normalize();
        Vec3f V1 = trianglesPoints[i + 1] * modelViewProjectMat;
        V1.normalize();
        Vec3f V2 = trianglesPoints[i + 2] * modelViewProjectMat;
        V2.normalize();

        // Computing raster space points
        int x0 = (V0.getX() + 1) / 2 * w;
        int y0 = (1 - V0.getY()) / 2 * h;
        int x1 = (V1.getX() + 1) / 2 * w;
        int y1 = (1 - V1.getY()) / 2 * h;
        int x2 = (V2.getX() + 1) / 2 * w;
        int y2 = (1 - V2.getY()) / 2 * h;

        // Finding bounding box coords
        int xmax= INT_MIN, ymax= INT_MIN;
        int xmin = INT_MAX, ymin= INT_MAX;
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

        for (int y = ymin; y <= ymax; y++) {
            for (int x = xmin; x <= xmax; x++) {
                if (pixelOverlapsTriangle(x0, y0, x1, y1, x2, y2, x, y))
                {
                    if (i == 27)
                    {
                         painter.setPen(QColor(0, 255, 0, 255));
                         painter.drawPoint(x, y);
                         painter.setPen(QColor(255, 0, 0, 255));
                    }
                    if (i == 24)
                    {
                         painter.setPen(QColor(255, 0, 0, 255));
                         painter.drawPoint(x, y);
                         painter.setPen(QColor(255, 0, 0, 255));
                    }
                }
            }
        }
//        std::cout << (trianglesPoints[i].getX() + 1) / 2 * w << ' ' << (1 - trianglesPoints[i].getY()) / 2 * h << std::endl;
    }
}

