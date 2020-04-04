//
// Created by m43 on 04. 04. 2020..
//

#ifndef FIRST_LINE_H
#define FIRST_LINE_H

#include "point.h"
#include "color.h"

class Line {
public:
    Line(const Point &start, const Point &end, const Color &color) : start_(start), end_(end), color_(color) {}

    [[nodiscard]] const Point &getStart() const {
        return start_;
    }

    [[nodiscard]] const Point &getEnd() const {
        return end_;
    }

    [[nodiscard]] const Color &getColor() const {
        return color_;
    }

private:
    Point start_;
    Point end_;
    Color color_;
};


#endif //FIRST_LINE_H
