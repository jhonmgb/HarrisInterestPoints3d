#include "vertex.h"

/**
 * @brief Vertex::Vertex
 *  This method construct a Vertex class without defining its private objects
 */
Vertex::Vertex()
{
    this->index = new (nothrow) int(0);
    this->coordinates =  new (nothrow) double[3] ;

    for (int i=0; i<3; i++)
    {
       *(coordinates +i ) = 0;
    }

    facesContainingPoint = new vector<int>;
}

/**
 * @brief Vertex::Vertex
 * This method construct a Vertex class defining the following objects
 * @param newIndex :  The index of the created Vertex
 * @param newCoordinates :  The 3D coordinates of the Vertex
 */
Vertex::Vertex(int newIndex, double* newCoordinates, int numberOfFaces)
{
    index = new (nothrow) int(newIndex);
    coordinates =  new (nothrow) double[3] ;

    if (coordinates == nullptr)
    {
        cout << "Error: memory could not be allocated";
    }
    else
    {
        for (int i=0; i<3; i++)
        {
           *(coordinates +i ) = *(newCoordinates + i);
        }
    }

    facesContainingPoint = new vector<int>;
}

/**
 * @brief Vertex::~Vertex
 * This method is the destructor of a Vertex Class, it deletes its objects
 */
Vertex::~Vertex()
{
    delete index;
    delete[] coordinates;
    delete facesContainingPoint;
}

/**
 * @brief Vertex::addNewFace
 * This method adds a face that contains the given vertex.
 * @param faceNumber: Face number wich contains the vertex.
 */
void Vertex::addNewFace(int faceNumber)
{
    vector<int>::iterator it;
    it = find ( (*facesContainingPoint).begin(), (*facesContainingPoint).end(), faceNumber);
    if(it == (*facesContainingPoint).end() )
    {
        //Element not found in facesContainingPoint
        (*facesContainingPoint).push_back(faceNumber);
    }
}

/**
 * @brief Vertex::DeleteFace
 * This method deletes a face that contains the given vertex.
 * @param faceNumber: Face to delete.
 */
void Vertex::deleteFace(int faceNumber)
{
    vector<int>::iterator it;
    it = find ( ( *facesContainingPoint ).begin(),
                ( *facesContainingPoint ).end(),
                faceNumber );

    if( it != ( *facesContainingPoint ).end() )
    {
        //Element found in facesContainingPoint
        ( * facesContainingPoint ).erase(it);
    }
}

/**
 * @brief Vertex::setCoordinates
 * This method writes the position of the given coordinates of the vereteex
 * @param newCoordinates: are the cooridnates value in X Y Z
 */
void Vertex::setCoordinates(double* newCoordinates)
{
    for(int i = 0; i<3 ; i++)
    {
        this->coordinates[i] = *(newCoordinates + i);
    }
}


/**
 * @brief Vertex::setCoordinates
 * This method writes the position of the given coordinates of the vereteex
 * @param newCoordinates: are the cooridnates value in X Y Z
 */
void Vertex::setCoordinates(double x, double y , double z)
{
    double newCoordinates[3] = { x, y, z};
    for(int i = 0; i<3 ; i++)
    {
        this->coordinates[i] = *(newCoordinates + i);
    }
}

/**
 * @brief Vertex::setIndex
 * This method allows to set the index of the vertex by the parameter newIndex
 * @param newIndex
 */
void Vertex::setIndex(int newIndex)
{
    *index=newIndex;
}

/**
 * @brief Vertex::getIndex
 * @returns the index value of the vertex
 */
int Vertex::getIndex()
{
    return *(this->index);
}

/**
 * @brief Vertex::getCoordinates
 * @return a pointer type double to the Coordinates of the given vertex
 */
double* Vertex::getCoordinates()
{
    return this->coordinates;
}

/**
 * @brief Vertex::getFaces
 * @return a std::vector containing all the faces that contains the vertex
 */
vector<int> Vertex::getFaces()
{
    return *(this->facesContainingPoint);
}
