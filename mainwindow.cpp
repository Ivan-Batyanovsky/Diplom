#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec4f.h"
#include "ToRefactor.h"

#include <QPaintEvent>
#include <QPixmap>
#include <iostream>
#include <cmath>
// To DO: z-buffer, functions, colourBuffer, projectMatrix

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_K:
            std::cout << "YEP\n";
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    size_t w = static_cast<size_t>(geometry().width());
    size_t h = static_cast<size_t>(geometry().height());
//    std::cout << w << ' ' << h << ' ' << w / (float) h <<  std::endl;
    QPainter painter(this);

    // Getting triangles(3 consecutive points from 0, 3, 6 ... vector.size() - 4 make triangle) of objects
    std::vector<Vec4f> trianglesPoints;
    loadPoints(trianglesPoints);

    Mat44f modelViewProjectMat;
    initMVPmatrix(modelViewProjectMat, w, h);

    colorBackground(painter, w, h);

    renderScene(painter, trianglesPoints, modelViewProjectMat, w, h);
}

