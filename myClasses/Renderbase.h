#ifndef RENDERBASE_H
#define RENDERBASE_H

#include "myClasses/Mat44f.h"
#include "myClasses/Vec4f.h"
#include "myClasses/Buffers.h"
#include "myClasses/Cube.h"
#include "myClasses/polygon.h"
#include <QPainter>

class RenderBase
{
public:
    RenderBase();
    void changeRotation(const Vec4f rotateAngle) { rotateAngle_ = rotateAngle_ + rotateAngle; }
    void changeTranslation(const Vec4f TranslateKoefs) { translateKoefs_ = translateKoefs_ + TranslateKoefs; }
    void changeScaling(const Vec4f ScaleKoefs) { scaleKoefs_ = scaleKoefs_ + ScaleKoefs; }
    std::vector<Vec4f> getPoints() const {return trianglesPoints_;}
    Mat44f getMVP() const {return modelViewProjectMat_;}
    void initMVPmatrix(size_t w, size_t h);
    void loadCube(Cube cube);
    void resizeBuffers(size_t w, size_t h);
    void renderScene(size_t w, size_t h);
    float edgeFunction(float ax, float ay, float bx, float by, float x, float y);
    void findBoundingBox(size_t x0, size_t y0, size_t x1, size_t y1, size_t x2, size_t y2, size_t &xmin, size_t &ymin, size_t &xmax, size_t &ymax);
    float convertToPixelX(Vec4f &x, const size_t w);
    float convertToPixelY(Vec4f &y, const size_t h);
    bool pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float &w0, float &w1, float &w2);
    Mat44f getRotation() const;
    Mat44f getTranslation() const;
    Mat44f getScaling() const;
    void qtDraw(QPainter & painter);
    bool topLeftRule(Vec4f V0, Vec4f V1, Vec4f V2, float w0, float w1, float w2);
    void loadTextures();
    void loadOBJ(std::string objFileName);
    bool projectVertices(myPolygon & triangle, Vec4f & V0, Vec4f & V1, Vec4f & V2);
    bool getArea(Vec4f & V0, Vec4f & V1, Vec4f & V2, float &area);
    void getRasterPoints(Vec4f &V0, Vec4f &V1, Vec4f &V2, float & x0, float & y0, float & x1, float & y1, float & x2, float & y2, float & area, size_t windowWidth, size_t windowHeight);
    void getBoundingBox(float x0, float y0, float x1, float y1, float x2, float y2, size_t & xmax, size_t & ymax, size_t & xmin, size_t & ymin);
    void divArea(float & w0, float & w1, float & w2, float & area);
    void getDepth(float &currentDepth, Vec4f &V0, Vec4f &V1, Vec4f &V2, float &w0, float &w1, float &w2, const float &area);
    bool isOnEdge(float w0, float w1, float w2);
    void setBuffersValues(int x, int y, const float &currentDepth, Buffers::uchar4 & pixel);
    void getTextureColour(Buffers::uchar4 & pixelColour, const myPolygon & triangle, const float & currentDepth, const float & w0, const float & w1, const float & w2, const float & z0, const float & z1, const float & z2);
    void checkBoundingBox(size_t & xmax, size_t & ymax);
    void precomputeZ(Vec4f & V0, Vec4f & V1, Vec4f & V2);
    void lightShader(Vec4f & V0, Vec4f & V1, Vec4f & V2);
    void saveZtoVector(Vec4f & savedZ, const Vec4f & V0, const Vec4f & V1, const Vec4f & V2);
    void testBaryc(Vec4f & V0, Vec4f & V1, Vec4f & V2, float & w0, float &w1, float &w2, size_t &x, size_t & y, float & currentDepth);
    Vec4f lightShader(const myPolygon &triangle, const float &w0, const float &w1, const float &w2, const float &currentDepth, const float &z0, const float &z1, const float &z2);
private:

    // Scaling, translate, rotate vectors and model * view * project matrice
    Vec4f scaleKoefs_;
    Vec4f translateKoefs_;
    Vec4f rotateAngle_;
    Mat44f modelViewProjectMat_;

    // Light
    Vec4f lightDirection_;

    // Containers
    std::vector<Vec4f> trianglesPoints_;
    std::vector<Vec4f> texturesPoints_;
    std::vector<Vec4f> normalsPoints_;
    std::vector<myPolygon> polygons_;
    std::vector<Buffers::Texture> textures_;
    Buffers::ColourBuffer clBuffer_;
    Buffers::fDepthBuffer zBuffer_;
};

#endif // RENDERBASE_H
