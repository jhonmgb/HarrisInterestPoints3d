#ifndef RENDERUTIL_H
#define RENDERUTIL_H

#include <QVector3D>
#include <QPoint>
#include <QOpenGLFunctions>

/**
 * @brief The RenderUtil class contains general parameters for rendering the 3d
 *  meshes.
 */
class RenderUtil
{
public:

    /**
     * @brief generateSphere function to get the coordinates that draws an
     *  sphere in OpenGL (No GLU needed). This code is adapted from
     *  http://www.cburch.com/cs/490/sched/feb8/
     * @param rad the radius of the sphere.
     * @param lats the number of latitudes.
     * @param longs the number of longitudes.
     * @param vtxs counter of vertexes, needed to fill the drawing buffer
     *  accordingly.
     * @param centre the centre where the sphere should be placed.
     * @return array of GLfloats with the coordinates of the vertexes of the
     *  sphere.
     */
    static GLfloat * generateSphere(
        double rad, int lats, int longs, int & vtxs, QVector3D & centre);

    /**
     * @brief backgroundColour constant representing the scene's background
     *  colour in RGB.
     */
    static const QVector3D backgroundColour;

    /**
     * @brief meshColour constant representing the mesh colour in RGB.
     */
    static const QVector3D meshColour;

    /**
     * @brief interestPointColour constant representing the colour in RGB of the
     *  interest points.
     */
    static const QVector3D interestPointColour;

    /**
     * @brief sphereLats constant representing the latitudes of the spheres who
     *  draws an interest point.
     */
    static const int sphereLats;

    /**
     * @brief sphereLats constant representing the longitudes of the spheres
     *  who draws an interest point.
     */
    static const int sphereLongs;

private:

    /**
     * @brief RenderUtil::RenderUtil No operational constructor.
     *  This class only contains static functions and parameters.
     */
    RenderUtil();
};

#endif // RENDERUTIL_H
