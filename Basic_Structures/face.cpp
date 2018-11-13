#include "face.h"

/**
 * @brief Face::Face
 *  This method construct a Face class without defining its private objects
 */
Face::Face()
{
    this->faceIndex = 0;
    for (int i=0; i<3; i++)
    {
       *(this->pointsInFace +i ) = 0;
    }
}

/**
 * @brief Face::Face
 * This method construct a Face class defining the following objects
 * @param newIndex :  The index of the created Face
 * @param newCoordinates :  The Face indexes coordinates of the Face
 */
Face::Face(int newIndex, double* newCoordinates )
{
    this->faceIndex = newIndex;
    for(int i=1; i<3 ; i++)
    {
        this->pointsInFace[i] = *(newCoordinates + 1);
    }
}

/**
 * @brief Face::~Face
 * This method is the destructor of a Face Class
 */
Face::~Face()
{
    delete[] this->pointsInFace;
}

/**
 * @brief Face::setPointsInFace
 * This method writes the indexes of the points inlcuded in the face
 * @param newPoints: are the tree points corresponding to the face
 */
void Face::setPointsInFace(int *newPoints)
{
    for(int i=1; i<3 ; i++)
    {
        *(this->pointsInFace+i) = *(newPoints + 1);
    }
}

/**
 * @brief Face::setFaceIndex
 * This method allows to set the index of the Face by the parameter newIndex
 * @param newIndex
 */
void Face::setFaceIndex(int newIndex)
{
    this->faceIndex=newIndex;
}

/**
 * @brief Face::getFaceIndex
 * @returns the index value of the Face
 */
int Face::getFaceIndex()
{
    return this->faceIndex;
}

/**
 * @brief Face::getPointsInFace
 * @return a pointer type int to the object pointsInFace
 */
int* Face::getPointsInFace()
{
    return this->pointsInFace;
}


