//
// Created by m43 on 21. 03. 2020..
//

#ifndef FIRST_ABSTRACT_MATRIX_H
#define FIRST_ABSTRACT_MATRIX_H

#include <functional>
#include "i_matrix.h"

namespace linalg {
    class AbstractMatrix : public IMatrix {
    public:
        ~AbstractMatrix() override;

        [[nodiscard]]  unique_ptr<IMatrix> nTranspose() const override;

        static unique_ptr<IMatrix> nTranspose(shared_ptr<IMatrix> matrix);

        IMatrix &add(const IMatrix &other) override;

        [[nodiscard]] unique_ptr<IMatrix> nAdd(const IMatrix &other) const override;

        IMatrix &sub(const IMatrix &other) override;

        [[nodiscard]] unique_ptr<IMatrix> nSub(const IMatrix &other) const override;

        [[nodiscard]] unique_ptr<IMatrix> nMultiply(const IMatrix &other) const override;

        double determinant() const override;

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
                throw invalid_argument("Invalid dimensions of matrix. Got dimensions: " + to_string(rows) + ", " + to_string(columns));
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

#endif //FIRST_ABSTRACT_MATRIX_H
