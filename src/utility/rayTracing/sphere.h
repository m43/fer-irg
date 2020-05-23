//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SPHERE_H
#define FER_IRG_SPHERE_H

#include "scene_object.h"
#include <glm/geometric.hpp>

using namespace std;

namespace raytracing {

    class Sphere : public SceneObject {
    public:

        Sphere(const Material &material, const dvec3 &center, double radius) :
                SceneObject(material, material), center(center), radius(radius) {}

        dvec3 center;
        double radius;

        void updateIntersection(Intersection &intersection, const Ray &ray) override {
            if (length(ray.d) - 1. > 0.00001) {
                throw invalid_argument("d is not normalized. norm: " + to_string(length(ray.d)));
                // TODO remove debug
            }

            dvec3 centerToStart = ray.origin - center;
            // double a = 1;
            double b = 2 * dot(ray.d, centerToStart);
            double c = dot(centerToStart, centerToStart) - radius * radius;

            double determinant = b * b - 4 * c;
            if (determinant < 0) {
                return;
            }

            double lambda1 = (-b - sqrt(determinant)) / 2;
            // double lambda2 = (-b + sqrt(determinant)) / 2;

            if (lambda1 > 0) {
                if (!intersection.hasAnyIntersection() || intersection.lambda > lambda1) {
                    intersection.object = this;
                    intersection.front = true;
                    intersection.lambda = lambda1;
                    intersection.point = ray.d * lambda1 + ray.origin;
                }
            }
        }

        dvec3 getNormalInPoint(const dvec3 &point) override {
            return normalize(point - center);
        }
    };
}

#endif //FER_IRG_SPHERE_H
