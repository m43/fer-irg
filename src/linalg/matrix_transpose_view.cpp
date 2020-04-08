//
// Created by m43 on 02. 04. 2020..
//

#include "matrix_transpose_view.h"
#include <utility>

MatrixTransposeView::~MatrixTransposeView() = default;

MatrixTransposeView::MatrixTransposeView(shared_ptr<IMatrix> original) {
    originalMatrix_ = std::move(original);
}

int MatrixTransposeView::getRowsCount() const {
    return originalMatrix_->getColsCount();
}

int MatrixTransposeView::getColsCount() const {
    return originalMatrix_->getRowsCount();
}

double MatrixTransposeView::get(int row, int column) const {
    throwIfIndexInvalid(row, column);

    return originalMatrix_->get(column, row);
}

IMatrix &MatrixTransposeView::set(int row, int column, double value) {
    throwIfIndexInvalid(row, column);

    originalMatrix_->set(column, row, value);
    return *this;
}

unique_ptr<IMatrix> MatrixTransposeView::clone() const {
    return make_unique<MatrixTransposeView>(originalMatrix_);
}

unique_ptr<IMatrix> MatrixTransposeView::newInstance(int rows, int columns) const {
    throwIfInvalidDimensions(rows, columns);
    return originalMatrix_->newInstance(rows, columns);
}


