//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_MATERIAL_H
#define FER_IRG_MATERIAL_H

#include <glm/vec3.hpp>

using namespace glm;

namespace raytracing {

    class Material {
    public:

        Material(double ar, double ag, double ab, double dr, double dg, double db, double rr, double rg, double rb,
                 double n, double kref) :
                Material(dvec3(ar, ag, ab), dvec3(dr, dg, db), dvec3(rr, rg, rb), n, kref) {}

        Material(const dvec3 &ambRgb, const dvec3 &difRgb, const dvec3 &refRgb, double n, double kref) :
                ambRGB(ambRgb), difRGB(difRgb), refRGB(refRgb), n(n), kref(kref) {}

        dvec3 ambRGB;
        dvec3 difRGB;
        dvec3 refRGB;
        double n;
        double kref;
    };

}

#endif //FER_IRG_MATERIAL_H
