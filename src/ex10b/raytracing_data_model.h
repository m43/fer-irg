//
// Created by m43 on 15. 05. 2020..
//

#ifndef FER_IRG_RAYTRACING_DATA_MODEL_H
#define FER_IRG_RAYTRACING_DATA_MODEL_H

#include "../utility/rayTracing/scene.h"

using namespace std;
using namespace raytracing;

class RayTracingDataModel {
public:

    RayTracingDataModel(int width, int height, int recursionDepth, double delta) :
            width_(width), height_(height), recursionDepth_(recursionDepth), delta_(delta) {}

    [[nodiscard]] int getWidth() const {
        return width_;
    }

    void setWidth(int width) {
        width_ = width;
    }

    [[nodiscard]] int getHeight() const {
        return height_;
    }

    void setHeight(int height) {
        height_ = height;
    }

    void setScene(const shared_ptr<Scene> &scene_ptr) {
        scene_ = scene_ptr;
    }

    const shared_ptr<Scene> &getScene() {
        return scene_;
    }

    int getRecursionDepth() {
        return recursionDepth_;
    }

    void setRecursionDepth(int recursionDepth) {
        recursionDepth_ = recursionDepth;
    }

    void increaseRecursionDepth() {
        recursionDepth_++;
    }

    void decreaseRecursionDepth() {
        if (recursionDepth_ > 0) {
            recursionDepth_--;
        }
    }

    double getDelta() {
        return delta_;
    }

private:
    int width_;
    int height_;
    int recursionDepth_;
    shared_ptr<Scene> scene_;
    double delta_;
};

#endif //FER_IRG_RAYTRACING_DATA_MODEL_H
