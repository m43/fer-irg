//
// Created by m34 on 14. 03. 2020..
//

#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "../utility/utilities.h"

using namespace std;
using namespace glm;
using namespace ex_utilities;

int main(void) {

    dmat3 M = dmat3();
    dvec3 R = dvec3();

    int i = 0;
    for (char c: {'A', 'B', 'C', 'T'}) {
        cout << "Unesi podatke o tocki " << c << " (x, y i z koordinate, odvojene razmakom, pa udari enter)" << endl;
        for (int j = 0; j < 3; j++) {
            if (i != 3) {
                cin >> M[i][j];
            } else {
                cin >> R[j];
            }
        }
        i++;
        cout << "Hvala." << endl << endl;
    }

    dvec3 solution = solve_equation_system(M, R);
    cout << "Baricentricne koordinate tocke T s obzirom na zadani trokut su: " << endl << to_string(solution) << endl;

    return 0;
}

/*

in:
1 1 0
6 11 2
11 1 0
6 6 1
out:
dvec3(0.25, 0.5, 0.25)

 in:
1 0 0
5 0 0
3 8 0
3 4 0
 out:
dvec3(0.25, 0.25, 0.5)
 */