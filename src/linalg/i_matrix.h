//
// Created by m34 on 16. 03. 2020..
//

#ifndef FER_UI_I_MATRIX_H
#define FER_UI_I_MATRIX_H

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

        // TODO How should I go about nTranspose, what would be a better practice than this what I did right here?
        //      Like, I make the caller pass a shared pointer in order to transpose the matrix and then I copy
        //      an instance of that pointer for myself.
        //      Should, for example the transposing functionality be actually moved to Matrix class? Then matrix
        //      could internally manipulate with an inner shared structure of elements (like shared_ptr<v<v<double>>>)
        [[nodiscard]] virtual unique_ptr<IMatrix> nTranspose() const = 0;

        // TODO same as with transpose
        // virtual unique_ptr<IMatrix> subMatrix(int row, int column) = 0;

        virtual IMatrix &add(const IMatrix &other) = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nAdd(const IMatrix &other) const = 0;

        virtual IMatrix &sub(const IMatrix &other) = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nSub(const IMatrix &other) const = 0;

        [[nodiscard]] virtual unique_ptr<IMatrix> nMultiply(const IMatrix &other) const = 0;

        [[nodiscard]] virtual double determinant() const = 0;


        [[nodiscard]] virtual unique_ptr<IMatrix> nInvert() const = 0;

        [[nodiscard]] virtual vector<vector<double>> toArray() const = 0;

        // TODO moved to abstract matrix as static method, because I ask for the vector as a smart pointer parameter
        //      and therefore it is static
        // virtual linalg::IVector toVector(bool liveView) = 0;

    };
}

#endif