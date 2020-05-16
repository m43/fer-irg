//
// Created by m43 on 15. 05. 2020..
//

#ifndef FER_IRG_RAY_H
#define FER_IRG_RAY_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

using namespace glm;
using namespace std;

namespace raytracing {

    class Ray {

    public:
        Ray(const dvec3 &start, const dvec3 &direction) : start(start), d(normalize(direction)) {}

        shared_ptr<Ray> fromPoints(const dvec3 &from, const dvec3 &to) {
            return make_shared<Ray>(from, normalize(to - from));
        }

        dvec3 start;
        dvec3 d;  // d for direction
    };

}

#endif //FER_IRG_RAY_H
