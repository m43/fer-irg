//
// Created by m43 on 16. 03. 2020..
//

#ifndef FER_IRG_I_VECTOR_H
#define FER_IRG_I_VECTOR_H

#include <vector>
#include <stdexcept>
#include <boost/serialization/array.hpp>
#include <array>
#include "i_vector.h"
#include "i_matrix.h"


namespace linalg {
    class IMatrix; // TODO Got a circular reference, this is a quick fix.

    // TODO are interfaces a good way at all of modeling in C++?
    //      Should I maybe have written only the AbstractVector?


    /**
     * This class models an abstract class that acts as an interface for vectors. These vectors are n-dimensional
     * structures that hold double values at indexes 0 - (n-1).
     *
     * @author Frano Rajič
     */
    class IVector {
    public:

        virtual ~IVector() = default;

        /**
         * @param index the index of the value to get
         * @return the value in vector at index
         */
        virtual double get(int index) = 0;

        /**
         * @param index the index of the value to set
         * @param value the value to set
         * @return this vector after update
         */
        virtual IVector &set(int index, double value) = 0;

        /**
         * @return the number of dimensions of this vector
         */
        virtual int getDimension() = 0;

        /**
         * @return a clone of this vector
         */
        virtual std::unique_ptr<IVector> clone() = 0;


        /**
         * Get a part of the vector starting from index=0 till newSize-1. If newSize is greater than the number of
         * dimensions of the current vector, then the rest will be filled with zeros.
         *
         * @param dimensions how many dimensions to clone
         * @return a new vector representing a part of this vector
         */
        virtual std::unique_ptr<IVector> copyPart(int newSize) = 0;


        /**
         * Function returns a new instance of an vector with given dimension number.
         *
         * @param dimension number of dimensions
         * @return the newly created vector with specified dimensions
         */
        virtual std::unique_ptr<IVector> newInstance(int dimension) = 0;

        /**
         * @param other the vector to add
         * @return this vector after adding the given vector
         */
        virtual IVector &add(IVector &other) = 0;

        /**
         * @param other the vector to add
         * @return a new vector that is the result of adding the given vector to this vector
         */
        virtual std::unique_ptr<IVector> nAdd(IVector &other) = 0;

        /**
         * @param other the vector that will be used to subtract
         * @return this vector subtracted by the given vector
         */
        virtual IVector &sub(IVector &other) = 0;

        /**
         * @param other the vector that will be used to subtract
         * @return a new vector that si the result of subtracting the given vector from this vector
         */
        virtual std::unique_ptr<IVector> nSub(IVector &other) = 0;

        /**
         * @param scalar the scalar value to multiply with
         * @return this vector multiplied with given scalar value
         */
        virtual IVector &scalarMultiply(double scalar) = 0;

        /**
         * @param scalar the scalar value to multiply with
         * @return a new vector that represents this vector multiplied with given scalar value
         */
        virtual std::unique_ptr<IVector> nScalarMultiply(double scalar) = 0;

        /**
         * @return the norm value of this vector
         */
        virtual double norm() = 0;

        /**
         * @return this vector normalized
         */
        virtual IVector &normalize() = 0;

        /**
         * @return a new vector that is the result of normalization of this vector
         */
        virtual std::unique_ptr<IVector> nNormalize() = 0;

        /**
         * @param other the other vector
         * @return the cosine of the angle between this and the given vector
         */
        virtual double cosine(IVector &other) = 0;

        /**
         * @param other the vector to make the scalar (aka dot) product with
         * @return the scalar product of this vector with the given vector
         */
        virtual double dotProduct(IVector &other) = 0;

        /**
         * Return the cross product of this vector with the given vector. This function only determines
         * the cross product for vectors of dimension=3.
         *
         * @param other the vector to make the vector (aka cross) product with
         * @return the vector product of this vector with the given vector
         */
        virtual std::unique_ptr<IVector> nCrossProduct3D(IVector &other) = 0;

        /**
         * Return a new vector for which this vector is the homogeneous coordinate format. The resulting vector will
         * have (n-1) dimensions if this vector has n dimensions.
         * @return a new
         */
        virtual std::unique_ptr<IVector> nFromHomogeneous() = 0;

        // TODO moved to static function of AbstractVector
        // virtual IMatrix &toRowMatrix(bool liveView) = 0;
        // virtual IMatrix &toColumnMatrix(bool) = 0;

        /**
         * Function that turns the this vector values into an std::vector. Not really an array, but still :P
         * @return std::vector containing the stored in this vector
         */
        virtual std::vector<double> toArray() = 0;

    };
}

#endif //FER_IRG_I_VECTOR_H
