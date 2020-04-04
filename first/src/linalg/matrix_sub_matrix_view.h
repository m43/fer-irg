//
// Created by m43 on 02. 04. 2020..
//

#ifndef FIRST_MATRIXSUBMATRIXVIEW_H
#define FIRST_MATRIXSUBMATRIXVIEW_H

#include "abstract_matrix.h"

namespace linalg {
    class MatrixSubMatrixView : public AbstractMatrix {
    public:

        // TODO remodel subMatrix functionality

        ~MatrixSubMatrixView() override;

        MatrixSubMatrixView(int excludeRow, int excludeColumn, shared_ptr<IMatrix> original);

        [[nodiscard]] int getRowsCount() const override;

        [[nodiscard]] int getColsCount() const override;

        [[nodiscard]] double get(int row, int column) const override;

        IMatrix &set(int row, int column, double value) override;

        [[nodiscard]] unique_ptr<IMatrix> clone() const override;

        [[nodiscard]] unique_ptr<IMatrix> newInstance(int rows, int columns) const override;

        // unique_ptr<IMatrix> subMatrix(int row, int column) override;

    private:
        shared_ptr<IMatrix> originalMatrix_;
        int excludeRow_;
        int excludeColumn_;

        // TODO not sure how to incorporate this constructor with shared_ptr's. With the static subMatrix that is written
        //      this constructor is useless. The static method is in AbstractMatrix and is useless here.
        // MatrixSubMatrixView(int excludeRows[], int excludeColumns[], shared_ptr<IMatrix> original);

        [[nodiscard]] inline int remapRow(int row) const;

        [[nodiscard]] inline int remapColumn(int column) const;
    };
}

#endif //FIRST_MATRIXSUBMATRIXVIEW_H
