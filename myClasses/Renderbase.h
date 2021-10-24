#ifndef RENDERBASE_H
#define RENDERBASE_H

<<<<<<< HEAD
#include "myClasses/Mat44f.h"
=======
>>>>>>> master
#include "myClasses/Vec4f.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include <QPainter>
<<<<<<< HEAD
=======

>>>>>>> master
class RenderBase
{
public:
    RenderBase();
<<<<<<< HEAD
    void changeRotation(const Vec4f rotateAngle) { rotateAngle_ = rotateAngle_ + rotateAngle; }
    void changeTranslation(const Vec4f TranslateKoefs) { translateKoefs_ = translateKoefs_ + TranslateKoefs; }
    void changeScaling(const Vec4f ScaleKoefs) {scaleKoefs_ = scaleKoefs_ + ScaleKoefs; }
    std::vector<Vec4f> getPoints() const {return trianglesPoints_;}
    Mat44f getMVP() const {return modelViewProjectMat_;}
    void initMVPmatrix(size_t w, size_t h);
    void loadCube(Cube cube);
    void resizeBuffers(size_t w, size_t h);
    void renderScene(QPainter & painter, size_t w, size_t h);
    float edgeFunction(float ax, float ay, float bx, float by, float x, float y);
    void findBoundingBox(int x0, int y0, int x1, int y1, int x2, int y2, int &xmin, int &ymin, int &xmax, int &ymax);
    int convertToPixelX(Vec4f &x, const size_t w);
    int convertToPixelY(Vec4f &y, const size_t h);
    bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float &w0, float &w1, float &w2);
    Mat44f getRotation() const;
    Mat44f getTranslation() const;
    Mat44f getScaling() const;

=======
//    RenderBase(const size_t w, const size_t h);

    void loadCube(const Vec4f posAndEdge);

    Buffers::ColourBuffer getColourBuffer() const { return clBuffer_; }
    Buffers::fDepthBuffer getDepthBuffer() const { return zBuffer_; }

    void resizeBuffers(const size_t w, const size_t h);
    void changeRotation(const Vec4f rotateAngle) { rotateAngle_ = rotateAngle_ + rotateAngle; }
    void changeTranslation(const Vec4f TranslateKoefs) { translateKoefs_ = translateKoefs_ + TranslateKoefs; }
    void changeScaling(const Vec4f ScaleKoefs) {scaleKoefs_ = scaleKoefs_ + ScaleKoefs; }
    void setMVPmatrix(size_t w, size_t h);
    void renderScene(QPainter & painter, size_t w, size_t h);
    Mat44f getRotation() const;
    Mat44f getTranslation() const;
    Mat44f getScaling() const;
>>>>>>> master
private:
    Vec4f scaleKoefs_;
    Vec4f translateKoefs_;
    Vec4f rotateAngle_;

<<<<<<< HEAD
=======
    float edgeFunction(float ax, float ay, float bx, float by, float x, float y) { return ((x - ax) * (by - ay) - (y - ay) * (bx - ax)); }
    int convertToPixelX(Vec4f & x, const size_t w) { return (x.getX() + 1) / 2 * w; }
    int convertToPixelY(Vec4f & y, const size_t h) { return (1 - y.getY()) / 2 * h; }
    void findBoundingBox(int x0, int y0, int x1, int y1, int x2, int y2, int & xmin, int & ymin, int & xmax, int & ymax);
    bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float & w0, float & w1, float & w2);

>>>>>>> master
    Mat44f modelViewProjectMat_;
    std::vector<Vec4f> trianglesPoints_;
    Buffers::ColourBuffer clBuffer_;
    Buffers::fDepthBuffer zBuffer_;
};

#endif // RENDERBASE_H
