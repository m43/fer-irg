//
// Created by m43 on 03. 04. 2020..
//

#ifndef FER_IRG_MATRIXVECTORVIEW_H
#define FER_IRG_MATRIXVECTORVIEW_H

#include "i_vector.h"
#include "abstract_matrix.h"

namespace linalg {
    class MatrixVectorView : public AbstractMatrix {
    public:
        MatrixVectorView(shared_ptr<IVector> vector, bool asRowMatrix);

        [[nodiscard]] int getRowsCount() const override;

        [[nodiscard]] int getColsCount() const override;

        [[nodiscard]] double get(int row, int column) const override;

        IMatrix &set(int row, int column, double value) override;


        [[nodiscard]] unique_ptr<IMatrix> clone() const override;

        [[nodiscard]] unique_ptr<IMatrix> newInstance(int rows, int columns) const override;

    private:
        bool asRowMatrix_;
        shared_ptr<IVector> originalVector_;
    };
}

#endif //FER_IRG_MATRIXVECTORVIEW_H
