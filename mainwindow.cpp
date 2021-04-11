#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec3f.h"

#include <QPaintEvent>
#include <QPixmap>

bool edgeFunction(const Vec3f &a, const Vec3f &b, const Vec3f &c)
{
    return ((c.getX() - a.getX()) * (b.getY() - a.getY()) - (c.getY() - a.getY()) * (b.getX() - a.getX()) >= 0);
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

    Buffers::fDepthBuffer zbuffer(w, h);
    for (size_t i = 0; i < w; i++) {
        for (size_t j  = 0; j < h; j++) {
            zbuffer.set(i, j, 10000.0f);
        }
    }
    Buffers::ColourBuffer cbuffer(w, h);
    cbuffer.clear();
    QPainter painter(this);
    Cube testCube(0,0,1, 1);
    std::vector<Vec3f> triangles;
    testCube.getIndexes(triangles);
    double x = 255.0 / w;
    double y = 255.0 / h;

    Vec3f p1 = triangles[0];
    Vec3f p2 = triangles[1];
    Vec3f p3 = triangles[2];
    for(size_t i = 0; i < w; i++)
    {
        for(size_t j = 0; j < h; j++)
        {
            if (zbuffer.get(i, j) != 10000.0f)
                painter.setPen(QColor(255, 0, 0, 255));

            painter.drawPoint(i, j);
            painter.setPen(QColor(0, 255, 255, 255));
        }
    }
}

