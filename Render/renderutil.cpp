#include "renderutil.h"

/**
 * @brief RenderUtil::RenderUtil No operational constructor.
 *  This class only contains static functions and parameters.
 */
RenderUtil::RenderUtil()
{
    //NO operational constructor.
}

/**
 * @brief RenderUtil::generateSphere function to get the coordinates that
 *  draws an sphere in OpenGL (No GLU needed). This code is adapted from
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
GLfloat * RenderUtil::generateSphere(
    double rad, int lats, int longs, int & vtxs, QVector3D & centre)
{
    GLfloat * elems = new GLfloat[(lats)*(longs+1) * 4 * 3];
    vtxs = 0;
    for(int i = 1; i <= lats; i++)
    {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / lats);
        double z0 = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / lats);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        for(int j = 0; j <= longs; j++)
        {
            double lng = 2.0 * M_PI * (double) (j - 1) / longs;
            double x = cos(lng);
            double y = sin(lng);

           QVector3D vec1(
                centre.x() + rad * x * zr0,
                centre.y() + rad * y * zr0,
                centre.z() + rad * z0);

           QVector3D vec2(
                centre.x() + rad * x * zr1,
                centre.y() + rad * y * zr1,
                centre.z() + rad * z1);

           QVector3D normal = QVector3D::normal(vec1, vec2);

           elems[vtxs++] = vec1.x();
           elems[vtxs++] = vec1.y();
           elems[vtxs++] = vec1.z();
           elems[vtxs++] = normal.x();
           elems[vtxs++] = normal.y();
           elems[vtxs++] = normal.z();

           elems[vtxs++] = vec2.x();
           elems[vtxs++] = vec2.y();
           elems[vtxs++] = vec2.z();
           elems[vtxs++] = normal.x();
           elems[vtxs++] = normal.y();
           elems[vtxs++] = normal.z();
       }
   }

    return elems;
}

/**
 * @brief RenderUtil::backgroundColour constant representing the scene's
 *  background colour in RGB.
 */
const QVector3D RenderUtil::backgroundColour = QVector3D(0.78f,0.82f,0.88f);

/**
 * @brief RenderUtil::meshColour constant representing the mesh colour in RGB.
 */
const QVector3D RenderUtil::meshColour = QVector3D(0.39f, 1.0f, 1.0f);

/**
 * @brief RenderUtil::interestPointColour constant representing the colour
 *  in RGB of the interest points.
 */
const QVector3D RenderUtil::interestPointColour = QVector3D(1.0f, 0, 0);

/**
 * @brief RenderUtil::sphereLats constant representing the latitudes of the
 *  spheres who draws an interest point.
 */
const int RenderUtil::sphereLats = 4;

/**
 * @brief RenderUtil::sphereLats constant representing the longitudes of the
 *  spheres who draws an interest point.
 */
const int RenderUtil::sphereLongs = 4;
