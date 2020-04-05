//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_TRIANGLE_H
#define FER_UI_TRIANGLE_H

#include "point.h"
#include "color.h"

template<class T>
class Triangle {
public:
    Triangle(const Point<T> &a, const Point<T> &b, const Point<T> &c, const Color &color) : a_(a), b_(b), c_(c), color_(color) {}

    [[nodiscard]] const Point<T> &getA() const {
        return a_;
    }

    [[nodiscard]] const Point<T> &getB() const {
        return b_;
    }

    [[nodiscard]] const Point<T> &getC() const {
        return c_;
    }

    [[nodiscard]] const Color &getColor() const {
        return color_;
    }

private:
    Point<T> a_;
    Point<T> b_;
    Point<T> c_;
    Color color_;
};


#endif //FER_UI_TRIANGLE_H
