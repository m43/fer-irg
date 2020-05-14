//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SCENE_H
#define FER_IRG_SCENE_H

#include "light.h"
#include "patch.h"
#include "scene_object.h"
#include "sphere.h"

#include "../../linalg/matrix_vector_view.cpp"
#include "../../linalg/vector.cpp"
#include "../../linalg/abstract_vector.cpp"
#include "../../linalg/matrix.cpp"
#include "../../linalg/abstract_matrix.cpp"
#include "../../linalg/matrix_transpose_view.cpp"
#include "../../linalg/matrix_sub_matrix_view.cpp"
#include "../../linalg/vector_matrix_view.cpp"

namespace raytracing {

    class Scene {
    public:
        Vector eye; // TODO how to use IVector here instead of Vector?
        Vector view;
        Vector viewUp;
        double h;
        double xAngle;
        double yAngle;
        dvec3 gaIntensity = dvec3(0, 0, 0);
        vector<Light> sources;
        vector<SceneObject> objects;

        Vector xAxis;
        Vector yAxis;
        double l;
        double r;
        double t;
        double b;

        void loadScene(string path) {
            // TODO
        }

    private:
        void computeKS() {
            // compute xAxis yAxis l r t b
            // TODO
        }
    };

}
#endif //FER_IRG_SCENE_H
