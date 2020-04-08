//
// Created by m43 on 03. 04. 2020..
//

#include <iostream>
#include <memory>

// TODO fix imports and project structure
#include "i_matrix.h"
#include "matrix.h"
#include "matrix.cpp"
#include "vector.h"
#include "vector.cpp"
#include "abstract_vector.h"
#include "abstract_vector.cpp"
#include "abstract_matrix.h"
#include "abstract_matrix.cpp"
#include "matrix_sub_matrix_view.h"
#include "matrix_sub_matrix_view.cpp"
#include "matrix_transpose_view.h"
#include "matrix_transpose_view.cpp"
#include "vector_matrix_view.h"
#include "vector_matrix_view.cpp"
#include "matrix_vector_view.h"
#include "matrix_vector_view.cpp"


using namespace std;
using namespace linalg;

int main() {
    unique_ptr<Matrix> a = Matrix::parseSimple("3 5 | 2 10");
    unique_ptr<Matrix> r = Matrix::parseSimple("2 | 8");

    cout << a->toString() << endl;
    cout << r->toString() << endl;


    shared_ptr<IMatrix> ainv = a->nInvert();
    cout << "A det: " << a->determinant() << endl;
    cout << "A inv: " << endl << dynamic_pointer_cast<Matrix>(ainv)->toString() << endl;

    shared_ptr<IMatrix> v = a->nInvert()->nMultiply(*r);
    cout << "Rjesenje sustava je: " << endl << dynamic_pointer_cast<Matrix>(v)->toString() << endl;

    // out is this 2x1 matrix: [[-1.000], [ 1.000]]
    return 0;
}

