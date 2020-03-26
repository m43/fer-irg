//
// Created by m43 on 21. 03. 2020..
//

#ifndef FIRST_ABSTRACT_MATRIX_H
#define FIRST_ABSTRACT_MATRIX_H

namespace linalg {
    class AbstractMatrix : public IMatrix {
        // TODO to virtual or not to virtual

        unique_ptr<IMatrix> nTranspose(bool b) override;

        IMatrix &add(const IMatrix &other) override;

        unique_ptr<IMatrix> nAdd(const IMatrix &other) override;

        IMatrix &sub(const IMatrix &other) override;

        unique_ptr<IMatrix> nSub(const IMatrix &other) override;

        unique_ptr<IMatrix> nMultiply(const IMatrix &other) override;

        double determinant() override;

        unique_ptr<IMatrix> subMatrix(int a, int b, bool ae) override;

        unique_ptr<IMatrix> nInvert() override;

        double **toArray() override;

        string toString(int precision = 3);

        // TODO
        //  IVector toVector(bool ae) override;

        virtual ~AbstractMatrix();
    };
}

#endif //FIRST_ABSTRACT_MATRIX_H
