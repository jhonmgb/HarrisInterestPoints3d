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
 * @brief Communicator::loadMesh uses the FileManager to load a mesh, reading
 *  the tri, vert OR off files.
 */
void Communicator::loadMesh(MeshType type, QString file1, QString file2)
{
    FileManager manager;
    delete mesh;
    mesh = 0;
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

/**
 * @brief Communicator::getMesh returns a pointer to the mesh.
 * @return a poiner to mesh
 */
Mesh * Communicator::getMesh()
{
    return mesh;
}

/**
 * @brief Communicator::bindEngine bind the communicator with the Engine that
 *  runs the calculations.
 * @param engine the instance of the Engine.
 */
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

/**
 * @brief Communicator::retrieveInterestPoints calls the Engine and calculates
 *  the interest points of the mesh.
 * @param numRings the number of ring to consider during the interest
 *  points calculation.
 * @param k the harris param.
 * @param percentageOfPoints the percentage of interest points to select.
 * @param selectionMode Indicates the way the interest points will be
 *  selected after calculation.
 * @return The calculated interest points.
 */
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
        engine->findInterestPoints(
            this->mesh, numRings, k, percentageOfPoints, mode);

    return convertIntPoints(indexes);
}

/**
 * @brief Communicator::healthCheck Checks wether the engine has been binded
 *  and the mesh has been loaded, prior to start the calculation of the
 *  interest points.
 */
void Communicator::healthCheck()
{
    if (mesh == NULL || engine == NULL)
    {
        string messge =
            "The mesh or the engine has not been initialized.";
        throw Exception(ExceptionType::MESH_ENGINE_NOT_BINDED, messge);
    }
}

/**
 * @brief Communicator::convertIntPoints retrieves the vertexes corresponding
 *  to every index.
 * @param indexes The indexes of the vertexes to retrieve.
 * @return a vector with the vertexes.
 */
vector<Vertex *> * Communicator::convertIntPoints(vector<int>* indexes)
{
    vector<Vertex *> * vtx = new vector<Vertex *>();

    for (int i = 0; i < indexes->size(); i++)
    {
        vtx->push_back(mesh->getAllVertexes()->at(indexes->at(i)));
    }

    delete indexes;
    return vtx;
}
