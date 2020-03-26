//
// Created by m34 on 16. 03. 2020..
//

#ifndef FIRST_I_MATRIX_H
#define FIRST_I_MATRIX_H

#include "i_vector.h"

using namespace std;

namespace linalg {
    class IMatrix {
        virtual int getRowsCount() = 0;

        virtual int getColsCount() = 0;

        virtual double get(int row, int col) = 0;

        virtual IMatrix &set(int row, int column, double value) = 0;

        virtual unique_ptr<IMatrix> clone() = 0;

        virtual unique_ptr<IMatrix> newInstance(int row, int count) = 0;

        // TODO unique pointers probably wont work, I think that somehow a shared pointer is needed, not sure. Or at least a shared pointer to the data elements (among the two matrices)...
        virtual unique_ptr<IMatrix> nTranspose(bool live_view) = 0;

        virtual IMatrix &add(const IMatrix &other) = 0;

        virtual unique_ptr<IMatrix> nAdd(const IMatrix &other) = 0;

        virtual IMatrix &sub(const IMatrix &other) = 0;

        virtual unique_ptr<IMatrix> nSub(const IMatrix &other) = 0;

        virtual unique_ptr<IMatrix> nMultiply(const IMatrix &other) = 0;

        virtual double determinant() = 0;

        virtual unique_ptr<IMatrix> subMatrix(int a, int b, bool ae) = 0;

        virtual unique_ptr<IMatrix> nInvert() = 0;

        virtual double **toArray() = 0; // TODO is double[][] good? myb some std::vector of std::vectors?

//        virtual linalg::IVector toVector(bool ae) = 0; // TODO

        // TODO the destructor is supposed to be here as well, riiight?
        virtual ~IMatrix() = 0;
    };
}

#endif