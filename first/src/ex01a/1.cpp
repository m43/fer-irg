//
// Created by m34 on 14. 03. 2020..
//

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utilities.h" // TODO how to fix this ".." part in the path?

using namespace std;
using namespace glm;

int main(void) {

    // calculations
    vec3 v1 = vec3(2, 3, -4) + vec3(-1, 4, -1);
    float s = dot(v1, vec3(-1, 4, -1));
    vec3 v2 = cross(v1, vec3(2, 2, 4));
    vec3 v3 = normalize(v2);
    vec3 v4 = -v2;

    dmat3 help_dmat3_1 = dmat3(1, 2, 4, 2, 1, 5, 3, 3, 1);
    dmat3 help_dmat3_2 = dmat3(vec3(-1, 5, -4), vec3(2, -2, -1), vec3(-3, 7, 3));

    dmat3 M1 = help_dmat3_1 + help_dmat3_2;
    dmat3 M2 = help_dmat3_1 * transpose(help_dmat3_2);
    dmat3 M3 = help_dmat3_1 * inverse(help_dmat3_2);

    dvec4 V = dvec4(1, 2, 3, 1) * dmat4(1, 0, 0, 2, 0, 2, 0, 3, 0, 0, 1, 3, 0, 0, 0, 1);

    // printing out the results
    cout << "v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")\n";
    cout << "s = " << s << "\n";
    cout << "v2 = " << to_string(v2) << "\n";
    cout << "v3 = " << to_string(v3) << "\n";
    cout << "v4 = " << to_string(v4) << "\n";

    cout << "IMatrix M1\n" << ex_utilities::pretty_print_matrix((const double *) value_ptr(M1), 3, 3) << "\n";
    cout << "IMatrix M2\n" << ex_utilities::pretty_print_matrix((const double *) value_ptr(M2), 3, 3) << "\n";
    cout << "IMatrix M3\n" << ex_utilities::pretty_print_matrix((const double *) value_ptr(M3), 3, 3) << "\n";

    cout << "V = " << to_string(V) << "\n";

    return 0;
}