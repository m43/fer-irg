//
// Created by m34 on 16. 03. 2020..
//

#ifndef FIRST_ABSTRACT_VECTOR_H
#define FIRST_ABSTRACT_VECTOR_H

#include <memory>
#include "i_vector.h"

namespace linalg {

    class AbstractVector : public IVector {
    public:
        // AbstractVector(); // TODO do i need a constructor here?

        // TODO Should all this functions/methods be virtual?
        // TODO is it a better practice to leave out the parameter name rather than to write it everywhere.
        //      Like the parameter 'other', it could have only be written in the end in the .cpp file, it is not
        //      necessary to write it everywhere, but I'm not sure which is better. I've picked to write the parameter
        //      so that it is easier to write documentation (I tend to use @param, coming from a Java background and
        //      javadoc...)

        IVector &add(IVector &other) override;

        std::unique_ptr<IVector> nAdd(IVector &other) override;

        IVector &sub(IVector &other) override;

        std::unique_ptr<IVector> nSub(IVector &other) override;

        IVector &scalarMultiply(double scalar) override;

        std::unique_ptr<IVector> nScalarMultiply(double scalar) override;

        double norm() override;

        IVector &normalize() override;

        std::unique_ptr<IVector> nNormalize() override;

        double cosine(IVector &other) override;

        double dotProduct(IVector &other) override;

        std::unique_ptr<IVector> nCrossProduct3D(IVector &other) override;

        std::unique_ptr<IVector> nFromHomogeneous() override;

        std::unique_ptr<IVector> copyPart(int newSize) override;

        IMatrix &toRowMatrix(bool) override;

        IMatrix &toColumnMatrix(bool) override;

        std::vector<double> toArray() override;

        std::string toString(int precision);

    protected:
        /**
         * Help method to check whether this vector has the same dimensions as the given one.
         *
         * @param other the vector to compare the dimensions with
         * @return true if same dimensions
         */
        bool checkIfSameDimensions(IVector &other) {
            return getDimension() == other.getDimension();
        }

        /**
         * Help method that throws an invalid_argument exception if the given vector is not of the same dimensions
         * as this one.
         *
         * @param other The vector to compare the dimensions with
         */
        void throwIfNotOfSameDimensions(IVector &other) {
            if (!checkIfSameDimensions(other)) {
                throw std::invalid_argument("Vectors not of same dimension.");
            }
        }

        /**
         * Help method to check whether the given index is a valid index for this vector.
         *
         * @param index the index to check
         * @return true if index in vector indexing range
         */
        bool checkIfIndexInValidRange(int index) {
            return !(index < 0 || index >= getDimension());
        }

        /**
         * Help method that throws an out_of_range exception if the given index is invalid.
         *
         * @param index the index to check
         */
        void throwIfIndexInvalidRange(int index) {
            if (!checkIfIndexInValidRange(index)) {
                throw std::out_of_range("The given index is not in valid range for this vector.");
            }
        }
    };
}

#endif //FIRST_ABSTRACT_VECTOR_H
