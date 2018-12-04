#include "Communicator/communicator.h"
#include "Communicator/exception.h"
#include "FileManager/filemanager.h"
#include <string>
#include <QDebug>

using std::string;

Mesh * Communicator::mesh = NULL;

Communicator::Communicator()
{

}

/**
 * @brief uses the FileManager to load a mesh, reading the tri, vert OR off files.
 */
void Communicator::loadMesh(MeshType type, QString file1, QString file2)
{
    FileManager manager;
    if (type == MeshType::TRIVERT)
    {
        QFile * triFile = new QFile(file1);
        QFile * vertFile = new QFile(file2);
        mesh = manager.readTriVert(triFile, vertFile);
        delete triFile;
        delete vertFile;
    }
    else if (type == MeshType::OFF)
    {
        QFile * off = new QFile(file1);
        mesh = manager.readOFF(off);
        delete off;
    }

    if (mesh == NULL)
    {
        string messge =
            "Error while building mesh. Check that your mesh files are not corrupted";
        throw Exception(ExceptionType::ERROR_WHILE_READING, messge);
    }
}

Mesh * Communicator::getMesh()
{
    return mesh;
}

void Communicator::bindEngine(Engine * engine)
{
    if (engine == NULL)
    {
        string messge =
            "Error while binding engine. The instance is corrupted";
        throw Exception(ExceptionType::ERROR_WHILE_BINDING, messge);
    }
    this->engine = engine;
}

vector<Vertex *> * Communicator::retrieveInterestPoints(
    int numRings, double k, double percentageOfPoints, QString selectionMode)
{
    SelectionMode mode;
    this->healthCheck();

    if (!selectionMode.toUpper().compare(QString("CLUSTERING")))
    {
        mode = SelectionMode::CLUSTERING;
    }
    else if (!selectionMode.toUpper().compare(QString("FRACTION")))
    {
        mode = SelectionMode::FRACTION;
    }
    else
    {
        string messge =
            "The selected selection method doesn't exists.";
        throw Exception(ExceptionType::UNKNOWN_SEL_METHOD, messge);
    }

    vector<int> * indexes =
        engine->findInterestPoints(this->mesh, numRings, k, percentageOfPoints, mode);

    return convertIntPoints(indexes);
}

void Communicator::healthCheck()
{
    if (mesh == NULL || engine == NULL)
    {
        string messge =
            "The mesh or the engine has not been initialized.";
        throw Exception(ExceptionType::MESH_ENGINE_NOT_BINDED, messge);
    }
}

vector<Vertex *> * Communicator::convertIntPoints(vector<int>* indexes)
{
    vector<Vertex *> * vtx = new vector<Vertex *>();

    for (int i = 0; i < indexes->size(); i++)
    {
        vtx->push_back(mesh->getAllVertexes()->at(indexes->at(i)));
    }

    return vtx;
}
