/**
 * DISCLAIMER: This source code has been adapted form the
 * glwidget class of the Hello GL2 Example inclued in the
 * Qt 5.11.2 package.
 * For more information: http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html
 */

#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "BasicStructures/mesh.h"
#include <cmath>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <QKeyEvent>

/**
 * @brief The OpenGLWidget class represents a widget which renders a 3D Mesh
 *  structure.
 */
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
private:
    QOpenGLShaderProgram * shader;
    QVector3D lightPosition;
    QMatrix4x4 projection;
    QMatrix4x4 cameraLocation;
    QVector<GLfloat> data;
    QOpenGLBuffer buffer;
    QPoint lastPosition;
    int interestPoints;
    int vertexes;
    int locMvMatrix;
    int locNormalMatrix;
    int locLight;
    int locProjection;
    int locColor;
    float depth;
    float cameraPositionX;
    float cameraPositionY;
    float angleX;
    float angleY;
    float angleZ;
    float farPlaneDistance;
    float proportion;

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

    /**
     * @brief initializePositions Initializes all the positions related with
     *  the elements in the scene.
     */
    void initializePositions();

    void renderInterestPointsInBuffer();
protected:

    /**
     * @brief initializeGL Inherited. Initializes the scene.
     */
    void initializeGL() override;

    /**
     * @brief paintGL Inherited. Draw the vertices contained in the drawing buffer,
     *  whithin the context.
     */
    void paintGL() override;

    /**
     * @brief resizeGL Inherited. Fixes the scene's aspect ratio according
     *  to the widget size.
     * @param w The width of the widget
     * @param h The height of the widget.
     */
    void resizeGL(int w, int h) override;

    /**
     * @brief wheelEvent Inherited. Controls the wheel event to zoom-in and zoom-out.
     */
    void wheelEvent(QWheelEvent *) override;

    /**
     * @brief mousePressEvent Inherited. Controls the mouse press event to give the
     *  focus to the widget and define the starting point of the drag event
     */
    void mousePressEvent(QMouseEvent *) override;

    /**
     * @brief mouseMoveEvent Inherited. Controls the mouse move event while dragging
     *  the screen. Rotates the scene accordint to the mouse movement.
     */
    void mouseMoveEvent(QMouseEvent *) override;

    /**
     * @brief keyPressEvent Inherited. Controls the key events. The up, down, left
     *  and right to displace the scene along the X and Y axis.
     */
    void keyPressEvent(QKeyEvent *) override;

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

    void drawInterestPoints();

    void reallocateBufferWithInteresPoints(vector<Vertex *> * interestPoints);
};

#endif
