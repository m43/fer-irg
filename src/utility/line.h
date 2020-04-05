//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_LINE_H
#define FER_UI_LINE_H

#include "point.h"
#include "color.h"

template<class T>
class Line {
public:
    Line(const Point<T> &start, const Point<T> &end, const Color &color) : start_(start), end_(end), color_(color) {}

    [[nodiscard]] const Point<T> &getStart() const {
        return start_;
    }

    [[nodiscard]] const Point<T> &getEnd() const {
        return end_;
    }

    [[nodiscard]] const Color &getColor() const {
        return color_;
    }

private:
    Point<T> start_;
    Point<T> end_;
    Color color_;
};

#endif //FER_UI_LINE_H
