//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SCENE_OBJECT_H
#define FER_IRG_SCENE_OBJECT_H

// TODO fix imports and project structure
#include "../../linalg/i_vector.h"
#include "../../linalg/vector.h"
// big TODO use only `linalg` library, not glm
#include <glm/vec3.hpp>

using namespace glm;

namespace raytracing {

    class Intersection;

    class SceneObject {
    public:
        // front
        dvec3 fambRGB;
        dvec3 fdifRGB;
        dvec3 frefRGB;
        double fn;
        double fkref;

        // back
        dvec3 bambRGB;
        dvec3 bdifRGB;
        dvec3 brefRGB;
        double bn;
        double bkref;

        virtual void updateIntersection(Intersection inters, IVector start, IVector d) = 0;

        virtual shared_ptr<IVector> getNormalInPoint(IVector point) = 0;
    };

    class Intersection {
        SceneObject object;
        double lambda;
        bool front;
        Vector point;
    };
}

#endif //FER_IRG_SCENE_OBJECT_H
