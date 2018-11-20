#include "mesh.h"



/**
 * @brief Mesh::Mesh : Construct a mesh class with the number of
 *                     vertex and faces
 * @param vertexNumber :  number of vertex of the mesh
 * @param facesNumber  :  number of faces of the mesh
 */
Mesh::Mesh()
{
    vertexes = new vector<Vertex *>();
    faces = new vector<Face *>();
}

/**
 * @brief Mesh::~Mesh: Destructs the Mesh objects, clear the vectors
 */
Mesh::~Mesh()
{
    delete faces;
    delete vertexes;
}

/**
 * @brief Mesh::setVertex: Defines the value of a vertex inside the Mesh
 * @param newVertex: The value of the vertex
 * @param position:  Position to include the vertex
 */
void Mesh::setVertex(Vertex * newVertex , int position)
{
    if( (unsigned int)position < vertexes->size())
    {
        vertexes->at(position) = newVertex;
    }
}

/**
 * @brief Mesh::addNewVertex: Add a new vertex in the mesh
 * @param newVertex: The new vertex to include in the mesh
 */
void Mesh::addNewVertex(Vertex * newVertex)
{

    vertexes->push_back(newVertex);
}

/**
 * @brief Mesh::setFace: Defines a face inside the Mesh
 * @param newFace: The face to include
 * @param position:  Position to include the face
 */
void Mesh::setFace(Face * newFace, int position)
{
    if( (unsigned int)position < faces->size())
    {
        faces->at(position)=newFace;
    }
}


/**
 * @brief Mesh::addNewVertex: Add a new face at the end of the mesh
 * @param newVertex: The new face to include in the mesh
 */
void Mesh::addNewFace(Face * newFace)
{
    faces->push_back(newFace);
}


/**
 * @brief getAllFaces : Return a vector of all the Faces in the mesh
 * @return
 */
vector<Face *> * Mesh::getAllFaces()
{
    return faces;
}



/**
 * @brief getAllVertexes: Return a vector of all the vertex in the mesh
 * @return
 */
vector<Vertex * > *  Mesh::getAllVertexes()
{
    return vertexes;
}


/**
 * @brief getFace:  Returns the face on a given position
 * @param position
 * @return
 */
Face * Mesh::getFace(int position)
{
    return faces->at(position);
}

/**
 * @brief getFace:  Returns the face on a given position
 * @param position
 * @return
 */
Vertex * Mesh::getVertex(int position)
{
    return vertexes->at(position);
}
