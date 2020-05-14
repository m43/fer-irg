//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_PATCH_H
#define FER_IRG_PATCH_H

#include "scene_object.h"
#include "../../linalg/i_vector.h"
#include "../../linalg/vector.h"

namespace raytracing {

    class Patch : SceneObject {
    public:
        Vector center;
        Vector v1;
        Vector v2;
        Vector normal;
        double w;
        double h;

        void updateIntersection(Intersection inters, IVector start, IVector d) override {
            // TODO
        }

        shared_ptr<IVector> getNormalInPoint(IVector point) override {
            // TODO
            return shared_ptr<IVector>();
        }
    };
}
#endif //FER_IRG_PATCH_H
