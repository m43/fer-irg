//
// Created by m43 on 04. 04. 2020..
//

#ifndef FIRST_LINE_DATA_MODEL_H
#define FIRST_LINE_DATA_MODEL_H

#include <vector>
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/line.h"

class LineDataModel {
public:
    LineDataModel(const Color &foregroundColor, const Color &backgroundColor, int width, int height) : foregroundColor_(
            foregroundColor), backgroundColor_(backgroundColor), width_(width), height_(height) {}

    [[nodiscard]] const std::vector<Line> &getLines() const {
        return lines_;
    }

    void setLines(const std::vector<Line> &lines) {
        lines_ = lines;
    }

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

    [[nodiscard]] bool isFirstClickMade() const {
        return firstClickMade_;
    }

    [[nodiscard]] const Point &getFirstClick() const {
        return firstClick_;
    }

    [[nodiscard]] const Point &getLastMousePosition() const {
        return lastMousePosition_;
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


    bool mousePress(int x, int y) {
        if (!firstClickMade_) {
            firstClickMade_ = true;
            firstClick_ = Point(x, y);
        } else {
            firstClickMade_ = false;
            lines_.emplace_back(firstClick_, Point(x, y), foregroundColor_);
        }
        return true;
    }

    bool mouseMoved(int x, int y) {
        lastMousePosition_ = Point(x, y);
        return firstClickMade_;
    }

    [[nodiscard]] bool isControled() const {
        return control_;
    }

    void setControl(bool control) {
        control_ = control;
    }

    [[nodiscard]] bool isSlicing() const {
        return slicing_;
    }

    void setSlicing(bool slicing) {
        slicing_ = slicing;
    }

private:
    std::vector<Line> lines_ = std::vector<Line>();
    Color foregroundColor_;
    Color backgroundColor_;
    bool firstClickMade_ = false;
    Point firstClick_ = Point(0, 0);
    Point lastMousePosition_ = Point(0, 0);
    int width_;
    int height_;
    bool control_;
    bool slicing_;
};

#endif //FIRST_LINE_DATA_MODEL_H
