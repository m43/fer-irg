//
// Created by m43 on 21. 03. 2020..
//

#include <regex>
#include <utility>
#include <memory>
#include <vector>

#include "matrix.h"

using namespace std;
using namespace linalg;


Matrix::Matrix(int rows, int columns) {
    elements_ = make_shared<vector<vector<double>>>(rows, vector<double>(columns, 0));
}

Matrix::Matrix(const vector<vector<double>> &elements) {
    elements_ = make_shared<vector<vector<double>>>(elements);
}

Matrix::Matrix(shared_ptr<vector<vector<double>>> elements) {
    elements_ = std::move(elements);
}


int Matrix::getRowsCount() const {
    return elements_->size();
}

int Matrix::getColsCount() const {
    return elements_->at(0).size();
}

double Matrix::get(int row, int column) const {
    throwIfIndexInvalid(row, column);

    return elements_->at(row).at(column);
}

IMatrix &Matrix::set(int row, int column, double value) {
    throwIfIndexInvalid(row, column);

    elements_->at(row).at(column) = value;
    return *this;
}

unique_ptr<IMatrix> Matrix::clone() const {
    return make_unique<Matrix>(*elements_);
}

unique_ptr<IMatrix> Matrix::newInstance(int rows, int columns) const {
    throwIfInvalidDimensions(rows, columns);

    return make_unique<Matrix>(rows, columns);
}

unique_ptr<Matrix> Matrix::parseSimple(const string &str) {
    int columns = -1;
    auto elements = make_shared<vector<vector<double>>>();

    int current_row = 0;
    int current_column = 0;
    elements->push_back(vector<double>());
    std::istringstream iss(str);
    for (std::string s; iss >> s;) {
        if (s == "|") {
            if (columns == -1) {
                columns = current_column + 1;
            } else {
                if (current_column + 1 != columns) {
                    throw invalid_argument("Each row needs to have the equal number of rows");
                }
            }
            current_column = 0;
            current_row++;
            elements->push_back(vector<double>());
        } else {
            (*elements).at(current_row).push_back(stod(s));
            current_column++;
        }
    }

    return make_unique<Matrix>(move(elements));
}

shared_ptr<Matrix> Matrix::identityMatrix(int dimension) {
    auto m = make_shared<Matrix>(dimension, dimension);
    for (int i = 0; i < dimension; i++) {
        m->set(i, i, 1);
    }
    return m;
}

