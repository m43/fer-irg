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

int main(void) {
    unique_ptr<IVector> a = make_unique<Vector>(3);
    unique_ptr<IVector> b = make_unique<Vector>(3);
    unique_ptr<IVector> c = make_unique<Vector>(3);
    unique_ptr<IVector> t = make_unique<Vector>(3);

    int i = 0;
    for (char ch: {'A', 'B', 'C', 'T'}) {
        cout << "Unesi podatke o točki " << ch << " (x, y i z koordinate, odvojene razmakom, pa udari enter)" << endl;
        for (int j = 0; j < 3; j++) {
            double current;
            cin >> current;
            if (i == 0) {
                a->set(j, current);
            } else if (i == 1) {
                b->set(j, current);
            } else if (i == 2) {
                c->set(j, current);
            } else {
                t->set(j, current);
            }
        }
        i++;
        cout << "Hvala." << endl << endl;
    }


    double pov = (*b).nSub(*a)->nCrossProduct3D(*c->nSub(*a))->norm() / 2.0;
    double povA = (*b).nSub(*t)->nCrossProduct3D(*c->nSub(*t))->norm() / 2.0;
    double povB = (*a).nSub(*t)->nCrossProduct3D(*c->nSub(*t))->norm() / 2.0;
    double povC = (*a).nSub(*t)->nCrossProduct3D(*b->nSub(*t))->norm() / 2.0;

    double t1 = povA / pov;
    double t2 = povB / pov;
    double t3 = povC / pov;

    cout << " Baricentricne koordinate su : (" << t1 << " ," << t2 << " ," << t3 << "). "
         << endl; // out: (0.25,0.25,0.5)

    return 0;
}

/*

in:
1 1 0
6 11 2
11 1 0
6 6 1
out:
(0.25 ,0.5 ,0.25)

 in:
1 0 0
5 0 0
3 8 0
3 4 0
 out:
(0.25 ,0.25 ,0.5)
 */