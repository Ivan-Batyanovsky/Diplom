#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec4f.h"
#include "myClasses/Renderbase.h"
#include "ToRefactor.h"

#include <QPaintEvent>
#include <QPixmap>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846f

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
            Render_.changeScaling(Vec4f(0.9f, 0.9f, 1.1f));
            break;
        case Qt::Key_P:
            Render_.changeScaling(Vec4f(1.1f, 1.1f, 0.9f));
            break;
        case Qt::Key_T:
            Render_.changeTranslation(Vec4f(0.0f, -1.0f, 0.0f));
            update();
            break;
        case Qt::Key_G:
            Render_.changeTranslation(Vec4f(0.0f, 1.0f, 0.0f));
            update();
            break;
        case Qt::Key_F:
            Render_.changeTranslation(Vec4f(1.0f, 0.0f, 0.0f));
//            std::cout << Render_.getTranslation();
            update();
            break;
        case Qt::Key_H:
            Render_.changeTranslation(Vec4f(-1.0f, 0.0f, 0.0f));
            update();
            break;
        case Qt::Key_R:
            Render_.changeTranslation(Vec4f(0.0f, 0.0f, 1.0f));
            update();
            break;
        case Qt::Key_Y:
            Render_.changeTranslation( Vec4f(0.0f, 0.0f, -1.0f));
            update();
            break;
        case Qt::Key_W:
            Render_.changeRotation(Vec4f(10.0f * PI / 360.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_S:
            Render_.changeRotation(Vec4f(-10.0f * PI / 360.0f, 0.0f, 0.0f));
            break;
        case Qt::Key_A:
            Render_.changeRotation(Vec4f(0.0f, 10.0f  * PI / 360.0f, 0.0f));
            break;
        case Qt::Key_D:
            Render_.changeRotation(Vec4f(0.0f, 010.f  * PI / 360.0f, 0.0f));
            break;
        case Qt::Key_Q:
            Render_.changeRotation(Vec4f(0.0f, 0.0f, 10.0f  * PI / 360.0f));
            break;
        case Qt::Key_E:
            Render_.changeRotation(Vec4f(0.0f, 0.0f, -10.0f  * PI / 360.0f));
            break;

    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    size_t w = static_cast<size_t>(geometry().width());
    size_t h = static_cast<size_t>(geometry().height());

    QPainter painter(this);

    // Getting triangles(3 consecutive points from 0, 3, 6 ... vector.size() - 4 make triangle) of objects
    static bool loaded = false;
    if (!loaded)
    {
        Render_.loadCube({-1.0f, -1.0f, -6.0f, 2.0f});
        loaded = true;
    }
    // Model * View * Projection matrices
//    Mat44f modelViewProjectMat;
//    initMVPmatrix(modelViewProjectMat, w, h);
//    std::cout << "Here AGAIN!"<< Render_.getTranslation().getElement(0, 3) << "\n";
    Render_.setMVPmatrix(w, h);

    // not necessary but prefer dark background
    colorBackground(painter, w, h);
//    std::cout << Render_.getTranslation();
    Render_.renderScene(painter, w, h);
}

