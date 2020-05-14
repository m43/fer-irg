//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SPHERE_H
#define FER_IRG_SPHERE_H

#include "scene_object.h"
#include "../../linalg/i_vector.h"
#include "../../linalg/vector.h"

namespace raytracing {

    class Sphere : SceneObject {
    public:
        Vector center;
        double radius;

        void updateIntersection(Intersection inters, IVector start, IVector d) override {
            // TODO
        }

        shared_ptr<IVector> getNormalInPoint(IVector point) override {
            // TODO
            return shared_ptr<IVector>();
        }
    };
}

#endif //FER_IRG_SPHERE_H
