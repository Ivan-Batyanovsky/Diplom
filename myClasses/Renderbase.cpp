#include <fstream>
#include <sstream>
#include <algorithm>
#include "Renderbase.h"

RenderBase::RenderBase()
{
    polygons_ = {};
    trianglesPoints_ = {};
    texturesPoints_ = {};
    normalsPoints_ = {};
    textures_ = {};

    float xy = -1.2f, z = -3.2f;
    translateKoefs_ = {xy, xy, z, 0.0f};
    scaleKoefs_ = {1.0f, 1.0f, 1.0f, 1.0f};
    rotateAngle_ = {0.0f, 0.0f, 0.0f, 0.0f};

    lightDirection_ = { -1.0f, -1.0f,  -z, 0.0f};
    lightDirection_.normalize();
}

float RenderBase::convertToPixelX(Vec4f & x, const size_t w)
{
    return (x.getX() + 1) / 2 * w;
}

float RenderBase::convertToPixelY(Vec4f & y, const size_t h)
{
    return (1 - y.getY()) / 2 * h;
}

bool RenderBase::pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float & w0, float & w1, float & w2)
{
    w0 = edgeFunction(x1, y1, x2, y2, x, y);
    if (w0 < 0)
        return false;

    w1 = edgeFunction(x2, y2, x0, y0, x, y);
    if (w1 < 0)
        return false;

    w2 = edgeFunction(x0, y0, x1, y1, x, y);
    if (w2 < 0)
        return false;

    return true;
}
void RenderBase::findBoundingBox(size_t x0, size_t y0, size_t x1, size_t y1, size_t x2, size_t y2, size_t & xmin, size_t & ymin, size_t & xmax, size_t & ymax)
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



void RenderBase::initMVPmatrix(size_t w, size_t h)
{
    float angleOfView = 60.0f, near = 1.0f, far = 100.0f;

    modelViewProjectMat_.setPerspective(angleOfView, near, far,  float(w) / float(h));

    Mat44f scale = getScaling(), translate = getTranslation(), rotate = getRotation();
//    modelViewProjectMat_.setIdentity();
//    modelViewProjectMat_ = modelViewProjectMat_ * scale * translate;
    modelViewProjectMat_ = modelViewProjectMat_ * rotate * scale * translate;

}

Mat44f RenderBase::getRotation() const
{
    float alpha = rotateAngle_.getZ(), beta = rotateAngle_.getY(), gamma = rotateAngle_.getX();
    Mat44f rotationMatrix({
        cosf(alpha) * cosf(beta), cosf(alpha) * sinf(beta) * sinf(gamma) - cosf(gamma) * sinf(alpha),  cosf(alpha) * cosf(gamma) * sinf(beta) + sinf(gamma) * sinf(alpha), 0.0f,
        sinf(alpha) * cosf(beta),  sinf(alpha) * sinf(beta) * sinf(gamma) + cosf(alpha) * cosf(gamma), sinf(alpha) * sinf(beta) * cosf(gamma) - cosf(alpha) * sinf(gamma), 0.0f ,
        -sinf(beta),                          sinf(gamma) * cosf(beta),                                                                                cosf(gamma) * cosf(beta),                                                                               1.0f});
    return rotationMatrix;
}

Mat44f RenderBase::getScaling() const
{
    Mat44f scalingMatrix({
                                 scaleKoefs_.getX(), 0.0f, 0.0f, 0.0f,
                                 0.0f, scaleKoefs_.getY(), 0.0f, 0.0f,
                                 0.0f, 0.0f, scaleKoefs_.getZ(), 0.0f,
                                 0.0f, 0.0f, 0.0f, 1.0f
                             });
    return scalingMatrix;
}

// tempColour remove later(has been used for tests)
void RenderBase::qtDraw(QPainter & painter)
{
    Buffers::uchar4 pixelColour;
    size_t w = clBuffer_.getWidth(), h = clBuffer_.getHeight();
    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
                pixelColour = clBuffer_.get(x, y);
                painter.setPen(QColor(pixelColour.x_, pixelColour.y_, pixelColour.z_, pixelColour.w_));
                painter.drawPoint(x, y);
        }
    }
}

bool RenderBase::topLeftRule(Vec4f V0, Vec4f V1, Vec4f V2, float w0, float w1, float w2)
{
    Vec4f edge0 = V2 - V1;
    Vec4f edge1 = V0 - V2;
    Vec4f edge2 = V1 - V0;

    bool overlaps = true;

    // If the point is on the edge, test if it is a top or left edge,
    // otherwise test if  the edge function is positive
    overlaps &= (w0 == 0 ? ((edge0.getY() == 0 && edge0.getX() > 0) ||  edge0.getY() > 0) : (w0 > 0));
    overlaps &= (w1 == 0 ? ((edge1.getY() == 0 && edge1.getX() > 0) ||  edge1.getY() > 0) : (w1 > 0));
    overlaps &= (w2 == 0 ? ((edge2.getY() == 0 && edge2.getX() > 0) ||  edge2.getY() > 0) : (w2 > 0));

    if (overlaps)
        return true;
    return false;
}

void RenderBase::loadTextures()
{
    for (size_t i = 0; i < textures_.size(); i++)
        textures_[i].setZebraLike();
    textures_[0].setZebraLike2();
}

void RenderBase::loadOBJ(std::string objFileName)
{
    std::ifstream objFile(objFileName);
    if (!objFile.is_open())
    {
        std::cout << "Cant open file\n";
    }
    std::stringstream stringStream;

    float v0, v1, v2;

    std::string textLine, stringPlug;

    size_t textureCount = 0;

    myPolygon triangle;

    while (std::getline(objFile, textLine))
    {
        if (textLine[0] == 'v' && textLine[1] == 't')
        {
            stringStream << textLine;
            stringStream >> stringPlug >> v0 >> v1;
            texturesPoints_.push_back({v0, v1, 0.0f, 1.0f});

            stringStream.clear();
            stringStream.str("");

            continue;
        }

        if (textLine[0] == 'v' && textLine[1] == 'n')
        {
            stringStream << textLine;
            stringStream >> stringPlug >> v0 >> v1 >> v2;
            normalsPoints_.push_back({v0, v1, v2, 1.0f});

            stringStream.clear();
            stringStream.str("");

            continue;
        }

        if (textLine[0] == 'v' && textLine[1] == ' ')
        {
            stringStream << textLine;
            stringStream >> stringPlug >> v0 >> v1 >> v2;
            trianglesPoints_.push_back({v0, v1, v2, 1.0f});

            stringStream.clear();
            stringStream.str("");

            continue;
        }

        if (textLine[0] == 'f' && textLine[1] == ' ')
        {
            std::string s;

            size_t vertice0, verticeTexture0, verticeNormal0;
            size_t vertice1, verticeTexture1, verticeNormal1;
            size_t vertice2, verticeTexture2, verticeNormal2;

            stringStream << textLine;

            stringStream >> stringPlug >> vertice0;
            stringStream.get();
            stringStream >> verticeTexture0;
            stringStream.get();
            stringStream >> verticeNormal0;

            stringStream  >> vertice1;
            stringStream.get();
            stringStream >> verticeTexture1;
            stringStream.get();
            stringStream >> verticeNormal1;

            stringStream  >> vertice2;
            stringStream.get();
            stringStream >> verticeTexture2;
            stringStream.get();
            stringStream >> verticeNormal2;

            stringStream.clear();
            stringStream.str("");

            triangle.setTextureID(textureCount);
            triangle.setV(vertice0, vertice1, vertice2);
            triangle.setVT(verticeTexture0, verticeTexture1, verticeTexture2);
            triangle.setVN(verticeNormal0, verticeNormal1, verticeNormal2);
            polygons_.push_back(triangle);

            continue;
        }

        if (textLine.find("usemtl") != std::string::npos)
        {
            std::string textureFileName = "C:/" + textLine.substr(7, textLine.size() - 7) + ".png";
            std::cout << textureFileName << std::endl;
            Buffers::Texture texture;

            texture.loadPNG(textureFileName);
            texture.setTextureID(textureCount++);
            textures_.push_back(texture);

            stringStream.clear();
            stringStream.str("");

            continue;
        }
    }
    objFile.close();
}

bool RenderBase::projectVertices(myPolygon & triangle, Vec4f &V0, Vec4f &V1, Vec4f &V2)
{

    size_t verticeID0, verticeID1, verticeID2;
    triangle.getV(verticeID0, verticeID1, verticeID2);

    V0 = modelViewProjectMat_ * trianglesPoints_[verticeID0 - 1];
    V1 = modelViewProjectMat_ * trianglesPoints_[verticeID1 - 1];
    V2 = modelViewProjectMat_ * trianglesPoints_[verticeID2 - 1];

//    V0 = trianglesPoints_[verticeID0 - 1] * modelViewProjectMat_;
//    V1 = trianglesPoints_[verticeID1 - 1] * modelViewProjectMat_;
//    V2 = trianglesPoints_[verticeID2 - 1] *modelViewProjectMat_;

    V0.divByW();
    V1.divByW();
    V2.divByW();

    if ( abs(V0.getX()) > 1 || abs(V0.getY()) > 1 || abs(V0.getZ()) > 1)
        return false;
    if ( abs(V1.getX()) > 1 || abs(V1.getY()) > 1 || abs(V1.getZ()) > 1)
        return false;
    if ( abs(V2.getX()) > 1 || abs(V2.getY()) > 1 || abs(V2.getZ()) > 1)
        return false;

    return true;
}

bool RenderBase::getArea(Vec4f &V0, Vec4f &V1, Vec4f &V2, float & area)
{
    area = edgeFunction(V0.getX(), V0.getY(), V1.getX(), V1.getY(), V2.getX(), V2.getY());

    if (abs(area) < std::numeric_limits<float>::epsilon())
        return false;

    if (area > 0)
    {
        Vec4f temp = V1;
        V1 = V2;
        V2 = temp;
        area *= -1;
    }

    return true;
}

void RenderBase::getRasterPoints(Vec4f & V0, Vec4f & V1, Vec4f & V2, float & x0, float & y0, float & x1, float & y1, float & x2, float & y2, float & area, size_t windowWidth, size_t windowHeight)
{
    x0 = convertToPixelX(V0, windowWidth);
    x1 = convertToPixelX(V1, windowWidth);
    x2 = convertToPixelX(V2, windowWidth);
    y0 = convertToPixelY(V0, windowHeight);
    y1 = convertToPixelY(V1, windowHeight);
    y2 = convertToPixelY(V2, windowHeight);

    area = edgeFunction(x0, y0, x1, y1, x2, y2);
//    if (area > 0)
//    {
//        Vec4f tempV = V2;
//        V2 = V0;
//        V0 = tempV;
//        float temp = x0;
//        x0 = x2;
//        x2 = temp;
//        temp = y0;
//        y0 = y2;
//        y2 = temp;
//        area *= -1.0f;
//    }
}

void RenderBase::getBoundingBox(float x0, float y0, float x1, float y1, float x2, float y2, size_t & xmax, size_t & ymax, size_t & xmin, size_t & ymin)
{
    xmax = 0, ymax = 0;
    xmin = SIZE_MAX, ymin = SIZE_MAX;
    findBoundingBox(x0, y0, x1, y1, x2, y2, xmin, ymin, xmax, ymax);
}

void RenderBase::getDepth(float & currentDepth, Vec4f & V0, Vec4f & V1, Vec4f & V2, float & w0, float & w1, float & w2, const float & area)
{
    w0 /= abs(area);
    w1 /= abs(area);
    w2 /= abs(area);

    currentDepth = (w0 / V0.getZ() +  w1 / V1.getZ() + w2 / V2.getZ());
}

bool RenderBase::isOnEdge(float w0, float w1, float w2)
{
    return (abs(w0) < std::numeric_limits<float>::epsilon() || abs(w1) < std::numeric_limits<float>::epsilon() || abs(w2) < std::numeric_limits<float>::epsilon());
}

void RenderBase::setBuffersValues(int x, int y, const float & currentDepth, Buffers::uchar4 & pixel)
{
    clBuffer_.set(x, y, pixel);
    zBuffer_.set(x, y, currentDepth);
}

void RenderBase::getTextureColour(Buffers::uchar4 & pixelColour, const myPolygon & triangle, const float &currentDepth, const float &w0, const float &w1, const float &w2, const float &z0, const float &z1, const float &z2)
{
    size_t currentTextureID = triangle.getTextureID();
    size_t vt0, vt1, vt2;

    triangle.getVT(vt0, vt1, vt2);

    float x0 = texturesPoints_[vt0 - 1].getX(), x1 = texturesPoints_[vt1 - 1].getX(), x2 = texturesPoints_[vt2 - 1].getX();
    float y0 = texturesPoints_[vt0 - 1].getY(), y1 = texturesPoints_[vt1 - 1].getY(), y2 = texturesPoints_[vt2 - 1].getY();

    float u = currentDepth * (w0 * x0 / z0 +  w1 * x1 / z1 + w2 * x2 / z2);
    float v = currentDepth * (w0 * y0 / z0 +  w1 * y1 / z1 + w2 * y2 / z2);

    if (u > 1) u = 1.0f;
    if (v > 1) v = 1.0f;

    Vec4f lightValues = lightShader(triangle, w0, w1, w2, currentDepth, z0, z1, z2);

    pixelColour =  textures_[currentTextureID - 1].get(u, v);
    pixelColour.x_ *= lightValues.getX();
    pixelColour.y_ *= lightValues.getY();
    pixelColour.z_ *= lightValues.getZ();
}

void RenderBase::checkBoundingBox(size_t & xmax, size_t & ymax)
{
    if (xmax == clBuffer_.getWidth())
        xmax -= 1;
    if (ymax == clBuffer_.getHeight())
        ymax -= 1;
}

void RenderBase::precomputeZ(Vec4f & V0, Vec4f & V1, Vec4f & V2)
{
    V0.setZ(1 / V0.getZ());
    V1.setZ(1 / V1.getZ());
    V2.setZ(1 / V2.getZ());
}

void RenderBase::saveZtoVector(Vec4f &savedZ, const Vec4f &V0, const Vec4f &V1, const Vec4f &V2)
{
    savedZ.setX(V0.getZ());
    savedZ.setY(V1.getZ());
    savedZ.setZ(V2.getZ());
}

void RenderBase::testBaryc(Vec4f &V0, Vec4f &V1, Vec4f &V2, float &w0, float &w1, float &w2, size_t &x, size_t &y, float &currentDepth)
{
    float xNDC = currentDepth * (V0.getX() * w0 + V1.getX() * w1 + V2.getX() * w2);
    float yNDC = currentDepth * (V0.getY() * w0 + V1.getY() * w1 + V2.getY() * w2);
}

Vec4f RenderBase::lightShader(const myPolygon &triangle, const float &w0, const float &w1, const float &w2, const float &currentDepth, const float &z0, const float &z1, const float &z2)
{
    size_t v0, v1, v2;
    size_t vn0, vn1, vn2;

    triangle.getV(v0, v1, v2);

    float x0 = trianglesPoints_[v0 - 1].getX(), x1 = trianglesPoints_[v1 - 1].getX(), x2 = trianglesPoints_[v2 - 1].getX();
    float y0 = trianglesPoints_[v0 - 1].getY(), y1 = trianglesPoints_[v1 - 1].getY(), y2 = trianglesPoints_[v2 - 1].getY();

    float currentX = currentDepth * (w0 * x0 * z0 +  w1 * x1 * z1 + w2 * x2 * z2);
    float currentY = currentDepth * (w0 * y0 * z0 +  w1 * y1 * z1 + w2 * y2 * z2);
    float currentZ = currentDepth;

    Vec4f v(currentX, currentY, currentZ);
    triangle.getVN(vn0, vn1, vn2);
    x0 = normalsPoints_[vn0 - 1].getX(), x1 = normalsPoints_[vn1 - 1].getX(), x2 = normalsPoints_[vn2 - 1].getX();
    y0 = normalsPoints_[vn0 - 1].getY(), y1 = normalsPoints_[vn1 - 1].getY(), y2 = normalsPoints_[vn2 - 1].getY();

    currentX = currentDepth * (w0 * x0 * z0 +  w1 * x1 * z1 + w2 * x2 * z2);
    currentY = currentDepth * (w0 * y0 * z0 +  w1 * y1 * z1 + w2 * y2 * z2);

    x0 = normalsPoints_[vn0 - 1].getZ(), x1 = normalsPoints_[vn1 - 1].getZ(), x2 = normalsPoints_[vn2 - 1].getZ();
    currentZ = currentDepth * (w0 * x0 * z0 +  w1 * x1 * z1 + w2 * x2 * z2);

    Vec4f n(currentX, currentY, currentZ);
    n.normalize();

    Vec4f result(0.0f ,0.0f, 0.0f);

    Vec4f ambientKoef(0.800000f, 0.800000f, 0.800000f);
    Vec4f diffuseKoef(0.640000f, 0.640000f, 0.640000f);
    Vec4f specularKoef(0.139456f, 0.139456f, 0.139456f);
    size_t shininess = 32;

    Vec4f Idiff = diffuseKoef * std::max(n.dot(lightDirection_), 0.3f);

    Vec4f e = v * -1;
    e.normalize();

    Vec4f r = lightDirection_ - n * 2 * (lightDirection_.dot(n));
    r = r * -1;
    r.normalize();

    Vec4f Ispecular = specularKoef * std::pow(std::max(r.dot(e), 0.0f), shininess);

    return Idiff;
}

Mat44f RenderBase::getTranslation() const
{
    Mat44f translationMatrix({
                                 1.0f, 0.0f, 0.0f, translateKoefs_.getX(),
                                 0.0f, 1.0f, 0.0f, translateKoefs_.getY(),
                                 0.0f, 0.0f, 1.0f, translateKoefs_.getZ(),
                                 0.0f, 0.0f, 0.0f, 1.0f
                             });
    return translationMatrix;
}

void RenderBase::loadCube(Cube cube)
{
    cube.getIndexes(trianglesPoints_);
    std::string textureFileName = "C:/minecraftBlock.png";
    std::cout << textureFileName << std::endl;
    Buffers::Texture texture;

    texture.loadPNG(textureFileName);
    texture.setTextureID(0);
    textures_.push_back(texture);
}

void RenderBase::resizeBuffers(size_t w, size_t h)
{
        clBuffer_.resize(w, h);
        zBuffer_.resize(w, h);
}

float RenderBase::edgeFunction(float ax, float ay, float bx, float by, float x, float y)
{
    return ((x - ax) * (by - ay) - (y - ay) * (bx - ax));
}

void RenderBase::renderScene(size_t windowWidth, size_t windowHeight)
{
    size_t polygonsNumber  = polygons_.size();
    for (size_t i = 0; i < polygonsNumber; i++)
    {
        // Triangle vertices
        Vec4f V0, V1, V2;
        myPolygon triangle = polygons_[i];

        // Projecting vertices to canvas
        if (projectVertices(triangle, V0, V1, V2) == false)
        {
//            std::cout << i << "-th triangle is not visible\n";
            continue;
        }

        // Barycentric Coordinates
        float w0, w1, w2, area;

        // Pixels of triangle and bounding box
        float x0, x1, x2, y0, y1, y2;
        size_t xmax, ymax, xmin, ymin;

        // Computing raster space points of triangle vertices
        getRasterPoints(V0, V1, V2, x0, y0, x1, y1, x2, y2, area , windowWidth, windowHeight);

        // Finding bounding box coords
        getBoundingBox(x0, y0, x1, y1, x2, y2, xmax, ymax, xmin, ymin);
        checkBoundingBox(xmax, ymax);

        // Current pixel depth
        float currentDepth;

        // Saving z coords
        Vec4f savedZ;
        saveZtoVector(savedZ, V0, V1, V2);

        // Current pixel colour
        Buffers::uchar4 pixelColour;

        // Precomputing z0 = 1 / z0, z1 = ...
        precomputeZ(V0, V1, V2);

        // Looping over window
        for (size_t y = ymin; y <= ymax; y++) {
            for (size_t x = xmin; x <= xmax; x++) {
                if (pixelOverlapsTriangle(x0, y0, x1, y1, x2, y2, x, y, w0, w1, w2))
                {
                    // Calculating pixel depth
                    getDepth(currentDepth, V0, V1, V2, w0, w1, w2, area);
                    testBaryc(V0, V1, V2, w0, w1, w2, x, y, currentDepth);


                    if (currentDepth < zBuffer_.get(x, y))
                    {
                        if (isOnEdge(w0, w1, w2))
                        {
                            // Colouring edges green
                            pixelColour = {0, 255,  0, 255};
                            setBuffersValues(x, y, currentDepth, pixelColour);

                            continue;
                        }

                        // Colouring inside triangle
                        getTextureColour(pixelColour, triangle, currentDepth, w0, w1, w2, V0.getZ(), V1.getZ(), V2.getZ());
                        setBuffersValues(x, y, currentDepth, pixelColour);
                    }
                }
            }
        }
    }
}
