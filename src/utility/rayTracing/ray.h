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
        Ray(const dvec3 &origin, const dvec3 &direction) : origin(origin), d(normalize(direction)) {}

        shared_ptr<Ray> fromPoints(const dvec3 &from, const dvec3 &to) {
            return make_shared<Ray>(from, normalize(to - from));
        }

        dvec3 origin;
        dvec3 d;  // d for direction
    };

}

#endif //FER_IRG_RAY_H
