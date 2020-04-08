//
// Created by m43 on 21. 03. 2020..
//

#include "abstract_matrix.h"
#include "matrix_transpose_view.h"
#include "matrix_sub_matrix_view.h"
#include "vector_matrix_view.h"
#include <functional>
#include <iomanip>

using namespace std;


AbstractMatrix::~AbstractMatrix() = default;;

IMatrix &AbstractMatrix::doFunction(const IMatrix &other, function<double(double, double)> func) {
    throwIfNotOfSameDimensions(other);

    for (int i = getRowsCount() - 1; i >= 0; i--) {
        for (int j = getColsCount() - 1; j >= 0; j--) {
            set(i, j, func(get(i, j), other.get(i, j)));
        }
    }
    return *this;
}

IMatrix &AbstractMatrix::add(const IMatrix &other) {
    return doFunction(other, plus<>());
}

unique_ptr<IMatrix> AbstractMatrix::nAdd(const IMatrix &other) const {
    auto cloned = clone();
    cloned->add(other);
    return cloned;
}

IMatrix &AbstractMatrix::sub(const IMatrix &other) {
    return doFunction(other, minus<>());
}

unique_ptr<IMatrix> AbstractMatrix::nSub(const IMatrix &other) const {
    auto cloned = clone();
    cloned->sub(other);
    return cloned;
}

unique_ptr<IMatrix> AbstractMatrix::nMultiply(const IMatrix &other) const {
    if (getColsCount() != other.getRowsCount()) {
        throw invalid_argument("Incompatible matrix given.");
    }

    int rows = getRowsCount();
    int columns = other.getColsCount();

    auto result = newInstance(rows, columns);

    for (int i = rows - 1; i >= 0; i--) {
        for (int j = columns - 1; j >= 0; j--) {
            double value = 0;
            for (int k = getColsCount() - 1; k >= 0; k--) {
                value += get(i, k) * other.get(k, j);
            }
            result->set(i, j, value);
        }
    }

    return result;
}

unique_ptr<IMatrix> AbstractMatrix::nTranspose() const {
    auto result = newInstance(getColsCount(), getRowsCount());
    for (int i = result->getRowsCount() - 1; i >= 0; i--) {
        for (int j = result->getColsCount() - 1; j >= 0; j--) {
            result->set(i, j, get(j, i));
        }
    }
    return result;
}

unique_ptr<IMatrix> AbstractMatrix::nTranspose(shared_ptr<IMatrix> matrix) {
    return make_unique<MatrixTransposeView>(move(matrix));
}

vector<vector<double>> AbstractMatrix::toArray() const {
    vector<vector<double>> result(getRowsCount(), vector<double>(getColsCount(), 0));

    for (int i = getRowsCount() - 1; i >= 0; i--) {
        for (int j = getColsCount() - 1; j >= 0; j--) {
            result[i][j] = get(j, i);
        }
    }
    return result;
}

string AbstractMatrix::toString(int precision) const {
    std::ostringstream oss;

    int rows = getRowsCount();
    int columns = getColsCount();
    int width = max(9, precision + 3);

    oss << "┌" << std::string(columns * (width + 1) + 2 - 2, ' ') << "┐\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j != 0) {
                oss << " ";
            } else {
                oss << "│";
            }
            oss << std::setw(width) << std::setprecision(precision) << get(i, j);
        }
        oss << " │\n";
    }
    oss << "└" << std::string(columns * (width + 1) + 2 - 2, ' ') << "┘\n";

    return oss.str();
}

unique_ptr<IMatrix> AbstractMatrix::subMatrix(int row, int column, shared_ptr<IMatrix> matrix) {
    return make_unique<MatrixSubMatrixView>(row, column, move(matrix));
}

double deepDeterminant(const shared_ptr<IMatrix> &matrix) {
    // TODO very inefficient if modeled with current sub matrix because each sub matrix points to its original matrix,
    //      not knowing that the original matrix is already a sub matrix. I implemented sub matrix not to use
    //      the structures int[] excludeRows and int[]excludeColumns, but to only remember the one row and one column
    //      that needs to be excluded. So if there are 10 sub matrices, then each would point at the one above it like
    //      this: 10th -> 9th -> 8th -> ... 2nd -> 1st -> originalMatrix
    //      instead of just 10th -> originalMatrix

    if (matrix->getColsCount() == 1) {
        return matrix->get(0, 0);
    }

    double result = 0;
    for (int c = matrix->getColsCount() - 1; c >= 0; c--) {
        result += (c % 2 == 0 ? 1 : -1) * matrix->get(0, c) * deepDeterminant(AbstractMatrix::subMatrix(0, c, matrix));
    }
    return result;
}

double AbstractMatrix::determinant() const {
    // TODO rewrite when sub matrix gets remodeled
    if (getColsCount() != getRowsCount()) {
        throw invalid_argument("Non-square matrices do not have determinants.");
    }
    return deepDeterminant(shared_ptr<IMatrix>(this->clone()));
}

unique_ptr<IMatrix> AbstractMatrix::nInvert() const {
    if (getColsCount() != getRowsCount()) {
        throw invalid_argument("Non square matrices do not have an inverse.");
    }

    auto cloned = shared_ptr<IMatrix>(this->clone());

    auto result = clone();
    double det = determinant();

    for (int i = getRowsCount() - 1; i >= 0; i--) {
        for (int j = getColsCount() - 1; j >= 0; j--) {
            result->set(i, j, (((i + j) % 2 == 0 ? 1 : -1) * subMatrix(i, j, cloned)->determinant()) / det);
        }
    }

    return result->nTranspose();
}

unique_ptr<IVector> AbstractMatrix::toVector(shared_ptr<IMatrix> matrix, bool liveView) {
    if (liveView) {
        return make_unique<VectorMatrixView>(matrix);
    } else {
        return make_unique<VectorMatrixView>(matrix->clone());
    }
}
