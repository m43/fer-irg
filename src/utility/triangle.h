//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_TRIANGLE_H
#define FER_IRG_TRIANGLE_H

#include "point.h"
#include "color.h"
#include "edge.h"

template<class T>
class Triangle {
public:
    Triangle(const Point<T> &a, const Point<T> &b, const Point<T> &c, const Color &color) : a_(a), b_(b), c_(c),
                                                                                            color_(color) {}

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

    bool isAntiClockwise() {
        auto e = Edge<T>(a_, b_);
        return (e.getA() * c_.getX() + e.getB() * c_.getY() + e.getC()) > 0;
    }

private:
    Point<T> a_;
    Point<T> b_;
    Point<T> c_;
    Color color_;
};


#endif //FER_IRG_TRIANGLE_H
