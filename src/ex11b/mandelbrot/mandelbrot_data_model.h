//
// Created by m43 on 16. 05. 2020..
//

#ifndef FER_IRG_MANDELBROT_DATA_MODEL_H
#define FER_IRG_MANDELBROT_DATA_MODEL_H

#include <vector>

using namespace std;

class ComplexPlaneDimensions {
public:
    ComplexPlaneDimensions(double vmin, double vmax, double umin, double umax) :
            vmin(vmin), vmax(vmax), umin(umin), umax(umax) {}

    [[nodiscard]] double getDeltaU() const;

    [[nodiscard]] double getDeltaV() const {
        return vmax - vmin;
    }

    double vmin;
    double vmax;
    double umin;
    double umax;
};

double ComplexPlaneDimensions::getDeltaU() const {
    return umax - umin;
}

class MandelbrotDataModel {
public:

    MandelbrotDataModel(int width, int height, int recursionDepth, ComplexPlaneDimensions cp,
                        double moveStepFactor = 0.1, double zoomScalingFactor = 2) :
            width_(width), height_(height), recursionDepth_(recursionDepth), initCp_(cp), cp_(cp),
            moveStepFactor_(moveStepFactor), zoomScalingFactor_(zoomScalingFactor) {}

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

    [[nodiscard]] int getRecursionDepth() const {
        return recursionDepth_;
    }

    void setRecursionDepth(int recursionDepth) {
        recursionDepth_ = recursionDepth;
    }

    void increaseRecursionDepth() {
        recursionDepth_++;
    }

    void decreaseRecursionDepth() {
        if (recursionDepth_ > 2) {
            recursionDepth_--;
        }
    }

    ComplexPlaneDimensions getComplexPlaneDimensions() {
        return cp_;
    }

    void pushComplexPlane(ComplexPlaneDimensions newComplexPlane) {
        cpStack_.push_back(cp_);
        cp_ = newComplexPlane;
    }

    void popComplexPlane() {
        if (!cpStack_.empty()) {
            cp_ = cpStack_.back();
            cpStack_.pop_back();
        }
    }

    void resetComplexPlane() {
        if (!cpStack_.empty()) {
            cp_ = initCp_;
            cpStack_.clear();
        }
    }

    void setComplexPlaneDimensions(const ComplexPlaneDimensions &cp) {
        cp_ = cp;
    }

    double getMoveStep() const {
        return moveStepFactor_;
    }

    void setMoveStep(double moveStep) {
        moveStepFactor_ = moveStep;
    }

    double getZoomScaling() const {
        return zoomScalingFactor_;
    }

    void setZoomScaling(double zoomScaling) {
        zoomScalingFactor_ = zoomScaling;
    }

    void moveRight() {
        double du = cp_.getDeltaU();
        cp_.umin += moveStepFactor_ * du;
        cp_.umax += moveStepFactor_ * du;
    }

    void moveLeft() {
        double du = cp_.getDeltaU();
        cp_.umin -= moveStepFactor_ * du;
        cp_.umax -= moveStepFactor_ * du;
    }

    void moveUp() {
        double dv = cp_.getDeltaV();
        cp_.vmin += moveStepFactor_ * dv;
        cp_.vmax += moveStepFactor_ * dv;
    }

    void moveDown() {
        double dv = cp_.getDeltaV();
        cp_.vmin -= moveStepFactor_ * dv;
        cp_.vmax -= moveStepFactor_ * dv;
    }

    void mousePress(int x, int y) {
        double du = cp_.getDeltaU();
        double dv = cp_.getDeltaV();

        double u = du * (double) x / width_ + cp_.umin;
        double v = dv * (double) (height_ - y) / height_ + cp_.vmin;

        ComplexPlaneDimensions newCp(
                v - dv / zoomScalingFactor_ / 2,
                v + dv / zoomScalingFactor_ / 2,
                u - du / zoomScalingFactor_ / 2,
                u + du / zoomScalingFactor_ / 2
        );
        pushComplexPlane(newCp);
    }

    [[nodiscard]] int getAlgorithm() const {
        return algorithm_;
    }

    void setAlgorithm(int algorithm) {
        algorithm_ = algorithm;
    }

    void pickPalette(int paletteNumber) {
        paletteNumber_ = paletteNumber;
    }

    [[nodiscard]] int getPalette() const {
        return paletteNumber_;
    }

private:
    int width_;
    int height_;

    int algorithm_ = 1;
    int paletteNumber_ = 3;
    int recursionDepth_;

    ComplexPlaneDimensions initCp_;
    ComplexPlaneDimensions cp_;
    vector<ComplexPlaneDimensions> cpStack_;
    double moveStepFactor_;
    double zoomScalingFactor_;
};

#endif //FER_IRG_MANDELBROT_DATA_MODEL_H
