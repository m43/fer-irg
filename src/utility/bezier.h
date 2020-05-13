//
// Created by m43 on 03. 05. 2020..
//

#ifndef FER_IRG_BEZIER_H
#define FER_IRG_BEZIER_H

#include "point.h"

// TODO fix imports and project structure
#include "../linalg/i_vector.h"
#include "../linalg/vector.h"
#include "../linalg/vector.cpp"
#include "../linalg/abstract_vector.h"
#include "../linalg/abstract_vector.cpp"
#include "../linalg/matrix.h"
#include "../linalg/matrix.cpp"
#include "../linalg/abstract_matrix.h"
#include "../linalg/abstract_matrix.cpp"
#include "../linalg/matrix_transpose_view.h"
#include "../linalg/matrix_transpose_view.cpp"
#include "../linalg/matrix_sub_matrix_view.h"
#include "../linalg/matrix_sub_matrix_view.cpp"
#include "../linalg/matrix_vector_view.h"
#include "../linalg/matrix_vector_view.cpp"
#include "../linalg/vector_matrix_view.h"
#include "../linalg/vector_matrix_view.cpp"

using namespace linalg;
using namespace std;

class BezierCurve {
public:

    void reset() {
        points_.clear();
        refreshed_ = false;
    }

    void addPoint(Point<double> p) {
        points_.push_back(p);
        refreshed_ = false;
    }

    const vector<Point<double>> &getPoints() const {
        return points_;
    }

    void updatePoint(int position, Point<double> p) {
        if (position < 0 || position >= (int) points_.size()) {
            throw invalid_argument("Invalid position given. No point at position `" + to_string(position) + "`.");
        }
        points_[position] = p;
        refreshed_ = false;
    }

    Point<double> interpolate(double t) {
        checkIfEnoughPoints();
        checkIfParameterValid(t);
        refresh();
        if (interpolationExists_) {
            int n = points_.size();
            Matrix T = Matrix(1, n);
            initializeRowOfT(0, n, T, t);
            auto result = T.nMultiply(*interpolationBR_);
            return Point<double>(result->get(0, 0), result->get(0, 1));
        } else {
            return Point<double>(-1, -1); // TODO
        }
    }

    Point<double> approximate(double t) {
        checkIfEnoughPoints();
        checkIfParameterValid(t);
        refresh();

        vector<Point<double>> castelj(points_);
        for (int i = 1, n = castelj.size(); i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                auto x = (1 - t) * castelj[j].getX() + t * castelj[j + 1].getX();
                auto y = (1 - t) * castelj[j].getY() + t * castelj[j + 1].getY();
                castelj[j] = Point<double>(x, y);
            }
        }
        return castelj[0];
    }

private:
    vector<Point<double>> points_;
    bool refreshed_;
    bool interpolationExists_;
    unique_ptr<IMatrix> interpolationBR_;

    void refresh() {
        if (!refreshed_) {
            refreshInterpolationStructures();
            refreshed_ = true;
        }
    }

    void refreshInterpolationStructures() {
        int n = points_.size();
        Matrix P = Matrix(n, 2);
        for (int i = 0; i < n; i++) {
            P.set(i, 0, points_[i].getX());
            P.set(i, 1, points_[i].getY());
        }
        Matrix T = Matrix(n, n);
        for (int i = 0; i < n; i++) {
            initializeRowOfT(i, n, T, i / (double) (n - 1));
        }

        try {
            auto invertedT = T.nInvert();
            interpolationBR_ = invertedT->nMultiply(P);
            interpolationExists_ = true;
        } catch (int) {
            interpolationExists_ = false;
        }
    }

    void initializeRowOfT(int row, int n, Matrix T, double t) {
        for (int column = n - 1; column >= 0; column--) {
            if (column == n - 1) {
                T.set(row, column, 1);
            } else if (column == n - 2) {
                T.set(row, column, t);
            } else {
                T.set(row, column, t * T.get(row, column + 1));
            }
        }
    }

    void checkIfParameterValid(double t) {
        if (t > 1 || t < 0) {
            throw invalid_argument("Parameter t must be in range [0,1].");
        }
    }

    void checkIfEnoughPoints() {
        if (points_.size() < 2) {
            throw invalid_argument("Not enough points.");
        }
    }
};

#endif //FER_IRG_BEZIER_H
