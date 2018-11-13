#include "mesh.h"

/**
 * @brief Mesh::Mesh : Construct a mesh class with the number of
 *                     vertex and faces
 * @param vertexNumber :  number of vertex of the mesh
 * @param facesNumber  :  number of faces of the mesh
 */
Mesh::Mesh(int vertexNumber, int facesNumber)
{
    vector<Vertex> tempVertex(vertexNumber);
    this-> vertexes = tempVertex;
    vector<Face> tempFaces(facesNumber);
    this-> faces = tempFaces;
}

/**
 * @brief Mesh::~Mesh: Destructs the Mesh objects, clear the vectors
 */
Mesh::~Mesh()
{
    this->faces.clear();
    this->vertexes.clear();
}

/**
 * @brief Mesh::setVertex: Defines the value of a vertex inside the Mesh
 * @param newVertex: The value of the vertex
 * @param position:  Position to include the vertex
 */
void Mesh::setVertex(Vertex newVertex , int position)
{
    this->vertexes.at(position)=newVertex;
}

/**
 * @brief Mesh::addNewVertex: Add a new vertex in the mesh
 * @param newVertex: The new vertex to include in the mesh
 */
void Mesh::addNewVertex(Vertex newVertex)
{
    this->vertexes.push_back(newVertex);
}

/**
 * @brief Mesh::setFace: Defines a face inside the Mesh
 * @param newFace: The face to include
 * @param position:  Position to include the face
 */
void Mesh::setFace(Face newFace, int position)
{
    this->faces.at(position)=newFace;
}


/**
 * @brief Mesh::addNewVertex: Add a new face at the end of the mesh
 * @param newVertex: The new face to include in the mesh
 */
void Mesh::addNewFace(Face newFace)
{
    this->faces.push_back(newFace);
}



