//
// Created by m43 on 21. 03. 2020..
//

#ifndef FER_IRG_ABSTRACT_MATRIX_H
#define FER_IRG_ABSTRACT_MATRIX_H

#include <functional>
#include "i_matrix.h"

namespace linalg {
    class AbstractMatrix : public IMatrix {
    public:
        ~AbstractMatrix() override;

        IMatrix &add(const IMatrix &other) override;

        [[nodiscard]] unique_ptr<IMatrix> nAdd(const IMatrix &other) const override;

        IMatrix &sub(const IMatrix &other) override;

        [[nodiscard]] unique_ptr<IMatrix> nSub(const IMatrix &other) const override;

        [[nodiscard]] unique_ptr<IMatrix> nMultiply(const IMatrix &other) const override;

        double determinant() const override;

        // TODO How should I go about nTranspose, what would be a better practice? What I did here is write implement
        //      two functions. First function takes no arguments and is virtual. It does the transposing after copying
        //      the current matrix and returns a new matrix. The second function is static takes a smart pointer to
        //      the matrix that needs to be transposed and then returns an transposed view of that matrix.
        //      The transposed view shares ownership of current matrix thanks to the given smart pointer.
        //      ...
        //      I find this approach as a inconvenient modeling approach because the static function is in the
        //      AbstractMatrix and one needs to know that fact to use the live transpose.
        //      A solution might be to move this static method to the IMatrix interface, but then the interface would
        //      not be pure virtual.
        //      Another solution might be to move the transposing functionality implementation to the final Matrix
        //      implementation so that the Matrix class could internally manipulate with an internally shared structure
        //      of elements (like shared_ptr<v<v<double>>>) and then could replicate itself without the need of
        //      a shared pointer to itself.
        //      ...
        //      I had the same problem with subMatrix function.
        [[nodiscard]]  unique_ptr<IMatrix> nTranspose() const override;

        static unique_ptr<IMatrix> nTranspose(shared_ptr<IMatrix> matrix);

        // unique_ptr<IMatrix> subMatrix(int row, int column) override;

        static unique_ptr<IMatrix> subMatrix(int row, int column, shared_ptr<IMatrix> matrix);

        [[nodiscard]] unique_ptr<IMatrix> nInvert() const override;

        [[nodiscard]] vector<vector<double>> toArray() const override;

        [[nodiscard]] string toString(int precision = 2) const;

        static unique_ptr<IVector> toVector(shared_ptr<IMatrix> matrix, bool liveView);

    protected:
        void throwIfNotOfSameDimensions(const IMatrix &other) const {
            if (getRowsCount() != other.getRowsCount() || getColsCount() != other.getColsCount()) {
                throw invalid_argument("Other matrix should be of same dimension.");
            }
        }

        static void throwIfInvalidDimensions(int rows, int columns) {
            if (rows <= 0 || columns <= 0) {
                throw invalid_argument(
                        "Invalid dimensions of matrix. Got dimensions: " + to_string(rows) + ", " + to_string(columns));
            }
        }

        void throwIfIndexInvalid(int row, int column) const {
            if (row < 0 || row >= getRowsCount()) {
                throw std::out_of_range("The given row number is invalid.");
            }
            if (column < 0 || column >= getColsCount()) {
                throw std::out_of_range("The given column number is invalid.");
            }
        }

        IMatrix &doFunction(const IMatrix &other, std::function<double(double, double)> func);
    };
}

#endif //FER_IRG_ABSTRACT_MATRIX_H
