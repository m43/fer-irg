//
// Created by m34 on 14. 03. 2020..
//

#include <iostream>
#include <glm/mat3x3.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../utility/utilities.h"

using namespace std;
using namespace glm;
using namespace ex_utilities;

int main(void) {
    dmat3 M = dmat3();
    dvec3 R = dvec3();

    for (int i = 0; i < 3; i++) {
        double a, b, c;
        cin >> a >> b >> c >> R[i];
        M[i] = {a, b, c};
    }
    M = transpose(M); // The transposing is to put loaded columns and orders in correct order

    dvec3 solution = solve_equation_system(M, R);
    cout << to_string(solution) << endl;

    return 0;
}

/*

in:
 1  1  1     6
-1 -2  1    -2
 2  1  3    13
out:
dvec3(1, 2, 3)

 */