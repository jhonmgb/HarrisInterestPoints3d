#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::Vector3d;
using Eigen::VectorXi;
using Eigen::MatrixXi;
using Eigen::VectorXd;

#ifndef EIGENWRAPPER_H
#define EIGENWRAPPER_H

/**
 * @brief The EVector3d class to wrap the Vector3d from Eigen. Operator < is modified so that it is valid for use in sets
 */
class EVector3d: public Vector3d
{
public:
    /**
     * @brief EVector3d Default constructor for wrapper class EVector3d
     */
    EVector3d();

    /**
     * @brief operator < Function for overloading operator < for class EVector3d
     * @return Boolean defined according to element-wise comparisons
     */
    bool operator<(const EVector3d) const;
};

/**
 * @brief The EMatrixXd class to wrap the MatrixXd from Eigen. This type is used for storing data in Backend
 */
class EMatrixXd: public MatrixXd
{
public:
    /**
     * @brief EMatrixXd Default constructor for wrapper class EMatrixXd
     */
    EMatrixXd();

    /**
     * @brief EMatrixXd Wrapper constructor for creating NxM matrix
     * @param rows Number of rows of the matrix
     * @param cols Number of columns of the matrix
     */
    EMatrixXd(int rows, int cols);
};

/**
 * @brief The EVectorXi class wraps the VectorXi from Eigen. Used for storing integers
 */
class EVectorXi: public VectorXi
{
public:
    /**
     * @brief EVectorXi Default constructor for wrapper class EVectorXi
     */
    EVectorXi();

    /**
     * @brief EVectorXi Wrapped constructor for creation of vector of integers of size numElem
     * @param numElem Number of elements of vector
     */
    EVectorXi(int numElem);
};

/**
 * @brief The EMatrixXi class wraps the MatrixXi class from Eigen. Used for storing the faces
 */
class EMatrixXi: public MatrixXi
{
public:
    /**
     * @brief EMatrixXi Default constructor for wrapper class EMatrixXi
     */
    EMatrixXi();

    /**
     * @brief EMatrixXi Wrapped constructor for building matrix of integers of size rows x cols
     * @param rows Number of rows
     * @param cols Number of columns
     */
    EMatrixXi(int rows, int cols);
};

/**
 * @brief The EVectorXd class wraps the class VectorXd of the Eigen library
 */
class EVectorXd: public VectorXd
{
public:
    /**
     * @brief EVectorXd is the default constructor for class EVectorXd
     */
    EVectorXd();

    /**
     * @brief EVectorXd is the constructor for creating a vector of class EVectorXd with numElem elements
     * @param numElem Number of elements for the vector
     */
    EVectorXd(int numElem);
};

#endif // EIGENWRAPPER_H
