#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "BasicStructures/mesh.h"
#include <cmath>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
private:
    QOpenGLShaderProgram * shader;
    QMatrix4x4 projection;
    QMatrix4x4 cameraLocation;
    QOpenGLBuffer buffer;
    int vertexes;
    int locProjection;
    int locMvMatrix;
    int locNormalMatrix;

    /**
     * @brief addToData Add a face represented by three QVector3D (And its normal
     * vectors), to a vector of QLfloats, by using a pointer to GLfloat as an
     * iterator.
     */
    void addToData(QVector3D *, QVector3D, GLfloat * &);

    /**
     * @brief calculateDepth calculates the right z displacement of the camara,
     *  to display the whole mesh. The
     * @param max is the most outer-top-left point of the mesh bounding box
     * @param min is the most inner-down-right point of the mesh bounding box
     */
    float calculateDepth(QVector3D & max, QVector3D & min);

protected:
    void initializeGL() override;
    void paintGL() override;

public:
    /**
     * @brief OpenGLWidget constructor
     * @param parent pointer to the parent widget.
     */
    OpenGLWidget(QWidget * parent = 0);
    ~OpenGLWidget();

    /**
     * @brief drawMesh Process and render the 3D mesh in the Opengl widget.
     * @param mesh The mesh to be rendered.
     */
    void drawMesh(Mesh * mesh);
};

#endif
