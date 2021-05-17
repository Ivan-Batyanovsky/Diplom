#include "myClasses/Renderbase.h"

RenderBase::RenderBase()
{
    scaleKoefs_ = {1.0f, 1.0f, 1.0f, 1.0f};
    translateKoefs_ = {0.0f, 0.0f, 0.0f, 1.0f};
    rotateAngle_ = {0.0f, 0.0f, 0.0f, 1.0f};

    modelViewProjectMat_.setIdentity();
    trianglesPoints_ = {};
    clBuffer_ = {};
    zBuffer_ = {};
}

void RenderBase::loadCube(const Vec4f posAndEdge)
{
    Cube testCube(posAndEdge);
    testCube.getIndexes(trianglesPoints_);
}

void RenderBase::resizeBuffers(const size_t w, const size_t h)
{
    if (clBuffer_.getRows() != h || clBuffer_.getColumns() != w)
    {
        clBuffer_.resize(h, w);
        zBuffer_.resize(h, w);
    }
}

void RenderBase::setMVPmatrix(size_t w , size_t h)
{
    float angleOfView = 45.0f, near = -2.0f, far = -50.0f;
//    modelViewProjectMat_.setIdentity();
    modelViewProjectMat_.setPerspective(angleOfView, near, far, w / float(h));
//    std::cout << modelViewProjectMat_;
}

void RenderBase::findBoundingBox(int x0, int y0, int x1, int y1, int x2, int y2, int &xmin, int &ymin, int &xmax, int &ymax)
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

bool RenderBase::pixelOverlapsTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int x, int y, float &w0, float &w1, float &w2)
{
    w0 = edgeFunction(x1, y1, x2, y2, x, y);
    if (w0 < 0) return false;

    w1 = edgeFunction(x2, y2, x0, y0, x, y);
    if (w1 < 0) return false;

    w2 = edgeFunction(x0, y0, x1, y1, x, y);
    if (w2 < 0) return false;

    return true;
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

Mat44f RenderBase::getTranslation() const
{
    Mat44f translationMatrix({
                                 1.0f, 0.0f, 0.0f, translateKoefs_.getX(),
                                 0.0f,1.0f, 0.0f, translateKoefs_.getY(),
                                 0.0f, 0.0f, 1.0f, translateKoefs_.getZ(),
                                 0.0f, 0.0f, 0.0f, 1.0f
                             });
    return translationMatrix;
}

void RenderBase::renderScene(QPainter &painter, size_t w, size_t h)
{
    for (size_t i = 0; i != trianglesPoints_.size(); i += 3)
    {
        // Triangle vertices
        Mat44f trans = getTranslation();
        Vec4f V0 =  trans * trianglesPoints_[i];
            V0 = V0 * modelViewProjectMat_;
        Vec4f V1 = trans * trianglesPoints_[i + 1];
            V1 = V1 * modelViewProjectMat_;
        Vec4f V2 = trans * trianglesPoints_[i + 2];
            V2 = V2* modelViewProjectMat_;
        V0.divByW();
        V1.divByW();
        V2.divByW();
//        Mat44f rotateMatrix = getRotation();
        Mat44f rotateMatrix = getTranslation();
        Mat44f scaleMatrix = getScaling();
        V0 = V0 * rotateMatrix;
        V1 = V1 * rotateMatrix;
        V2 = V2 * rotateMatrix;

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
//        Buffers::ColourBuffer clBuffer(w, h);
//        Buffers::fDepthBuffer zBuffer(w, h);

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
