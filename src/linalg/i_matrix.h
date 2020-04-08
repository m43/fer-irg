//
// Created by m34 on 16. 03. 2020..
//

#ifndef FER_IRG_I_MATRIX_H
#define FER_IRG_I_MATRIX_H

#include <memory>
#include "i_vector.h"

using namespace std;

namespace linalg {
    class IMatrix {
    public:

        virtual ~IMatrix() = default;

        [[nodiscard]] virtual int getRowsCount() const = 0;

        [[nodiscard]] virtual int getColsCount() const = 0;

        [[nodiscard]] virtual double get(int row, int column) const = 0;

        virtual IMatrix &set(int row, int column, double value) = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> clone() const = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> newInstance(int rows, int columns) const = 0;

        /**
         * @return a transposed copy of this matrix
         */
        [[nodiscard]] virtual unique_ptr<IMatrix> nTranspose() const = 0;

        // TODO I made it static in AbstractClass, not sure how to implement a live view in the case it is virtual: how
        //      can I make a live view without asking for a smart pointer of the respective matrix
        // /**
        //  * @param row the row to exclude in the submatrix
        //  * @param column the column to exclude in the submatrix
        //  * @return a sub matrix copy of the current matrix
        //  */
        // virtual unique_ptr<IMatrix> subMatrix(int row, int column) = 0;

        virtual IMatrix &add(const IMatrix &other) = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nAdd(const IMatrix &other) const = 0;

        virtual IMatrix &sub(const IMatrix &other) = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nSub(const IMatrix &other) const = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nMultiply(const IMatrix &other) const = 0;

        [[nodiscard]] virtual double determinant() const = 0;


        [[nodiscard]] virtual unique_ptr<IMatrix> nInvert() const = 0;

        [[nodiscard]] virtual vector<vector<double>> toArray() const = 0;

        // TODO moved to abstract matrix as static method, because I ask for the vector as a smart pointer argument
        //      and therefore it is static
        // virtual linalg::IVector toVector(bool liveView) = 0;

    };
}

#endif