//
// Created by m43 on 21. 03. 2020..
//

#ifndef FIRST_MATRIX_H
#define FIRST_MATRIX_H


namespace linalg {
    class Matrix : public AbstractMatrix {

        Matrix(int, int);

        Matrix(int, int, double **, bool);

        int getRowsCount() override;

        int getColsCount() override;

        double get(int row, int col) override;

        IMatrix &set(int row, int column, double value) override;

        unique_ptr<IMatrix> clone() override;

        unique_ptr<IMatrix> newInstance(int row, int count) override;

        static unique_ptr<Vector> parseSimple(string str);

        virtual ~Matrix();

    };
}

#endif //FIRST_MATRIX_H
