/**
 * DISCLAIMER: This source code has been adapted form the
 * glwidget class of the Hello GL2 Example inclued in the
 * Qt 5.11.2 package.
 * For more information: http://doc.qt.io/qt-5/qtopengl-hellogl2-example.html
 */

#include "openglwidget.h"
#include "renderutil.h"

/**
 * @brief OpenGLWidget constructor
 * @param parent pointer to the parent widget.
 */
OpenGLWidget::OpenGLWidget(QWidget * parent) : QOpenGLWidget (parent)
{
    shader = NULL;
    initializePositions();
}

/**
 * @brief initializePositions Initializes all the positions related with
 *  the elements in the scene.
 */
void OpenGLWidget::initializePositions()
{
    lightPosition.setX(0);
    lightPosition.setY(0);
    lightPosition.setZ(0);
    vertexes = 0;
    depth = 0;
    cameraPositionX = 0;
    cameraPositionY = 0;
    angleX = -45.0f;
    angleY = 45.0f;
    angleZ = 0.0f;
    farPlaneDistance = 0.0f;
    proportion = 0.0f;
    interestPoints = 0;
}

OpenGLWidget::~OpenGLWidget()
{
}

/**
 * @brief initializeGL Inherited. Initializes the scene.
 */
void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(
        RenderUtil::backgroundColour.x(),
        RenderUtil::backgroundColour.y(),
        RenderUtil::backgroundColour.z(),
        1);

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
    locLight = shader->uniformLocation("lightPos");
    locColor = shader->uniformLocation("currentColor");

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

/**
 * @brief paintGL Inherited. Draw the vertices contained in the drawing buffer,
 *  whithin the context.
 */
void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    shader->bind();
    shader->setUniformValue(locProjection, projection);
    QMatrix4x4 rotationMatrix;
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(angleX, 1,0,0);
    rotationMatrix.rotate(angleY, 0,1,0);
    rotationMatrix.rotate(angleZ, 0,0,1);

    cameraLocation.setToIdentity();

    cameraLocation.translate(
        cameraPositionX, cameraPositionY, (-4.0/3.0) * depth);
    lightPosition.setZ(depth * 2);

    shader->setUniformValue(locMvMatrix, cameraLocation * rotationMatrix);
    QMatrix3x3 normalMatrix = rotationMatrix.normalMatrix();
    shader->setUniformValue(locNormalMatrix, normalMatrix);
    shader->setUniformValue(locLight, lightPosition);
    shader->setUniformValue(locColor, RenderUtil::meshColour);

    glDrawArrays(GL_TRIANGLES, 0, vertexes);

    if (interestPoints > 0)
    {
        renderInterestPointsInBuffer();
    }

    shader->release();
    //qDebug() << glGetError() << " ";
}


void OpenGLWidget::renderInterestPointsInBuffer()
{
    int slope = (RenderUtil::sphereLongs + 1 )*2;
    shader->setUniformValue(locColor, RenderUtil::interestPointColour);
    for (int i = 0; i < interestPoints; i++)
    {
        for (int j = 0; j < RenderUtil::sphereLats; j++)
        {
            glDrawArrays(
                GL_TRIANGLE_STRIP,
                vertexes + (j * slope) + (i * RenderUtil::sphereLats * slope),
                slope);
        }
    }
}

/**
 * @brief drawMesh Process and render the 3D mesh in the Opengl widget.
 * @param mesh The mesh to be rendered.
 */
void OpenGLWidget::drawMesh(Mesh * mesh)
{
    initializePositions();
    QVector3D maxVector(0.0f, 0.0f, 0.0f);
    QVector3D minVector(0.0f, 0.0f, 0.0f);

    vector<Face *> * faces = mesh->getAllFaces();
    vector<Vertex *> * vertexes = mesh->getAllVertexes();
    int coordinatesPerVertex = 3;

    this->vertexes = faces->size() * 3;

    // Creation of a vector of GLfloats where the coodinates of every vertex in the
    // mesh will be stored, along with the coordinates of its normal vector.
    data = QVector<GLfloat>(this->vertexes * coordinatesPerVertex * 2);

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

            maxVector.setX((x > maxVector.x())? x : maxVector.x());
            maxVector.setY((y > maxVector.y())? y : maxVector.y());
            maxVector.setZ((z > maxVector.z())? z : maxVector.z());

            minVector.setX((x < minVector.x())? x : minVector.x());
            minVector.setY((y < minVector.y())? y : minVector.y());
            minVector.setZ((z < minVector.z())? z : minVector.z());
        }

        QVector3D normal = QVector3D::normal(faceVer[0], faceVer[1], faceVer[2]);
        addToData(faceVer, normal, start);
    }

    depth = calculateDepth(maxVector, minVector);
    cameraPositionX = -(maxVector.x() + minVector.x()) / 2.0f;
    cameraPositionY = -(maxVector.y() + minVector.y()) / 2.0f;

    farPlaneDistance = maxVector.distanceToPoint(minVector);
    proportion = farPlaneDistance / 360.0f;

    resizeGL(this->width(), this->height());

    buffer.bind();
    buffer.allocate(data.constData(), data.length() * sizeof(GLfloat));
    buffer.release();
    update();
}

void OpenGLWidget::reallocateBufferWithInteresPoints(vector<Vertex *> * interestPoints)
{

    this->interestPoints = interestPoints->size();
    QVector<GLfloat> newData = data;
    for (Vertex * myVertex : *interestPoints)
    {
        int elements = 0;

        QVector3D centre(
            myVertex->getCoordinates()[0],
            myVertex->getCoordinates()[1],
            myVertex->getCoordinates()[2]);
        GLfloat * elms =
            RenderUtil::generateSphere(
                proportion * 2.0f,
                RenderUtil::sphereLats,
                RenderUtil::sphereLongs,
                elements,
                centre);

        for (int i = 0; i < elements; i++)
        {
            newData.push_back(elms[i]);
        }
    }

    buffer.bind();
    buffer.allocate(newData.constData(), newData.length() * sizeof(GLfloat));
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

/**
 * @brief wheelEvent Inherited. Controls the wheel event to zoom-in and zoom-out.
 */
void OpenGLWidget::wheelEvent(QWheelEvent * event)
{
    QPoint roll = event->angleDelta();
    float delta = roll.y()/(8.0f * 45.0f);
    depth += proportion * delta;
    update();
}

/**
 * @brief mousePressEvent Inherited. Controls the mouse press event to give the
 *  focus to the widget and define the starting point of the drag event
 */
void OpenGLWidget::mousePressEvent(QMouseEvent * event)
{
    this->setFocus();
    lastPosition = event->pos();
}

/**
 * @brief mouseMoveEvent Inherited. Controls the mouse move event while dragging
 *  the screen. Rotates the scene accordint to the mouse movement.
 */
void OpenGLWidget::mouseMoveEvent(QMouseEvent * event)
{

    int dx = event->x() - lastPosition.x();
    int dy = event->y() - lastPosition.y();

    if (event->buttons() & Qt::LeftButton)
    {
        angleX = angleX + 2 * dy;
        angleY = angleY + 2 * dx;
    }
    else if (event->buttons() & Qt::RightButton)
    {
        angleX = angleX + 2 * dy;
        angleZ = angleZ + 2 * dx;
    }
    lastPosition = event->pos();
    update();
}

/**
 * @brief keyPressEvent Inherited. Controls the key events. The up, down, left
 *  and right to displace the scene along the X and Y axis.
 */
void OpenGLWidget::keyPressEvent(QKeyEvent * event)
{
    int key = event->key();

    switch(key)
    {
        case Qt::Key_Up :
            cameraPositionY = cameraPositionY + proportion;
            break;
        case Qt::Key_Down :
            cameraPositionY  = cameraPositionY - proportion;
            break;
        case Qt::Key_Left:
            cameraPositionX = cameraPositionX - proportion;
            break;
        case Qt::Key_Right:
            cameraPositionX = cameraPositionX + proportion;
            break;
    }
    update();
}

/**
 * @brief resizeGL Inherited. Fixes the scene's aspect ratio according
 *  to the widget size.
 * @param w The width of the widget
 * @param h The height of the widget.
 */
void OpenGLWidget::resizeGL(int w, int h)
{
    projection.setToIdentity();
    projection.perspective(
        90.0f, GLfloat(w)/h, 0.01f, (4.0/3.0) * farPlaneDistance);
}

void OpenGLWidget::drawInterestPoints()
{
    interestPoints = 14;
    GLfloat floats[] =
    {
        -14.665700f, 14.623900f, 51.540001f,
        2.850450f, 42.581299f, 51.009602f,
        7.531370f, 8.660440f, 33.058601f,
        2.978240f, 37.160999f, 66.557098f,
        4.219920f, 22.941601f, 70.514397f,
        4.313190f, 25.350300f, 70.067703f,
        6.468030f, 17.576799f, 70.261002f,
        7.736700f, 17.180799f, 69.606300f,
        8.932300f, 16.710400f, 68.819000f,
        6.597800f, 20.087799f, 69.988403f,
        7.797780f, 19.681499f, 69.352997f,
        8.912280f, 19.197701f, 68.592903f,
        9.986520f, 16.225599f, 67.927002f,
        11.000900f, 13.340600f, 66.990196
    };

    int sum = 0;
    vector<Vertex*> vertexesP;
    for (int i = 0; i < 14; i++)
    {
        double * coords = new double[3];
        Vertex * vert = new Vertex();
        coords[0] = floats[sum++];
        coords[1] = floats[sum++];
        coords[2] = floats[sum++];
        vert->setCoordinates(coords);
        vertexesP.push_back(vert);
    }
    reallocateBufferWithInteresPoints(&vertexesP);

}
