//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_LIGHT_H
#define FER_IRG_LIGHT_H

#include <glm/vec3.hpp>

using namespace glm;

namespace raytracing {

    class Light {
    public:
        Light(const dvec3 &position, const dvec3 &rgb) : position(position), rgb(rgb) {}

        dvec3 position;
        dvec3 rgb;
    };

}

#endif //FER_IRG_LIGHT_H
