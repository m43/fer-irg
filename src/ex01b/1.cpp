//
// Created by m43 on 03. 04. 2020..
//

#include <iostream>
#include <memory>

// TODO how to properly deal with this includes? I see two problems:
//          1. the starting ".." - depends on the path
//          2. too many includes needed, there should be a more neat way
//      I think a good solution has to do with moving the linalg to a library

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

/*
 * Neka su zadane tri vrha trokuta u 3D: A = (1, 0, 0), B = (5, 0, 0) te C = (3, 8, 0), i neka je zadana to£ka
 * T = (3, 4, 0). Treba odrediti baricentri£ne koordinate te to£ke s obzirom na zadane vrhove trokuta.
 */

using namespace std;
using namespace linalg;

int main() {
    // calculations
    unique_ptr<Vector> v1 = Vector::parseSimple("2 3 -4");
    v1->add(*Vector::parseSimple("-1 4 -1"));
    double s = v1->dotProduct(*Vector::parseSimple("-1 4 -1"));
    shared_ptr<IVector> v2 = v1->nCrossProduct3D(*Vector::parseSimple("2 2 4"));
    shared_ptr<IVector> v3 = v2->nNormalize();
    shared_ptr<IVector> v4 = v2->clone();
    v4->sub(*v2).sub(*v2);

    unique_ptr<Matrix> help_dmat3_1 = Matrix::parseSimple("1 2 3 | 2 1 3 | 4 5 1");
    unique_ptr<Matrix> help_dmat3_2 = Matrix::parseSimple("-1 2 -3 | 5 -2 7 | -4 -1 3");

    shared_ptr<IMatrix> M1 = help_dmat3_1->nAdd(*help_dmat3_2);
    shared_ptr<IMatrix> M2 = help_dmat3_1->nMultiply(*help_dmat3_2->nTranspose());
    shared_ptr<IMatrix> M3 = help_dmat3_1->nMultiply(*help_dmat3_2->nInvert());

    shared_ptr<IMatrix> V_matrix = Vector::toRowMatrix(Vector::parseSimple("1 2 3 1"), true)->nMultiply(
            *Matrix::parseSimple("1 0 0 0 | 0 2 0 0 | 0 0 1 0 | 2 3 3 1"));
    shared_ptr<IVector> V = Matrix::toVector(V_matrix, true);

    // printing out the results
    cout << "v1 = (" << v1->get(0) << ", " << v1->get(1) << ", " << v1->get(2) << ")\n";
    cout << "s = " << s << "\n";

    // TODO Is there any normal way of calling AbstractVector::toString, not this casting? How should I have modeled
    //      the IVector and AbstractVector classes to allow this? Some ideas:
    //          1. move the functions to IVector -- but then i would break one of the rules of good modeling
    //          2. leave these functions from the IVector interface definition
    //          3. create static functions that work with objects, like toString(IVector)
    cout << "v2 = " << (dynamic_pointer_cast<AbstractVector>(v2))->toString();
    cout << "v3 = " << (dynamic_pointer_cast<AbstractVector>(v3))->toString();
    cout << "v4 = " << (dynamic_pointer_cast<AbstractVector>(v4))->toString() << "\n";

    cout << "IMatrix M1\n" << (dynamic_pointer_cast<AbstractMatrix>(M1))->toString() << "\n";
    cout << "IMatrix M2\n" << (dynamic_pointer_cast<AbstractMatrix>(M2))->toString() << "\n";
    cout << "IMatrix M3\n" << (dynamic_pointer_cast<AbstractMatrix>(M3))->toString() << "\n";

    cout << "V = " << (dynamic_pointer_cast<AbstractVector>(V))->toString() << "\n";
    return 0;
}

