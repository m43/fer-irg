//
// Created by m34 on 14. 03. 2020..
//

#include <iostream>
#include <string>
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

using namespace std;
using namespace linalg;

int main() {
    auto M = make_shared<Matrix>((size_t) 3, (size_t) 3);
    auto R = make_shared<Vector>((size_t) 3);

    for (int i = 0; i < 3; i++) {
        double a, b, c, d;
        cin >> a >> b >> c >> d;
        M->set(i, 0, a);
        M->set(i, 1, b);
        M->set(i, 2, c);
        R->set(i, d);
    }


    shared_ptr<IMatrix> solution = M->nInvert()->nMultiply(*AbstractVector::toColumnMatrix(R, true));
    cout << dynamic_pointer_cast<AbstractMatrix>(solution)->toString() << endl;
    return 0;
}

/*

in:
 1  1  1     6
-1 -2  1    -2
 2  1  3    13
out:
┌          ┐
│        1 │
│        2 │
│        3 │
└          ┘

 */