#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Vertex
{
    private:
        /**
         * @brief index: Index asociated to the point
         */
        int index;

        /**
         * @brief coordinates: (X Y Z) coordinates
         */
        double coordinates[3];

        /**
         * @brief facesContainingPoint: Faces that contains the point
         */
        vector<int> facesContainingPoint;

    public:

        /**
         * @brief Vertex
         *  This method construct a Vertex class without defining its private objects
         */
        Vertex();

        /**
         * @brief Vertex
         * This method construct a Vertex class defining the following objects
         * @param newIndex :  The index of the created Vertex
         * @param newCoordinates :  The 3D coordinates of the Vertex
         */
        Vertex(int newIndex, double* newCoordinates );

        /**
         * @brief ~Vertex
         * This method is the destructor of a Vertex Class, it deletes its objects
         */
        ~Vertex();

        /**
         * @brief addNewFace
         * This method adds a face that contains the given vertex.
         * @param faceNumber: Face number wich contains the vertex.
         */
        void addNewFace(int faceNumber);

        /**
         * @brief DeleteFace
         * This method deletes a face that contains the given vertex.
         * @param faceNumber: Face to delete.
         */
        void deleteFace(int faceNumber);

        /**
         * @brief setCordinates
         * This method writes the position of the given coordinates of the vereteex
         * @param newCoordinates: are the cooridnates value in X Y Z
         */
        void setCordinates(double* newCoordinates);

        /**
         * @brief setIndex
         * This method allows to set the index of the vertex by the parameter newIndex
         * @param newIndex
         */
        void setIndex(int newIndex);

        /**
         * @brief getIndex
         * @returns the index value of the vertex
         */
        int getIndex();

        /**
         * @brief getCoordinates
         * @return a pointer type double to the Coordinates of the given vertex
         */
        double* getCoordinates();

        /**
         * @brief getFaces
         * @return a std::vector containing all the faces that contains the vertex
         */
        vector<int> getFaces();


};

#endif // VERTEX_H
