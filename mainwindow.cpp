#include "mainwindow.h"

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <iostream>
#include <cmath>
#include <QDir>

#define PI 3.14159265358979323846f

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Getting triangles(3 consecutive points from 0, 3, 6 ... vector.size() - 4 make triangle) of objects
    Render_ = RenderBase();

    // Load .obj files here using loadOBJ
    // Example:
    //    Render_.loadOBJ("C:/myOBJ.obj");
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_O:
            Render_.changeScaling(Vec4f(-0.1f, -0.1f, -0.1));
            update();
            break;
        case Qt::Key_P:
            Render_.changeScaling(Vec4f(0.1f, 0.1f, 0.1f));
            update();
            break;
        case Qt::Key_T:
            Render_.changeTranslation(Vec4f(0.0f, -0.3f, 0.0f));
            update();
            break;
        case Qt::Key_G:
            Render_.changeTranslation(Vec4f(0.0f, 0.3f, 0.0f));
            update();
            break;
        case Qt::Key_F:
            Render_.changeTranslation(Vec4f(0.3f, 0.0f, 0.0f));
            update();
            break;
        case Qt::Key_H:
            Render_.changeTranslation(Vec4f(-0.3f, 0.0f, 0.0f));
            update();
            break;
        case Qt::Key_R:
            Render_.changeTranslation(Vec4f(0.0f, 0.0f, 0.3f));
            update();
            break;
        case Qt::Key_Y:
            Render_.changeTranslation( Vec4f(0.0f, 0.0f, -0.3f));
            update();
            break;
        case Qt::Key_W:
            Render_.changeRotation(Vec4f(5.0f * PI / 360.0f, 0.0f, 0.0f));
            update();
            break;
        case Qt::Key_S:
            Render_.changeRotation(Vec4f(-5.0f * PI / 360.0f, 0.0f, 0.0f));
            update();
            break;
        case Qt::Key_A:
            Render_.changeRotation(Vec4f(0.0f, 5.0f  * PI / 360.0f, 0.0f));
            update();
            break;
        case Qt::Key_D:
            Render_.changeRotation(Vec4f(0.0f, -5.f  * PI / 360.0f, 0.0f));
            update();
            break;
        case Qt::Key_Q:
            Render_.changeRotation(Vec4f(0.0f, 0.0f, 5.0f  * PI / 360.0f));
            update();
            break;
        case Qt::Key_E:
            Render_.changeRotation(Vec4f(0.0f, 0.0f, -5.0f  * PI / 360.0f));
            update();
            break;
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    size_t windowWidth = static_cast<size_t>(geometry().width());
    size_t windowHeight = static_cast<size_t>(geometry().height());

    QPainter painter(this);

    // Model * View * Projection matrices
    Render_.initMVPmatrix(windowWidth, windowHeight);

    // Resize buffers after evety rebdered frame
    Render_.resizeBuffers(windowWidth, windowHeight);

    // Colouring colour buffer with the scene
    Render_.renderScene(windowWidth, windowHeight);

    // Showing rendered scene in window
    Render_.qtDraw(painter);
}

