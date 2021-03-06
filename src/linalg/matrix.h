//
// Created by m43 on 21. 03. 2020..
//

#ifndef FER_IRG_MATRIX_H
#define FER_IRG_MATRIX_H

#include "abstract_matrix.h"

namespace linalg {
    class Matrix : public AbstractMatrix {
    private:
        shared_ptr<vector<vector<double>>> elements_;
        // Note that there is as well the option to choose "vector<vector<shared_ptr<int>>>" Which would be faster I think.
        // TODO Would it be faster? I think that the fastest would be to have a sequence, but I'm not sure how to
        //      accomplish this using a vector of vectors

    public:

        ~Matrix() override = default;

        Matrix(int rows, int columns);

        explicit Matrix(const vector<vector<double>> &elements);

        explicit Matrix(shared_ptr<vector<vector<double>>> elements);

        [[nodiscard]] int getRowsCount() const override;

        [[nodiscard]] int getColsCount() const override;

        [[nodiscard]] double get(int row, int column) const override;

        IMatrix &set(int row, int column, double value) override;

        [[nodiscard]] unique_ptr<IMatrix> clone() const override;

        [[nodiscard]] unique_ptr<IMatrix> newInstance(int rows, int columns) const override;

        static unique_ptr<Matrix> parseSimple(const string &str);

        static shared_ptr<Matrix> identityMatrix(int dimension);
    };
}

#endif //FER_IRG_MATRIX_H
