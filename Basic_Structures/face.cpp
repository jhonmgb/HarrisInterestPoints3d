#include "face.h"

/**
 * @brief Face::Face
 *  This method construct a Face class without defining its private objects
 */
Face::Face()
{
    faceIndex = new (nothrow) int(0) ;
    pointsInFace = new (nothrow) int[3] ;
    if (pointsInFace == nullptr)
    {
        cout << "Error: memory could not be allocated";
    }
    else
    {
        for (int i=0; i<3; i++)
        {
           *(this->pointsInFace +i ) = 0;
        }
    }
}

/**
 * @brief Face::Face
 * This method construct a Face class defining the following objects
 * @param newIndex :  The index of the created Face
 * @param newCoordinates :  The Face indexes coordinates of the Face
 */
Face::Face(int newIndex, int* newPoints )
{
    faceIndex = new (nothrow) int(newIndex) ;
    pointsInFace = new (nothrow) int[3] ;
    if (pointsInFace == nullptr)
    {
        cout << "Error: memory could not be allocated";
    }
    else
    {
        for (int i=0; i<3; i++)
        {
           *(pointsInFace +i ) = *(newPoints + i);
        }
    }
}

/**
 * @brief Face::~Face
 * This method is the destructor of a Face Class
 */
Face::~Face()
{
    delete faceIndex;
    delete[] this->pointsInFace;
}

/**
 * @brief Face::setPointsInFace
 * This method writes the indexes of the points inlcuded in the face
 * @param newPoints: are the tree points corresponding to the face
 */
void Face::setPointsInFace(int *newPoints)
{
    for( int i = 0 ; i < 3 ; i++ )
    {
        *( pointsInFace + i ) = *( newPoints + i );
    }
}

/**
 * @brief setPointsInFace
 * This method writes the indexes of the points inlcuded in the face
 * @param point1: index of point N1
 * @param point2: index of point N2
 * @param point3: index of point N2
 */
void Face::setPointsInFace( int point1, int point2, int point3)
{
    int newPoints[3] = { point1 , point2 , point3 };
    for( int i = 0 ; i < 3 ; i++ )
    {
        *( pointsInFace + i ) = *( newPoints + i );
    }
}

/**
 * @brief Face::setFaceIndex
 * This method allows to set the index of the Face by the parameter newIndex
 * @param newIndex
 */
void Face::setFaceIndex(int newIndex)
{
    *faceIndex = newIndex;
}

/**
 * @brief Face::getFaceIndex
 * @returns the index value of the Face
 */
int Face::getFaceIndex()
{
    return *faceIndex;
}

/**
 * @brief Face::getPointsInFace
 * @return a pointer type int to the object pointsInFace
 */
int* Face::getPointsInFace()
{
    return this->pointsInFace;
}
