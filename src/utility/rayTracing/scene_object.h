//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SCENE_OBJECT_H
#define FER_IRG_SCENE_OBJECT_H

#include "material.h"
#include "ray.h"
#include <glm/vec3.hpp>

using namespace glm;

namespace raytracing {

    class Intersection;

    class SceneObject {
    public:
        SceneObject(const Material &frontMat, const Material &backMat) : frontMat(frontMat), backMat(backMat) {}

        Material frontMat;
        Material backMat;

        virtual void updateIntersection(Intersection &intersection, const Ray &ray) = 0;

        virtual dvec3 getNormalInPoint(const dvec3 &point) = 0;
    };

    class Intersection {
    public:
        SceneObject *object;
        double lambda;
        bool front;
        dvec3 point;

        bool hasAnyIntersection() {
            return object != NULL;
        }
    };
}

#endif //FER_IRG_SCENE_OBJECT_H
