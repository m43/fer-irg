//
// Created by m43 on 03. 04. 2020..
//

#include "matrix_vector_view.h"
#include "matrix.h"

MatrixVectorView::MatrixVectorView(shared_ptr<IVector> vector, bool asRowMatrix) {
    originalVector_ = move(vector);
    asRowMatrix_ = asRowMatrix;
}

int MatrixVectorView::getRowsCount() const {
    return (asRowMatrix_ ? 1 : originalVector_->getDimension());
}

int MatrixVectorView::getColsCount() const {
    return (asRowMatrix_ ? originalVector_->getDimension() : 1);
}

double MatrixVectorView::get(int row, int column) const {
    throwIfIndexInvalid(row, column);

    if (asRowMatrix_) {
        return originalVector_->get(column);
    } else {
        return originalVector_->get(row);
    }
}


IMatrix &MatrixVectorView::set(int row, int column, double value) {
    throwIfIndexInvalid(row, column);

    if (asRowMatrix_) {
        originalVector_->set(column, value);
    } else {
        originalVector_->set(row, value);
    }

    return *this;
}

unique_ptr<IMatrix> MatrixVectorView::clone() const {
    return make_unique<MatrixVectorView>(originalVector_->clone(), asRowMatrix_);
}

unique_ptr<IMatrix> MatrixVectorView::newInstance(int rows, int columns) const {
    throwIfInvalidDimensions(rows, columns);
    // TODO who should create a new instance for me? I can only access the original vector from here, no matrix object

    // this is pretty sneaky but works:
    return make_unique<Matrix>(rows, columns);
}
