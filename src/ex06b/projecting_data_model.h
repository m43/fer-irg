//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_PROJECTING_DATA_MODEL_H
#define FER_IRG_PROJECTING_DATA_MODEL_H

#include <utility>
#include <vector>
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/line.h"
#include "../utility/object_model.h"

class DataModel {
public:
    DataModel(const Color &foregroundColor,
              const Color &backgroundColor,
              int width, int height, double initialAngle, double increment) :
            foregroundColor_(foregroundColor), backgroundColor_(backgroundColor), width_(width), height_(height),
            initialAngle_(initialAngle), increment_(increment) {}


    [[nodiscard]] const Color &getForegroundColor() const {
        return foregroundColor_;
    }

    void setForegroundColor(const Color &foregroundColor) {
        foregroundColor_ = foregroundColor;
    }

    [[nodiscard]] const Color &getBackgroundColor() const {
        return backgroundColor_;
    }

    void setBackgroundColor(const Color &backgroundColor) {
        backgroundColor_ = backgroundColor;
    }

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

    void setObjectModel(shared_ptr<ObjectModel> om) {
        om_ = move(om);
    }

    shared_ptr<ObjectModel> getObjectModel() {
        return om_;
    }

    void incrementAngle() {
        angle_ += increment_;
    }

    void decrementAngle() {
        angle_ -= increment_;
    }

    double getAngle() {
        return angle_;
    }

    void resetAngle() {
        angle_ = initialAngle_;
    }

    void switchFill() {
        fill_ = !fill_;
    }

    void setFill(bool fill) {
        fill_ = fill;
    }

    bool shouldFill() {
        return fill_;
    }

    void setAlgorithmNumber(int alg) {
        algorithm_ = alg;
    }

    int getAlgorithmNumber() {
        return algorithm_;
    }

private:
    Color foregroundColor_;
    Color backgroundColor_;
    int width_;
    int height_;
    const double initialAngle_;
    double angle_;
    double increment_;
    bool fill_ = false;
    int algorithm_ = 1;
    shared_ptr<ObjectModel> om_;
};

#endif //FER_IRG_PROJECTING_DATA_MODEL_H
