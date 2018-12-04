#ifndef RENDERUTIL_H
#define RENDERUTIL_H

#include <QVector3D>
#include <QPoint>
#include <QOpenGLFunctions>

class RenderUtil
{
public:
    static GLfloat * generateSphere(
        int rad, int lats, int longs, int & vtxs, QVector3D & centre);

    static const QVector3D backgroundColour;
    static const QVector3D meshColour;
    static const QVector3D interestPointColour;
    static const int sphereLats;
    static const int sphereLongs;

private:
    RenderUtil();
};

#endif // RENDERUTIL_H
