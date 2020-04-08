//
// Created by m43 on 02. 04. 2020..
//

#include "matrix_sub_matrix_view.h"

MatrixSubMatrixView::~MatrixSubMatrixView() = default;

MatrixSubMatrixView::MatrixSubMatrixView(int excludeRow, int excludeColumn, shared_ptr<IMatrix> original) {
    originalMatrix_ = move(original);
    excludeRow_ = excludeRow;
    excludeColumn_ = excludeColumn;
}

int MatrixSubMatrixView::getRowsCount() const {
    return originalMatrix_->getRowsCount() - 1;
}

int MatrixSubMatrixView::getColsCount() const {
    return originalMatrix_->getColsCount() - 1;
}

double MatrixSubMatrixView::get(int row, int column) const {
    throwIfIndexInvalid(row, column);

    return originalMatrix_->get(remapRow(row), remapColumn(column));
}

IMatrix &MatrixSubMatrixView::set(int row, int column, double value) {
    throwIfIndexInvalid(row, column);

    return originalMatrix_->set(remapRow(row), remapColumn(column), value);
}

unique_ptr<IMatrix> MatrixSubMatrixView::clone() const {

    return make_unique<MatrixSubMatrixView>(excludeRow_, excludeColumn_, originalMatrix_->clone());
}

unique_ptr<IMatrix> MatrixSubMatrixView::newInstance(int rows, int columns) const {
    throwIfInvalidDimensions(rows, columns);

    return originalMatrix_->newInstance(rows, columns);
}

int MatrixSubMatrixView::remapRow(int row) const {
    return row >= excludeRow_ ? row + 1 : row;
}

int MatrixSubMatrixView::remapColumn(int column) const {
    return column >= excludeColumn_ ? column + 1 : column;
}
