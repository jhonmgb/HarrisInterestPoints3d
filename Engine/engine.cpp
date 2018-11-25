#include "../Engine/engine.h"
#include "../Basic_Structures/mesh.h"
#include "eigenwrapper.h"
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using std::set_difference;
using std::inserter;

/**
 * @brief Engine Default constructor for class Engine
 */
Engine::Engine()
{

}

/**
 * @brief findInterestPoints Method for finding interest points for a mesh
 * @param theMesh Mesh sent by communicator for computing interest points
 * @param numRings Number of rings to be considered for the computation of neighbourhood
 * @param k Constant for Harris operator computation (Equation 3 in paper)
 * @return vector of integers with indixes of vertexes that are of interest
 */
vector<int> * Engine::findInterestPoints(Mesh * theMesh, int numRings, double k)
{
    Engine computations = Engine();
    EMatrixXd vertexes = computations.getVertexesFromMesh(theMesh);
    EMatrixXi faces = computations.getFacesFromMesh(theMesh);
    EVectorXd harrisValues(vertexes.rows()); //Vector for storing values of harris operator for each vertex

    //For each vertex, compute harris operator
    for(int iVertex=0; iVertex< vertexes.rows(); iVertex++)
    {
        //Get neighbourhood k
        EVectorXi facesForThisVertex = computations.getFacesForVertex(theMesh, iVertex);
        EVectorXi neighbours = computations.getDirectNeighbours(iVertex, faces, facesForThisVertex);
        EVectorXi kRings = computations.getRings(iVertex, numRings, faces, neighbours, theMesh);
        EMatrixXd pointskRings = computations.getVertexesFromIndexes(kRings, theMesh);
        int currentVertexIndexInkRings = computations.getVertexIndexInNeighbourhood(iVertex, kRings);

        //Here use pointskRings to compute PCA, fitting surface, etc
        //Esteban = PCA(currentVertexIndexInkRings, pointskRings)


        //Here compute harris operator using info from surface fitting

    }

    return NULL;
}

/**
 * @brief getVertexesFromMesh converts vector of vertexes of theMesh into an EMatrixXd
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @return Matrix with vertexes
 */
EMatrixXd Engine::getVertexesFromMesh(Mesh * theMesh)
{
    int numPoints = theMesh->getAllVertexes()->size();
    double * currVertex = NULL;
    EMatrixXd points(numPoints,3);
    for(int iVertex=0; iVertex<numPoints; iVertex++)
    {
        currVertex = theMesh->getVertex(iVertex)->getCoordinates();
        for(int j=0; j<3; j++)
        {
            points(iVertex,j) = currVertex[j];
        }
    }
    return points;
}

/**
 * @brief getFacesFromMesh converts vector of faces of theMesh into an EMatrixXi
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @return Matrix with faces
 */
EMatrixXi Engine::getFacesFromMesh(Mesh * theMesh)
{
    int numFaces = theMesh->getAllFaces()->size();
    int * currFace = NULL;
    EMatrixXi faces(numFaces, 3);
    for(int iFace=0; iFace<numFaces; iFace++)
    {
        currFace = theMesh->getFace(iFace)->getPointsInFace();
        for(int j=0; j<3;j++)
        {
            faces(iFace, j) = currFace[j];
        }
    }
    return faces;
}

/**
 * @brief getFacesForVertex gets the faces that contain certain vertex
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @param pointIndex Index of the point for which faces have to be found
 * @return Vector with indexes of faces in which vertex is involved
 */
EVectorXi Engine::getFacesForVertex(Mesh * theMesh, int pointIndex)
{
    vector<int> facesForVertex = theMesh->getVertex(pointIndex)->getFaces();
    EVectorXi facesForThisVertex(facesForVertex.size());
    for(int iF=0; iF<facesForVertex.size(); iF++)
    {
        facesForThisVertex(iF) = facesForVertex.at(iF);
    }
    return facesForThisVertex;
}

/**
 * @brief getDirectNeighbours finds the direct neighbours of a vertex
 * @param vertex is the index of the vertex
 * @param faces is the matrix of faces
 * @param facesThatContainPoint is the vector that contains indexes of faces that contain vertex
 * @return Indexes of direct neighbours as a vector
 */
EVectorXi Engine::getDirectNeighbours(int iVertex, EMatrixXi faces, EVectorXi facesThatContainPoint)
{
    int numFacesWithVertex = facesThatContainPoint.size();
    set<int> directNeighbours;
    for(int i=0; i<numFacesWithVertex; i++)
    {
        for(int j=0; j< 3; j++)
        {
            if(faces(facesThatContainPoint(i), j) != iVertex)
            {
                directNeighbours.insert(faces(facesThatContainPoint(i), j));
            }
        }
    }
    int numDirectNeighbours = directNeighbours.size();
    EVectorXi vertexesFirstNeighbourhood(numDirectNeighbours);
    int ctrlVar1(0);
    for (set<int>::iterator it=directNeighbours.begin(); it!=directNeighbours.end(); ++it)
    {
        vertexesFirstNeighbourhood(ctrlVar1) = *it;
        ctrlVar1++;
    }
    return vertexesFirstNeighbourhood;
}

/**
 * @brief getRings gets neighbourhood k for point with index vertex
 * @param vertex is the index of the vertex
 * @param k is the depth of the ring neighbourhood
 * @param faces is the matrix of faces
 * @param firstNeighbours is a vector containing the indexes of the direct neighbours
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @return a vector with indexes of neighbours until depth k (includes all points within ring k and also ring k)
 */
EVectorXi Engine::getRings(int vertex, int k, EMatrixXi faces, EVectorXi firstNeighbours, Mesh * theMesh)
{
    set <int> s0;
    s0.insert(vertex);
    set <int> s1;
    set <int> sAccum;
    for(int iNei=0;iNei<firstNeighbours.size(); iNei++)
    {
        s1.insert(firstNeighbours(iNei));
    }
    set <int> result = s0;
    result.insert(s1.begin(), s1.end());
    set <int> tempSet1;
    set <int> tempSet2;
    for(int ring=2; ring<k; ring++)
    {
        for (set<int>::iterator it=s1.begin(); it!=s1.end(); ++it)
        {
            EVectorXi facesThatContainPoint = this->getFacesForVertex(theMesh, *it);
            EVectorXi someNeighbours = this->getDirectNeighbours(*it, faces, facesThatContainPoint);
            for(int i=0; i<someNeighbours.size(); i++)
            {
                sAccum.insert(someNeighbours(i));
                result.insert(someNeighbours(i));
            }
        }
        set_difference(sAccum.begin(), sAccum.end(), s1.begin(), s1.end(), inserter(tempSet1, tempSet1.end()));
        set_difference(tempSet1.begin(), tempSet1.end(), s0.begin(), s0.end(), inserter(tempSet2, tempSet2.end()));
        s0 = s1;
        s1 = tempSet2;
        tempSet1.clear();
        tempSet2.clear();
    }
    int kNeighboursSize = result.size();
    EVectorXi kNeighbours(kNeighboursSize);
    int ctrlVar1(0);
    for (set<int>::iterator it=result.begin(); it!=result.end(); ++it)
    {
        kNeighbours(ctrlVar1) = *it;
        ctrlVar1++;
    }
    return kNeighbours;
}

/**
 * @brief getVertexesFromIndexes gets matrix with vertexes corresponding to specific indexes
 * @param indexes indexes of vertexes
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @return Matrix with points corresponding to given indexes
 */
EMatrixXd Engine::getVertexesFromIndexes(EVectorXi indexes, Mesh * theMesh)
{
    EMatrixXd points(indexes.size(), 3);
    for(int iP=0; iP<indexes.size(); iP++)
    {
        double * xyz =  theMesh->getVertex(indexes(iP))->getCoordinates();
        points(iP, 0) = xyz[0];
        points(iP, 1) = xyz[1];
        points(iP, 2) = xyz[2];
    }
    return points;
}

/**
 * @brief getVertexFromMeshAsEVector3d Gets a vertex as a vector from its position or index
 * @param position is the index of the vertex that is required
 * @param theMesh is the mesh or surface being analyzed (read and sent from middleware)
 * @return
 */
EVector3d Engine::getVertexFromMeshAsEVector3d(int position, Mesh * theMesh)
{
    double * xyz = theMesh->getVertex(position)->getCoordinates();
    EVector3d vertexVector;
    vertexVector(0) = xyz[0];
    vertexVector(1) = xyz[1];
    vertexVector(2) = xyz[2];
    return vertexVector;
}

/**
 * @brief getVertexIndexInNeighbourhood Gets index of vertex in the neighbourhood vector
 * @param vertexIndex is the index of vertex for which neighbourhood was computed
 * @param indexesOfNeighbours is the vector with the indexes of the neighbours
 * @return index of vertexIndex in indexOfNeighbours
 */
int Engine::getVertexIndexInNeighbourhood(int vertexIndex, EVectorXi indexesOfNeighbours)
{
    int indexOfVertex(0);
    for(int i=0; i<indexesOfNeighbours.size(); i++)
    {
        if(indexesOfNeighbours(i)==vertexIndex)
        {
            indexOfVertex = i;
            break;
        }
    }
    return indexOfVertex;
}
