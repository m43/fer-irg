//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_TRIANGLE_DATA_MODEL_H
#define FER_IRG_TRIANGLE_DATA_MODEL_H

#include <vector>
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/triangle.h"

enum TriangleDataModelState {
    CLEAR, FIRST_CLICK, SECOND_CLICK
};

class TriangleDataModel {
public:
    explicit TriangleDataModel(std::vector<Color> palette, Color foregroundColor, Color backgroundColor, int height,
                               int width)
            : foregroundColor_(foregroundColor), backgroundColor_(backgroundColor), palette_(std::move(palette)),
              width_(width),
              height_(height) {};

    [[nodiscard]] TriangleDataModelState getState() const {
        return state_;
    }

    [[nodiscard]] const std::vector<Triangle<int>> &getTriangles() const {
        return triangles_;
    }

    void setTriangles(const std::vector<Triangle<int>> &triangles) {
        triangles_ = triangles;
    }

    [[nodiscard]] const Point<int> &getFirstClick() const {
        return firstClick_;
    }

    void setFirstClick(const Point<int> &firstClick) {
        firstClick_ = firstClick;
    }

    [[nodiscard]] const Point<int> &getSecondClick() const {
        return secondClick_;
    }

    void setSecondClick(const Point<int> &secondClick) {
        secondClick_ = secondClick;
    }

    [[nodiscard]] const Point<int> &getLastMousePosition() const {
        return lastMousePosition_;
    }

    void setLastMousePosition(const Point<int> &lastMousePosition) {
        lastMousePosition_ = lastMousePosition;
    }

    [[nodiscard]] const Color &getCurrentColor() const {
        return palette_[currentColorIndex_];
    }

    void setCurrentColor(const Color &currentColor) {
        palette_[currentColorIndex_] = currentColor;
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
        if (state_ == SECOND_CLICK) {
            state_ = CLEAR;
            // TODO is this triangle created on the stack?
            triangles_.emplace_back(firstClick_, secondClick_, Point(x, y), palette_[currentColorIndex_]);
            return true;
        }

        if (state_ == CLEAR) {
            state_ = FIRST_CLICK;
            firstClick_ = Point(x, y);
        } else {
            state_ = SECOND_CLICK;
            secondClick_ = Point(x, y);
        }
        return false;
    }

    bool mouseMoved(int x, int y) {
        lastMousePosition_ = Point(x, y);
        return state_ != CLEAR;
    }

    bool nextColor() {
        currentColorIndex_ = (currentColorIndex_ + 1) % palette_.size();
        return true;
    }

    bool previousColor() {
        currentColorIndex_ = (currentColorIndex_ + palette_.size() - 1) % palette_.size();
        return true;
    }

    [[nodiscard]] const std::vector<Color> &getPalette() const {
        return palette_;
    }

    void setPalette(const std::vector<Color> &palette) {
        palette_ = palette;
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

private:
    TriangleDataModelState state_ = CLEAR;
    std::vector<Triangle<int>> triangles_ = std::vector<Triangle<int>>();
    Color foregroundColor_;
    Color backgroundColor_;
    std::vector<Color> palette_ = std::vector<Color>();
    Point<int> firstClick_ = Point(0, 0);
    Point<int> secondClick_ = Point(0, 0);
    Point<int> lastMousePosition_ = Point(0, 0);
    unsigned long currentColorIndex_ = 0;
    int width_;
    int height_;
};

#endif //FER_IRG_TRIANGLE_DATA_MODEL_H
