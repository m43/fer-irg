//
// Created by m43 on 03. 04. 2020..
//

#include <iostream>
#include <memory>

#include "i_vector.h"
#include "vector.h"
#include "vector.cpp"
#include "abstract_vector.cpp"

/*
 * Neka su zadane tri vrha trokuta u 3D: A = (1, 0, 0), B = (5, 0, 0) te C = (3, 8, 0), i neka je zadana to£ka
 * T = (3, 4, 0). Treba odrediti baricentri£ne koordinate te to£ke s obzirom na zadane vrhove trokuta.
 */

using namespace std;
using namespace linalg;

int main() {
    unique_ptr<IVector> a = Vector::parseSimple("1 0 0");
    unique_ptr<IVector> b = Vector::parseSimple("5 0 0");
    unique_ptr<IVector> c = Vector::parseSimple("3 8 0");

    unique_ptr<IVector> t = Vector::parseSimple("3 4 0");

    double pov = (*b).nSub(*a)->nCrossProduct3D(*c->nSub(*a))->norm() / 2.0;
    double povA = (*b).nSub(*t)->nCrossProduct3D(*c->nSub(*t))->norm() / 2.0;
    double povB = (*a).nSub(*t)->nCrossProduct3D(*c->nSub(*t))->norm() / 2.0;
    double povC = (*a).nSub(*t)->nCrossProduct3D(*b->nSub(*t))->norm() / 2.0;

    double t1 = povA / pov;
    double t2 = povB / pov;
    double t3 = povC / pov;

    cout << " Baricentricne koordinate su : (" << t1 << " ," << t2 << " ," << t3 << "). " << endl; // out: (0.25,0.25,0.5)
    return 0;
}

