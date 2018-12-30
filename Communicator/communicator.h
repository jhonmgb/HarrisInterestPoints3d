#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QString>
#include "BasicStructures/mesh.h"
#include "Engine/engine.h"

enum MeshType {TRIVERT, OFF};

/**
 * @brief The Communicator class intermediates between the Engine and the UI.
 */
class Communicator
{
private:
    // This static instance ensures that there is one and only one
    // mesh during the whole execution of the program.
    static Mesh * mesh;

    Engine * engine;

    /**
     * @brief healthCheck Checks wether the engine has been binded and the mesh
     *  has been loaded, prior to start the calculation of the interest points.
     */
    void healthCheck();

public:
    Communicator();

    /**
     * @brief uses the FileManager to load a mesh, reading the tri, vert OR off
     * files.
     */
    void loadMesh(MeshType, QString, QString);

    /**
     * @brief getMesh returns a pointer to the mesh.
     * @return a poiner to mesh
     */
    Mesh * getMesh();

    /**
     * @brief bindEngine bind the communicator with the Engine that runs the
     *  calculations.
     * @param engine the instance of the Engine.
     */
    void bindEngine(Engine * engine);

    /**
     * @brief retrieveInterestPoints calls the Engine and calculates the
     *  interest points of the mesh.
     * @param numRings the number of ring to consider during the interest
     *  points calculation.
     * @param k the harris param.
     * @param percentageOfPoints the percentage of interest points to select.
     * @param selectionMode Indicates the way the interest points will be
     *  selected after calculation.
     * @return The calculated interest points.
     */
    vector<Vertex *> * retrieveInterestPoints(
        int numRings, double k, double percentageOfPoints, QString selectionMode);

    /**
     * @brief convertIntPoints retrieves the vertexes corresponding to every
     *  index.
     * @param indexes The indexes of the vertexes to retrieve.
     * @return a vector with the vertexes.
     */
    vector<Vertex *> * convertIntPoints(vector<int>* indexes);

};

#endif // COMMUNICATOR_H
