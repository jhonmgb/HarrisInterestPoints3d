#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Face
{
    private:
        /**
         * @brief faceIndex : Index asociated to the face
         */
        int faceIndex;

        /**
         * @brief pointsInFace: points asociated to trianglular faces
         */
        int pointsInFace[3];

    public:

        /**
         * @brief Face
         *  This method construct a Face class without defining its private objects
         */
        Face();

        /**
         * @brief Face
         * This method construct a Face class defining the following objects
         * @param newIndex :  The index of the created Face
         * @param newCoordinates :  The Face indexes coordinates of the Face
         */
        Face(int newIndex, double* newCoordinates );

        /**
         * @brief ~Face
         * This method is the destructor of a Face Class
         */
        ~Face();

        /**
         * @brief setPointsInFace
         * This method writes the indexes of the points inlcuded in the face
         * @param newPoints: are the tree points corresponding to the face
         */
        void setPointsInFace(int* newPoints);

        /**
         * @brief Face::setFaceIndex
         * This method allows to set the index of the Face by the parameter newIndex
         * @param newIndex
         */
        void setFaceIndex(int newIndex);

        /**
         * @brief Face::getFaceIndex
         * @returns the index value of the Face
         */
        int getFaceIndex();

        /**
         * @brief Face::getPointsInFace
         * @return a pointer type int to the object pointsInFace
         */
        int* getPointsInFace();


};





#endif // FACE_H
