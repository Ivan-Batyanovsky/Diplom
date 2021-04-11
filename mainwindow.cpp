#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec3f.h"

#include <QPaintEvent>
#include <QPixmap>
#include <iostream>

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
    for (size_t i = 0; i < trianglesPoints.size(); i++)
    {
        trianglesPoints[i] = trianglesPoints[i] * modelViewProjectMat;
        trianglesPoints[i].normalize();
        int px = (trianglesPoints[i].getX() + 1) / 2 * w;
        int py = (1 - trianglesPoints[i].getY()) / 2 * h;
        painter.drawPoint(px, py);
//        std::cout << (trianglesPoints[i].getX() + 1) / 2 * w << ' ' << (1 - trianglesPoints[i].getY()) / 2 * h << std::endl;
    }
}

