//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_3D_OBJECT_DATA_MODEL_H
#define FER_UI_3D_OBJECT_DATA_MODEL_H

#include <utility>
#include <vector>
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/line.h"
#include "../utility/object_model.h"

class DataModel {
public:
    DataModel(const Color &foregroundColor, const Color &backgroundColor, int width,
              int height) : foregroundColor_(
            foregroundColor), backgroundColor_(backgroundColor), width_(width), height_(height) {}


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

    bool mousePress(int, int) {
        return true;
    }

    bool mouseMoved(int x, int y) {
        lastMousePosition_ = Point(x, y);
        return true;
    }

    [[nodiscard]] double getRotateX() const {
        return rotateX_;
    }

    void rotateX(int delta) {
        rotateX_ += delta;
    }

    [[nodiscard]] double getRotateY() const {
        return rotateY_;
    }

    void rotateY(int delta) {
        rotateY_ += delta;
    }

    const Point<int> &getLastMousePosition() const {
        return lastMousePosition_;
    }

    void setObjectModel(shared_ptr<ObjectModel> om) {
        om_ = move(om);
    }

    shared_ptr<ObjectModel> getObjectModel() {
        return om_;
    }

private:
    Color foregroundColor_;
    Color backgroundColor_;
    int width_;
    int height_;
    Point<int> lastMousePosition_ = Point(0, 0);
    double rotateX_ = 0;
    double rotateY_ = 0;

    shared_ptr<ObjectModel> om_;
};

#endif //FER_UI_3D_OBJECT_DATA_MODEL_H
