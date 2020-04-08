//
// Created by m43 on 02. 04. 2020..
//

#ifndef FER_IRG_MATRIXTRANSPOSEVIEW_H
#define FER_IRG_MATRIXTRANSPOSEVIEW_H

#include "abstract_matrix.h"

namespace linalg {
    class MatrixTransposeView : public AbstractMatrix {
    public:

        ~MatrixTransposeView() override;

        explicit MatrixTransposeView(shared_ptr<IMatrix> original);

        [[nodiscard]] int getRowsCount() const override;

        [[nodiscard]] int getColsCount() const override;

        [[nodiscard]] double get(int row, int column) const override;

        IMatrix & set(int row, int column, double value) override;


        [[nodiscard]] unique_ptr<IMatrix> clone() const override;

        [[nodiscard]] unique_ptr<IMatrix> newInstance(int rows, int columns) const override;

        // TODO in the lab assigment was also the function "toarray" added here, but I see no
        //      difference in the way I would write it here than it is already written in the
        //      base class

    private:
        shared_ptr<IMatrix> originalMatrix_;
    };
}


#endif //FER_IRG_MATRIXTRANSPOSEVIEW_H
