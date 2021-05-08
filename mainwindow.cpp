#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec4f.h"
#include "ToRefactor.h"

#include <QPaintEvent>
#include <QPixmap>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846f

std::vector<Vec4f> trianglesPoints;
/* To DO: z-buffer, colourBuffer
*/
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
        case Qt::Key_O:
            makeScaling(trianglesPoints, Vec4f(0.9f, 0.9f, 1.1f));
            break;
        case Qt::Key_P:
            makeScaling(trianglesPoints, Vec4f(1.1f, 1.1f, 0.9f));
            break;
        case Qt::Key_T:
            makeTranslation(trianglesPoints, Vec4f(0.0f, 1.0f, 0.0f));
            update();
            break;
        case Qt::Key_G:
            makeTranslation(trianglesPoints, Vec4f(0.0f, -1.0f, 0.0f));
            break;
        case Qt::Key_F:
            makeTranslation(trianglesPoints, Vec4f(1.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_H:
            makeTranslation(trianglesPoints, Vec4f(-1.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_R:
            makeTranslation(trianglesPoints, Vec4f(0.0f, 0.0f, 1.0f));
            break;
        case Qt::Key_Y:
            makeTranslation(trianglesPoints, Vec4f(0.0f, 0.0f, -1.0f));
            break;
        case Qt::Key_W:
            makeRotation(trianglesPoints, Vec4f(10.0f * PI / 360.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_S:
            makeRotation(trianglesPoints, Vec4f(-10.0f * PI / 360.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_A:
            makeRotation(trianglesPoints, Vec4f(0.0f, 10.0f  * PI / 360.0f, 0.0f));
            break;
        case Qt::Key_D:
            makeRotation(trianglesPoints, Vec4f(0.0f, 010.f  * PI / 360.0f, 0.0f));
            break;
        case Qt::Key_Q:
            makeRotation(trianglesPoints, Vec4f(0.0f, 0.0f, 10.0f  * PI / 360.0f));
            break;
        case Qt::Key_E:
            makeRotation(trianglesPoints, Vec4f(0.0f, 0.0f, -10.0f  * PI / 360.0f));
            update();
            break;

    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    size_t w = static_cast<size_t>(geometry().width());
    size_t h = static_cast<size_t>(geometry().height());

    QPainter painter(this);

    // Getting triangles(3 consecutive points from 0, 3, 6 ... vector.size() - 4 make triangle) of objects
    loadPoints(trianglesPoints);

    // Model * View * Projection matrices
    Mat44f modelViewProjectMat;
    initMVPmatrix(modelViewProjectMat, w, h);

    // not necessary but prefer dark background
    colorBackground(painter, w, h);

    renderScene(painter, trianglesPoints, modelViewProjectMat, w, h);
}

