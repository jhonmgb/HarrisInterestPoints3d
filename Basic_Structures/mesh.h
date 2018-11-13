#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "face.h"
#include "vertex.h"

using namespace std;

class Mesh
{
    private:
        /**
         * @brief faces:  It is the vector of faces contained in the mesh
         */
        vector<Face> faces;

        /**
         * @brief vertexes:  It is the vector of vertexes contained in the mesh
         */
        vector<Vertex> vertexes;

    public:

        /**
         * @brief Mesh : Construct a mesh class with the number of
         *                     vertex and faces
         * @param vertexNumber :  number of vertex of the mesh
         * @param facesNumber  :  number of faces of the mesh
         */
        Mesh(int vertexNumber, int facesNumber);

        /**
         * @brief ~Mesh: Destructs the Mesh objects, clear the vectors
         */
        ~Mesh();

        /**
         * @brief setVertex: Defines a vertex inside the Mesh
         * @param newVertex: The vertex to include
         * @param position:  Position to include the vertex
         */
        void setVertex(Vertex newVertex , int position);

        /**
         * @brief addNewVertex: Add a new vertex at the end of the mesh
         * @param newVertex: The new vertex to include in the mesh
         */
        void addNewVertex(Vertex newVertex);

        /**
         * @brief setFace: Defines a face inside the Mesh
         * @param newFace: The face to include
         * @param position:  Position to include the face
         */
        void setFace(Face newFace, int position);

        /**
         * @brief addNewVertex: Add a new face at the end of the mesh
         * @param newVertex: The new face to include in the mesh
         */
        void addNewFace(Face newFace);

};

#endif // MESH_H
