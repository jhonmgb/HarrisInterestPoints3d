#include "../BasicStructures/mesh.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace Eigen;

#ifndef ENGINE_H
#define ENGINE_H

/**
 * @brief The Engine class for managing all computations related to the Harris operator
 */
class Engine
{
public:
    /**
     * @brief Engine Default constructor for class Engine
     */
    Engine();

    /**
     * @brief findInterestPoints Method for finding interest points for a mesh
     * @param theMesh Mesh sent by communicator for computing interest points
     * @param numRings Number of rings to be considered for the computation of neighbourhood
     * @param k Constant for Harris operator computation (Equation 3 in paper)
     * @return vector of integers with indixes of vertexes that are of interest
     */
    vector<int> * findInterestPoints(Mesh * theMesh, int numRings, double k);

    /**
     * @brief getVertexesFromMesh converts vector of vertexes of theMesh into an MatrixXd
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @return Matrix with vertexes
     */
    MatrixXd getVertexesFromMesh(Mesh * theMesh);

    /**
     * @brief getFacesFromMesh converts vector of faces of theMesh into an MatrixXi
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @return Matrix with faces
     */
    MatrixXi getFacesFromMesh(Mesh * theMesh);

    /**
     * @brief getFacesForVertex gets the faces that contain certain vertex
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @param pointIndex Index of the point for which faces have to be found
     * @return Vector with indexes of faces in which vertex is involved
     */
    VectorXi getFacesForVertex(Mesh * theMesh, int pointIndex);

    /**
     * @brief getDirectNeighbours finds the direct neighbours of a vertex
     * @param vertex is the index of the vertex
     * @param faces is the matrix of faces
     * @param facesThatContainPoint is the vector that contains indexes of faces that contain vertex
     * @return Indexes of direct neighbours as a vector
     */
    VectorXi getDirectNeighbours(int vertex, MatrixXi faces, VectorXi facesThatContainPoint);

    /**
     * @brief getRings gets neighbourhood k for point with index vertex
     * @param vertex is the index of the vertex
     * @param k is the depth of the ring neighbourhood
     * @param faces is the matrix of faces
     * @param firstNeighbours is a vector containing the indexes of the direct neighbours
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @return a vector with indexes of neighbours until depth k (includes all points within ring k and also ring k)
     */
    VectorXi getRings(int vertex, int k, MatrixXi faces, VectorXi firstNeighbours, Mesh * theMesh);

    /**
     * @brief getVertexesFromIndexes gets matrix with vertexes corresponding to specific indexes
     * @param indexes indexes of vertexes
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @return Matrix with points corresponding to given indexes
     */
    MatrixXd getVertexesFromIndexes(VectorXi indexes, Mesh * theMesh);

    /**
     * @brief getVertexFromMeshAsVector3d Gets a vertex as a vector from its position or index
     * @param position is the index of the vertex that is required
     * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
     * @return
     */
    Vector3d getVertexFromMeshAsVector3d(int position, Mesh * theMesh);

    /**
     * @brief getVertexIndexInNeighbourhood Gets index of vertex in the neighbourhood vector
     * @param vertexIndex is the index of vertex for which neighbourhood was computed
     * @param indexesOfNeighbours is the vector with the indexes of the neighbours
     * @return index of vertexIndex in indexOfNeighbours
     */
    int getVertexIndexInNeighbourhood(int vertexIndex, VectorXi indexesOfNeighbours);

    //Here add functions for PCA and surface fitting

    //Here function for computing Harris operator from surface fitting coefficients

    //Here select interest points according to highest Harris operator or clustering

};

#endif // ENGINE_H
