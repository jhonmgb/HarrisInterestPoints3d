#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <new>
#include "face.h"
#include "vertex.h"

using namespace std;

class Mesh
{
    private:
        /**
         * @brief faces:  It is a pointer to the vector of pointers to faces contained in the mesh
         */
        vector<Face *> * faces;

        /**
         * @brief vertexes:  It is a pointer to the vector of pointers to vertexes contained in the mesh
         */
        vector<Vertex *> * vertexes;

    public:

        /**
         * @brief Mesh : Construct a mesh class
         */
        Mesh();

        /**
         * @brief ~Mesh: Destructs the Mesh objects, clear the vectors
         */
        ~Mesh();

        /**
         * @brief setVertex: Defines a vertex inside the Mesh
         * @param newVertex: A pointer to the vertex to include
         * @param position:  Position to include the vertex
         */
        void setVertex(Vertex * newVertex , int position);

        /**
         * @brief addNewVertex: Add a new vertex at the end of the mesh
         * @param newVertex: A pointer to the new vertex to include in the mesh
         */
        void addNewVertex(Vertex * newVertex);

        /**
         * @brief setFace: Defines a face inside the Mesh
         * @param newFace: A pointer to the face to include
         * @param position:  Position to include the face
         */
        void setFace(Face * newFace, int position);

        /**
         * @brief addNewFace: Add a new face at the end of the mesh
         * @param newFace: Pointer to the new face to include in the mesh
         */
        void addNewFace(Face * newFace);

        /**
         * @brief getAllFaces : Return a pointer to a vector of pointers to all the Faces in the mesh
         * @return
         */
        vector<Face * > * getAllFaces();

        /**
         * @brief getAllVertexes: Returns a pointer to a vector of pointers to all the vertex in the mesh
         * @return
         */
        vector<Vertex *> * getAllVertexes();

        /**
         * @brief getFace:  Returns a pointer to the face on a given position
         * @param position
         * @return
         */
        Face * getFace(int position);

        /**
         * @brief getVertex: Returns a pointer to a vertex in a given position
         * @param position
         * @return
         */
        Vertex * getVertex(int position);


};

#endif // MESH_H
