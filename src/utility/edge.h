//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_EDGE_H
#define FER_IRG_EDGE_H

#include "line.h"

template<class T>
class Edge {
public:
    Edge(Line<T> line) : Edge(line.getStart(), line.getEnd()) {}

    Edge(Point<T> start, Point<T> end) : start_(start), end_(end) {
        a_ = -end.getY() + start.getY();
        b_ = end.getX() - start.getX();
        c_ = start.getX() * end.getY() - start.getY() * end.getX();
    }

    [[nodiscard]] T getA() const {
        return a_;
    }

    [[nodiscard]]  T getB() const {
        return b_;
    }

    [[nodiscard]] T getC() const {
        return c_;
    }

    [[nodiscard]] const Point<T> &getStart() const {
        return start_;
    }

    [[nodiscard]] const Point<T> &getEnd() const {
        return end_;
    }

    bool pointsUp() {
        return end_.getY() > start_.getY();
    }

private:
    Point<T> start_;
    Point<T> end_;
    T a_;
    T b_;
    T c_;
};

#endif //FER_IRG_EDGE_H
