//
// Created by m34 on 16. 03. 2020..
//

#include <cmath>
#include <iostream>
#include <iomanip>
#include "i_vector.h"
#include "abstract_vector.h"
#include "i_matrix.h"
#include "abstract_matrix.h"
#include "matrix_vector_view.h"

using namespace std;
using namespace linalg;

IVector &AbstractVector::add(IVector &other) {
    throwIfNotOfSameDimensions(other);

    for (int i = getDimension() - 1; i >= 0; i--) {
        set(i, get(i) + other.get(i));
    }
    return *this;
}

unique_ptr<IVector> AbstractVector::nAdd(IVector &other) {
    auto result = clone();
    result->add(other); // TODO it would be cool to be able to chain commands like in streams :)
    return result;
}

IVector &AbstractVector::sub(IVector &other) {
    throwIfNotOfSameDimensions(other);

    for (int i = getDimension() - 1; i >= 0; i--) {
        set(i, get(i) - other.get(i));
    }
    return *this;
}

unique_ptr<IVector> AbstractVector::nSub(IVector &other) {
    auto result = clone();
    result->sub(other);
    return result;
}

IVector &AbstractVector::scalarMultiply(double scalar) {
    for (int i = 0; i < getDimension(); i++) {
        set(i, scalar * get(i));
    }
    return *this;
}

unique_ptr<IVector> AbstractVector::nScalarMultiply(double scalar) {
    auto result = clone();
    result->scalarMultiply(scalar);
    return result;
}

double AbstractVector::norm() {
    double squares = 0;
    for (int i = getDimension() - 1; i >= 0; i--) {
        double elem = get(i);
        squares += elem * elem;
    }
    return sqrt(squares);
}

IVector &AbstractVector::normalize() {
    double normValue = norm();
    for (int i = getDimension() - 1; i >= 0; i--) {
        set(i, get(i) / normValue);
    }
    return *this;
}

unique_ptr<IVector> AbstractVector::nNormalize() {
    auto result = clone();
    result->normalize();
    return result;
}

double AbstractVector::cosine(IVector &other) {
    return dotProduct(other) / (norm() * other.norm());
}

double AbstractVector::dotProduct(IVector &other) {
    throwIfNotOfSameDimensions(other);


    double result = 0;
    for (int i = getDimension() - 1; i >= 0; i--) {
        result += get(i) * other.get(i);
    }
    return result;
}

unique_ptr<IVector> AbstractVector::nCrossProduct3D(IVector &other) {
    if (getDimension() != 3) {
        throw std::invalid_argument("Vector must have 3 dimensions.");
    }
    throwIfNotOfSameDimensions(other);


    std::vector<double> v1 = toArray();
    std::vector<double> v2 = other.toArray();

    auto result = newInstance(getDimension());
    result->set(0, v1[1] * v2[2] - v1[2] * v2[1]);
    result->set(1, v1[0] * v2[2] - v1[2] * v2[0]);
    result->set(2, v1[0] * v2[1] - v1[1] * v2[0]);

    return result;
}

unique_ptr<IVector> AbstractVector::nFromHomogeneous() {
    if (getDimension() == 1) {
        throw std::invalid_argument("Dimension cannot be 1.");
    }

    double homogeneousComponent = get(getDimension() - 1);
    // TODO is it OK to divide by 0 or should I rather add an check and exception throwing

    auto result = newInstance(getDimension() - 1);
    for (int i = getDimension() - 2; i >= 0; i--) {
        result->set(i, get(i) / homogeneousComponent);
    }

    return result;
}

std::vector<double> AbstractVector::toArray() {
    std::vector<double> result;

    for (int i = 0; i < getDimension(); i++) {
        result.push_back(get(i));
    }

    return result;
}

unique_ptr<IVector> AbstractVector::copyPart(int newSize) {
    if (newSize <= 0) {
        throw std::invalid_argument("New size must be a positive number.");
    }

    auto result = newInstance(newSize);
    for (int i = newSize - 1, currentDimension = getDimension(); i >= 0; i--) {
        result->set(i, i >= currentDimension ? 0 : get(i));
    }

    return result;
}

unique_ptr<IMatrix> AbstractVector::toRowMatrix(shared_ptr<IVector> vector, bool liveView) {
    if (liveView) {
        return make_unique<MatrixVectorView>(vector, true);
    } else {
        return make_unique<MatrixVectorView>(vector->clone(), true);
    }
}

unique_ptr<IMatrix> AbstractVector::toColumnMatrix(shared_ptr<IVector> vector, bool liveView) {
    if (liveView) {
        return make_unique<MatrixVectorView>(vector, false);
    } else {
        return make_unique<MatrixVectorView>(vector->clone(), false);
    }
}

std::string AbstractVector::toString(int precision) {
    ostringstream oss;

    oss << "[";
    for (int i = 0, n = getDimension(); i < n; i++) {
        oss << std::setprecision(precision) << get(i) << (i == n - 1 ? "" : " ");
    }
    oss << "]\n";

    return oss.str();
}

