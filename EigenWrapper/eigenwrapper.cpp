#include "eigenwrapper.h"

/**
 * @brief EVector3d::EVector3d Default constructor for EVector3d
 */
EVector3d::EVector3d()
{

}

/**
 * @brief EVector3d::operator < Method modification for operator < so that sets can be used on this type of element
 * @param vector Input vector of class EVector3d
 * @return Returns a boolean depending on the conditions for < comparison. Element wise comparison are performed.
 */
bool EVector3d::operator<(const EVector3d  vector) const
{
    if(this->x() < vector.x() || this->y() < vector.y() || this->z() < vector.z()) return true;
    else return false;
}

/**
 * @brief EMatrixXd::EMatrixXd Default constructor for EMatrixXd
 */
EMatrixXd::EMatrixXd(int rows, int cols):MatrixXd(rows, cols)
{

}

/**
 * @brief EVectorXi Wrapped constructor for creation of vector of integers of size numElem
 * @param numElem Number of elements of vector
 */
EVectorXi::EVectorXi(int numElem):VectorXi(numElem)
{

}

/**
 * @brief EMatrixXi Wrapped constructor for building matrix of integers of size rows x cols
 * @param rows Number of rows
 * @param cols Number of columns
 */
EMatrixXi::EMatrixXi(int rows, int cols):MatrixXi(rows, cols)
{

}

/**
 * @brief EVectorXd is the constructor for creating a vector of class EVectorXd with numElem elements
 * @param numElem Number of elements for the vector
 */
EVectorXd::EVectorXd(int numElem):VectorXd(numElem)
{

}
