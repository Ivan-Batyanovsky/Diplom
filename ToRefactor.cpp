#include "mainwindow.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/Vec4f.h"

#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846f
/* To think: top left-rule implementation*/

//Bad kostil -> make general rule!
void makeRotation(std::vector<Vec4f> & trianglesPoints, Vec4f anglesVec)
{
    Mat44f rotationMatrix;
//    static const Vec4f anglesVec(-45.0f * PI / 360.0f, 45.0f * PI / 360.0f,45.0f * PI / 360.0f);

    for (size_t i = 0, end = trianglesPoints.size(); i < end; i += 3)
    {
        rotationMatrix.setRotationX(anglesVec);
        trianglesPoints[i] = rotationMatrix * trianglesPoints[i];
        trianglesPoints[i + 1] = rotationMatrix * trianglesPoints[i + 1];
        trianglesPoints[i + 2] = rotationMatrix * trianglesPoints[i + 2];
        rotationMatrix = Mat44f();
        rotationMatrix.setRotationY(anglesVec);
        trianglesPoints[i] = rotationMatrix * trianglesPoints[i];
        trianglesPoints[i + 1] = rotationMatrix * trianglesPoints[i + 1];
        trianglesPoints[i + 2] = rotationMatrix * trianglesPoints[i + 2];
        rotationMatrix.setRotationZ(anglesVec);
        rotationMatrix = Mat44f();
        trianglesPoints[i] = rotationMatrix * trianglesPoints[i];
        trianglesPoints[i + 1] = rotationMatrix * trianglesPoints[i + 1];
        trianglesPoints[i + 2] = rotationMatrix * trianglesPoints[i + 2];
        rotationMatrix = Mat44f();
    }

}

void makeScaling(std::vector<Vec4f> & trianglesPoints, Vec4f koefVec)
{
    Mat44f scalingMatrix;
    scalingMatrix.setScaling(koefVec);

    for (size_t i = 0, end = trianglesPoints.size(); i < end; i += 3)
    {
        trianglesPoints[i] = scalingMatrix * trianglesPoints[i];
        trianglesPoints[i + 1] = scalingMatrix * trianglesPoints[i + 1];
        trianglesPoints[i + 2] = scalingMatrix * trianglesPoints[i + 2];
    }
}

void makeTranslation(std::vector<Vec4f> & trianglesPoints, Vec4f koefVec)
{
    Mat44f translationMatrix;
    translationMatrix.setScaling(koefVec);

    for (size_t i = 0, end = trianglesPoints.size(); i < end; i += 3)
    {
        trianglesPoints[i] = translationMatrix * trianglesPoints[i];
        trianglesPoints[i + 1] = translationMatrix * trianglesPoints[i + 1];
        trianglesPoints[i + 2] = translationMatrix * trianglesPoints[i + 2];
    }
}
float edgeFunction(float ax, float ay, float bx, float by, float x, float y)
{
    return ((x - ax) * (by - ay) - (y - ay) * (bx - ax)); // std::numeric_limits<T>::epsilon
}

// otrisovat rebra, optimize na rebre, PROVERKA NA 0,
bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float & w0, float & w1, float & w2)
{
    w0 = edgeFunction(x1, y1, x2, y2, x, y);
    if (w0 < 0) return false;

    w1 = edgeFunction(x2, y2, x0, y0, x, y);
    if (w1 < 0) return false;

    w2 = edgeFunction(x0, y0, x1, y1, x, y);
    if (w2 < 0) return false;

    return true;
}

void checkNormals(const Vec4f & V0, const Vec4f & V1, const Vec4f & V2)
{
//    Vec4f triagNormal = vecMul(V1- V0, V2 - V0).normalize();
//    Vec4f camPos = Vec4f(0, 0, -1);

    std::cout << edgeFunction(V0.getX(), V0.getY(), V1.getX(), V1.getY(), V2.getX(), V2.getY())  << ' ';
//    std::cout <<  sin(skalMul(triagNormal, camPos) / (triagNormal.getLength() * camPos.getLength()))  * 180.0 / 3.14159265<< ' ';
}

void colorBackground(QPainter & painter, size_t w, size_t h)
{
    painter.setPen(QColor(0, 0, 0, 255));
    for(size_t i = 0; i < w; i++)
        for(size_t j = 0; j < h; j++)
                painter.drawPoint(i, j);
}

void loadPoints(std::vector<Vec4f> & trianglesPoints)
{
    // init objects to draw
    Cube testCube(-1.0f, -1.0f, -6.0f, 2.0f);
    testCube.getIndexes(trianglesPoints);
}

void initMVPmatrix(Mat44f & modelViewProjectMat, size_t w, size_t h)
{
    float angleOfView = 45.0f, near = -2.0f, far = -50.0f;
    modelViewProjectMat.setPerspective(angleOfView, near, far, w / float(h));
//    modelViewProjectMat.setIdentity();
//    std::cout << modelViewProjectMat;
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
        V0.divByW();
        V1.divByW();
        V2.divByW();

        // Barycentric Coordinates
        float w0, w1, w2, area;

        area = edgeFunction(V0.getX(), V0.getY(), V1.getX(), V1.getY(), V2.getX(), V2.getY());
        if (area == 0)
        {
            std::cout << i << "-th traingle area == 0, skipping...\n";
            continue;
        }
        if (area > 0)
        {
            Vec4f temp = V1;
            V1 = V2;
            V2 = temp;
            area *= -1;
        }
        // Computing raster space points of triangle vertices
        int x0 = convertToPixelX(V0, w);
        int x1 = convertToPixelX(V1, w);
        int x2 = convertToPixelX(V2, w);
        int y0 = convertToPixelY(V0, h);
        int y1 = convertToPixelY(V1, h);
        int y2 = convertToPixelY(V2, h);

        // Finding bounding box coords
        int xmax= INT_MIN, ymax= INT_MIN;
        int xmin = INT_MAX, ymin= INT_MAX;
        findBoundingBox(x0, y0, x1, y1, x2, y2, xmin, ymin, xmax, ymax);

        // Init buffers(colour and depth respectively)
        Buffers::ColourBuffer clBuffer(w, h);
        Buffers::fDepthBuffer zBuffer(w, h);

//        std::cout << - (V2.getY() -  V0.getY()) * (V1.getX() - V0.getX()) << ' ' << area << std::endl;
//        std::cout << "i= " << i << std::endl << V0 << V1 << V2;
//        std::cout << trianglesPoints[i] << " " << trianglesPoints[i + 1] << " " << trianglesPoints[i + 2] << std::endl;
//        if (i != 12)
//            continue;
//        if (i == 12)
//             std::cout << x0 << ' ' << y0 << ' ' <<   x1 << ' ' << y1 << ' '  << x2 << ' ' << y2 << std::endl;

//        if (i == 21) std::cout << "Before Area!\n"<< V0 << V1 << V2;
//        if (i == 21) std::cout << V0 << V1 << V2;
        for (int y = ymin; y <= ymax; y++) {
            for (int x = xmin; x <= xmax; x++) {
                if (pixelOverlapsTriangle(x0, y0, x1, y1, x2, y2, x, y, w0, w1, w2))
                {
                    w0 /= area;
                    w1 /= area;
                    w2 /= area;

//                    if (i != 18 && i != 21 && i != 24 && i != 27)
//                    {
//                        continue;
//                    }
//                    if (i != 21)
//                        continue;

                                        if (i == 21 || i == 18)
                                        {
                                            continue;
                                        }
                    // Colouring edges green
                    if (abs(w0) < std::numeric_limits<float>::epsilon() ||
                            abs(w1) < std::numeric_limits<float>::epsilon() ||
                            abs(w2) < std::numeric_limits<float>::epsilon())
                    {
                        painter.setPen(QColor(0, 255,  0, 255));
                        painter.drawPoint(x, y);
//                        std::cout << w0 << ' ' << w1 << ' ' << w2 << std::endl;
                        continue;
                    }
//                    std::cout << V0 << ' ' << V1 << ' ' << V2 << ' ' << area << std::endl;
                    painter.setPen(QColor(((i / 3) + 3) * 9, 0 , ((i / 3) + 3) * 9, 122));
                    painter.drawPoint(x, y);
                }
            }
        }
    }
}


















