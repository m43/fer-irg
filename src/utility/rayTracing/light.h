//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_LIGHT_H
#define FER_IRG_LIGHT_H

#include "../../linalg/i_vector.h"
#include "../../linalg/vector.h"
// big TODO use only `linalg` library, not glm
#include <glm/vec3.hpp>

using namespace glm;

namespace raytracing {

    class Light {
    public:
        Light(const Vector &position, const dvec3 &rgb) : position(position), rgb(rgb) {}

        Vector position;
        dvec3 rgb;
    };

}

#endif //FER_IRG_LIGHT_H
