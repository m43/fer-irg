//
// Created by m43 on 03. 04. 2020..
//

#include "vector_matrix_view.h"

VectorMatrixView::VectorMatrixView(shared_ptr<IMatrix> matrix) {
    int rows = matrix->getRowsCount();
    int columns = matrix->getColsCount();

    if (rows != 1 && columns != 1) {
        throw invalid_argument("The given matrix is not a one liner.");
    }
    rowMatrix_ = rows == 1;
    dimension_ = max(rows, columns);
    originalMatrix_ = move(matrix);
}

int VectorMatrixView::getDimension() {
    return dimension_;

    // TODO is it a better practice to save the dimension in a private variable dimensions_ or rather to call the
    //      following each time (the following line calculates the number of elements in the saved originalMatrix_
    //      member variable):
    // return rowMatrix_ ? originalMatrix_->getColsCount() : originalMatrix_->getRowsCount();
}

double VectorMatrixView::get(int index) {
    if (index < 0 || index >= dimension_) {
        throw invalid_argument("Given index out of range");
    }

    return rowMatrix_ ? originalMatrix_->get(0, index) : originalMatrix_->get(index, 0);
}


IVector &VectorMatrixView::set(int index, double value) {
    throwIfIndexInvalidRange(index);

    if (index < 0 || index >= dimension_) {
        throw invalid_argument("Given index out of range");
    }

    rowMatrix_ ? originalMatrix_->set(0, index, value) : originalMatrix_->set(index, 0, value);

    return *this;
}

std::unique_ptr<IVector> VectorMatrixView::clone() {
    return make_unique<VectorMatrixView>(originalMatrix_->clone());
}

unique_ptr<IVector> VectorMatrixView::newInstance(int dimension) {
    throwIfInvalidDimension(dimension);

    return make_unique<VectorMatrixView>(originalMatrix_->newInstance(0, dimension));
}
