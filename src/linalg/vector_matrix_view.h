//
// Created by m43 on 03. 04. 2020..
//

#ifndef FER_UI_VECTOR_MATRIX_VIEW_H
#define FER_UI_VECTOR_MATRIX_VIEW_H

#include "abstract_vector.h"

namespace linalg {
    class VectorMatrixView : public AbstractVector {
    public:
        explicit VectorMatrixView(shared_ptr<IMatrix> matrix);

        int getDimension() override;

        double get(int index) override;

        IVector &set(int index, double value) override;

        std::unique_ptr<IVector> clone() override;

        unique_ptr<IVector> newInstance(int elements) override;

    private:
        shared_ptr<IMatrix> originalMatrix_;
        int dimension_;
        bool rowMatrix_;
    };
}


#endif //FER_UI_VECTOR_MATRIX_VIEW_H
