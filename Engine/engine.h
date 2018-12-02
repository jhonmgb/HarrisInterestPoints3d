#include "../BasicStructures/mesh.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <cmath>

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
     * @param percentageOfPoints is a double indicating how many points should be considered as interest points
     * @param selectionMode is a string defining the type of selection for the interest points
     * @return vector of integers with indixes of vertexes that are of interest
     */
    vector<int> * findInterestPoints(Mesh * theMesh, int numRings, double k, double percentageOfPoints, string selectionMode);

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

    /**
     * @brief centerNeighbourhood :
     *        Centrates a Neighbourhood arround its centroid and translate
     *        the set of points to the origin
     * @param Neighbourhood
     * @return
     */
    MatrixXd centerNeighbourhood(MatrixXd Neighbourhood , MatrixXd& Centroid );

    /**
     * @brief rotationToFitPlane:
     *        Apply Principal Component Analysis to the set of points and
     *        choose the eigenvector with the lowest associated eigenvalue
     *        as the normal of the fitting plane.
     * @param centeredPoints : the centrated points of the Neibourhood
     * @param analizedPointIndex  : the vertex of analisys
     * @return
     */
    MatrixXd rotateToFitPlane(MatrixXd centeredPoints, int analizedPointIndex);

    /**
     * @brief fitQuadraticSurface
     *        Apply Least Squares to fit a quadratic surface to the rotated
     *        points of the NEibourhood.
     * @param rotatedPoints     : the rotated points of the Neibourhood
     * @param analizedPointIndex  : the vertex of analisys
     * @return
     */
    MatrixXd fitQuadraticSurface(MatrixXd rotatedPoints, int analizedPointIndex);


    /**
     * @brief findderivativeEmatrix formulates the derivative matrix for
     *        the harris operator
     * @param X : the parameters of the Quadratic Surface.
     * @return
     */
    MatrixXd findderivativeEmatrix(MatrixXd X);

    /**
     * @brief computeHarris computes the Harris operator for the current point
     * @param E Matrix with parameters A,B,C obtained from surface fitting
     * @param k Paramter for Harris operator calculation according to formula (3)
     * @return Value of Harris operator according to equation (3)
     */
    double computeHarris(MatrixXd E, double k);

    //Here select interest points according to highest Harris operator or clustering

    /**
     * @brief getDiagonalOfMesh computes the diagonal lenght of the points in the mesh
     * @param vertexes A matrix containing all the vertex of the mesh
     * @return the distance between the lowest and the maximum point int the mesh
     */
    double getDiagonalOfMesh(MatrixXd allVertexes);

};

#endif // ENGINE_H
