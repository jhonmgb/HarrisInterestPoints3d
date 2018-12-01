#include "openglwidget.h"

/**
 * @brief OpenGLWidget constructor
 * @param parent pointer to the parent widget.
 */
OpenGLWidget::OpenGLWidget(QWidget * parent) : QOpenGLWidget (parent)
{
    shader = NULL;
    vertexes = 0;
}

OpenGLWidget::~OpenGLWidget()
{
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    //Initialize shader
    shader = new QOpenGLShaderProgram();

    shader->addShaderFromSourceFile(
        QOpenGLShader::Vertex, ":/Render/vertexshader.glsl");
    shader->addShaderFromSourceFile(
        QOpenGLShader::Fragment, ":/Render/fragmentshader.glsl");
    shader->bindAttributeLocation("vertex", 0);
    shader->bindAttributeLocation("normal", 1);
    shader->link();

    shader->bind();

    locProjection = shader->uniformLocation("projMatrix");
    locMvMatrix = shader->uniformLocation("mvMatrix");
    locNormalMatrix = shader->uniformLocation("normalMatrix");

    buffer.create();
    buffer.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    buffer.bind();
    buffer.allocate(0);

    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    buffer.release();

    shader->release();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    shader->bind();
    shader->setUniformValue(locProjection, projection);
    QMatrix4x4 identity;
    identity.setToIdentity();
    identity.rotate(45, 0,1,0);
    identity.rotate(-45, 1,0,0);
    shader->setUniformValue(locMvMatrix, cameraLocation * identity);
    QMatrix3x3 normalMatrix = identity.normalMatrix();
    shader->setUniformValue(locNormalMatrix, normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, vertexes);

    shader->release();
}

/**
 * @brief drawMesh Process and render the 3D mesh in the Opengl widget.
 * @param mesh The mesh to be rendered.
 */
void OpenGLWidget::drawMesh(Mesh * mesh)
{
    QVector3D maxVector(0.0f, 0.0f, 0.0f);
    QVector3D minVector(0.0f, 0.0f, 0.0f);

    vector<Face *> * faces = mesh->getAllFaces();
    vector<Vertex *> * vertexes = mesh->getAllVertexes();
    int coordinatesPerVertex = 3;

    this->vertexes = faces->size() * 3;

    // Creation of a vector of GLfloats where the coodinates of every vertex in the
    // mesh will be stored, along with the coordinates of its normal vector.
    QVector<GLfloat>data(this->vertexes * coordinatesPerVertex * 2);

    GLfloat * start = &data.first();
    for (int i = 0; i < faces->size(); i++)
    {
        Face * face = faces->at(i);
        int * pointsIndexes = face->getPointsInFace();
        QVector3D faceVer[3];

        float x, y, z;
        for (int j = 0; j< 3; j++)
        {
            Vertex * current = vertexes->at(pointsIndexes[j]);
            x = current->getCoordinates()[0];
            y = current->getCoordinates()[1];
            z = current->getCoordinates()[2];

            faceVer[j].setX(x);
            faceVer[j].setY(y);
            faceVer[j].setZ(z);

            maxVector.setX(x > maxVector.x()? x : maxVector.x());
            maxVector.setY(y > maxVector.y()? y : maxVector.y());
            maxVector.setZ(z > maxVector.z()? z : maxVector.z());

            minVector.setX(x < minVector.x()? x : minVector.x());
            minVector.setY(y < minVector.y()? y : minVector.y());
            minVector.setZ(z < minVector.z()? z : minVector.z());
        }

        QVector3D normal = QVector3D::normal(faceVer[0], faceVer[1], faceVer[2]);
        addToData(faceVer, normal, start);
    }

    float depth = calculateDepth(maxVector, minVector);
    cameraLocation.setToIdentity();
    cameraLocation.translate(
        -(maxVector.x() + minVector.x()) / 2.0f,
        -(maxVector.y() + minVector.y()) / 2.0f,
        (-4.0/3.0) * depth);

    float farPlaneDistance = maxVector.distanceToPoint(minVector);
    projection.setToIdentity();
    projection.perspective(90.0f, GLfloat(1000)/600, 0.01f, (4.0/3.0) * farPlaneDistance);

    buffer.bind();
    buffer.allocate(data.constData(), data.length() * sizeof(GLfloat));
    buffer.release();

    update();
}

/**
 * @brief addToData Add a face represented by three QVector3D (And its normal
 * vectors), to a vector of QLfloats, by using a pointer to GLfloat as an
 * iterator.
 */
void OpenGLWidget::addToData(QVector3D * vector3d, QVector3D normal, GLfloat * & start)
{
    for (int i = 0; i < 3; i++)
    {
        *start = vector3d[i].x();
        *(++start) = vector3d[i].y();
        *(++start) = vector3d[i].z();
        *(++start) = normal.x();
        *(++start) = normal.y();
        *(++start) = normal.z();
        ++start;
    }
}

/**
 * @brief calculateDepth calculates the right z displacement of the camara,
 *  to display the whole mesh. The
 * @param max is the most outer-top-left point of the mesh bounding box
 * @param min is the most inner-down-right point of the mesh bounding box
 */
float OpenGLWidget::calculateDepth(QVector3D & max, QVector3D & min)
{
    float maxVal = 0.0f;
    for(int i = 0; i < 3; i++)
    {
        if (max[i] > maxVal)
        {
            maxVal = max[i];
        }

        if (abs(min[i]) > maxVal)
        {
            maxVal = abs(min[i]);
        }
    }
    return maxVal;
}
