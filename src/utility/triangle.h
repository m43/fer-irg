//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_TRIANGLE_H
#define FER_UI_TRIANGLE_H

#include "point.h"
#include "color.h"

class Triangle {
public:
    Triangle(const Point &a, const Point &b, const Point &c, const Color &color) : a_(a), b_(b), c_(c), color_(color) {}

    [[nodiscard]] const Point &getA() const {
        return a_;
    }

    [[nodiscard]] const Point &getB() const {
        return b_;
    }

    [[nodiscard]] const Point &getC() const {
        return c_;
    }

    [[nodiscard]] const Color &getColor() const {
        return color_;
    }

private:
    Point a_;
    Point b_;
    Point c_;
    Color color_;
};


#endif //FER_UI_TRIANGLE_H
