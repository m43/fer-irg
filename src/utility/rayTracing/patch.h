//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_PATCH_H
#define FER_IRG_PATCH_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "../utilities.h"

#include "scene_object.h"

using namespace std;
using namespace glm;

namespace raytracing {

    class Patch : public SceneObject {
    public:
        Patch(const Material &frontMat, const Material &backMat, const dvec3 &center, const dvec3 &v1, const dvec3 &v2,
              double w, double h) : SceneObject(frontMat, backMat), center(center), v1(normalize(v1)),
                                    v2(normalize(v2)), w(w), h(h) { normal = normalize(cross(v1, v2)); }

        dvec3 center;
        dvec3 v1;
        dvec3 v2;
        dvec3 normal;
        double w;
        double h;

        void updateIntersection(Intersection &intersection, const Ray &ray) override {
            dvec3 system_solution = ex_utilities::solve_equation_system(v1, v2, -ray.d, ray.start - center);
            double mi_1 = system_solution.x;
            double mi_2 = system_solution.y;
            double lambda = system_solution.z;

            double D = -dot(normal, center);
            double lambda2 = -1;
            double nDotD = dot(normal, ray.d);
            if (nDotD > 0) {
                lambda2 = -(D + dot(normal, ray.start)) / dot(normal, ray.d);
            } // TODO remove
            if (lambda2 != -1 && lambda - lambda2 > 0.0001) {
                throw invalid_argument("Ne more");
            }

            if (lambda > 0 && abs(mi_1) <= w / 2 && abs(mi_2) <= h / 2) {
                if (!intersection.hasAnyIntersection() || intersection.lambda > lambda) {
                    intersection.object = this;
                    intersection.lambda = lambda;
                    intersection.front = dot(normal, ray.d) < 0;
                    intersection.point = ray.start + lambda * ray.d;
                }
            }

        }

        dvec3 getNormalInPoint(const dvec3 &) override {
            return normal;
        }
    };
}
#endif //FER_IRG_PATCH_H
