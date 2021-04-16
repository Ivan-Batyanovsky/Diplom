#ifndef TOREFACTOR_H
#define TOREFACTOR_H

#include "mainwindow.h"
#include "myClasses/Vec4f.h"

bool edgeFunction(int ax, int ay, int bx, int by, int x, int y);
bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y);
void colorBackground(QPainter & painter, size_t w, size_t h);
void loadPoints(std::vector<Vec4f> & trianglesPoints);
void initMVPmatrix(Mat44f & modelViewProjectMat, size_t w, size_t h);
void renderScene(QPainter & painter, std::vector<Vec4f> & trianglesPoints, Mat44f & modelViewProjectMat, size_t w, size_t h);
int convertToPixelX(float x);
int convertToPixelY(float y);
void findBoundingBox(int x0, int y0, int x1, int y1, int x2, int y2, int & xmin, int & ymin, int & xmax, int & ymax);

#endif // TOREFACTOR_H
