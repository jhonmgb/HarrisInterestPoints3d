#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QString>
#include "BasicStructures/mesh.h"
#include "Engine/engine.h"

enum MeshType {TRIVERT, OFF};

class Communicator
{
private:
    // This static instance ensures that there is one and only one
    // mesh during the whole execution of the program.
    static Mesh * mesh;

    Engine * engine;

    void healthCheck();

public:
    Communicator();

    /**
     * @brief uses the FileManager to load a mesh, reading the tri, vert OR off files.
     */
    void loadMesh(MeshType, QString, QString);

    /**
     * @brief getMesh returns a pointer to the mesh.
     * @return a poiner to mesh
     */
    Mesh * getMesh();

    void bindEngine(Engine * engine);

    vector<Vertex *> * retrieveInterestPoints(
        int numRings, double k, double percentageOfPoints, QString selectionMode);

    vector<Vertex *> * convertIntPoints(vector<int>* indexes);

};

#endif // COMMUNICATOR_H
