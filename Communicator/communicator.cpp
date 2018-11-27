#include "Communicator/communicator.h"
#include "Communicator/exception.h"
#include "FileManager/filemanager.h"
#include <string>

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
