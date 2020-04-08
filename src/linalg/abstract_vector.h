//
// Created by m34 on 16. 03. 2020..
//

#ifndef FER_IRG_ABSTRACT_VECTOR_H
#define FER_IRG_ABSTRACT_VECTOR_H

#include <memory>
#include "i_vector.h"

namespace linalg {

    class AbstractVector : public IVector {
    public:
        ~AbstractVector() override = default;

        // AbstractVector(); // TODO do i need a constructor here?

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

        // TODO The functions "toRowMatrix" and "toColumnMatrix" are not virtual but static in order to be able to
        //      receive the additional parameter "shared_ptr<IVector> vector" of the vector that needs to be
        //      worked on. Therefore the implementation does not depend on any specific vector object, but can be made
        //      static. The problem I encountered was not being able to implement a liveView otherwise - how should I
        //      pass a *SMART* pointer to the "MatrixVectorView" constructor if I want to be sure that the given
        //      smart pointer is a valid one aka the real owner?
        //      ...
        //      If I was implementing the function with the signature toRowMatrix(bool liveView), then I don't see
        //      how I could return unique_ptr<IMatrix> when the returned matrix points to the original IVector that is
        //      already owned by an client that created the original vector.
        //      ...
        //      To clarify things further, here is a code snipped of using the function toRowMatrix:
        //          shared_ptr<IVector> myOriginalVector = Vector(3);
        //          shared_ptr<IMatrix> rowMatrixLiveView = AbstractVector::toRowMatrix(myOriginalVector, true);
        //          // now if myOriginalVector gets deleted because reasons, then rowMatrixLiveView would work just fine
        //      ...
        //      And here is a code snippet of how the code might look if shared_ptr<IVector> was not a argument of the
        //      function and what problem would arise:
        //          shared_ptr<IVector> myOriginalVector = Vector(3);
        //          shared_ptr<IMatrix> rowMatrixLiveView = myOriginalVector.toRowMatrix(true);
        //          //  now if myOriginalVector gets deleted (because reasons), then rowMatrixLiveView would be in
        //          //  a inconsistent state!
        //      ...
        //      What would be a better way of modeling this?
        //      I had the same issue with modeling matrices (subMatrix).

        /**
         * Return a row matrix view of this vector
         * @param liveView should the returned matrix be a live view of this vector or rather a copy
         * @return a row matrix of this vector
         */
        static unique_ptr<IMatrix> toRowMatrix(shared_ptr<IVector> vector, bool liveView);

        /**
         * Return a column matrix view of this vector
         * @param liveView should the returned matrix be a live view of this vector or rather a copy
         * @return a column matrix of this vector
         */
        static unique_ptr<IMatrix> toColumnMatrix(shared_ptr<IVector> vector, bool liveView);

        std::vector<double> toArray() override;

        std::string toString(int precision = 2);

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

        static void throwIfInvalidDimension(int dimension) {
            if (dimension <= 0) {
                throw std::out_of_range("Vector dimension must be positive.");
            }
        }
    };
}

#endif //FER_IRG_ABSTRACT_VECTOR_H
