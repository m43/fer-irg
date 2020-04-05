//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_POINT_H
#define FER_UI_POINT_H

template<class T>
class Point {
public:
    Point(T x, T y) : x_(x), y_(y) {}

    [[nodiscard]] T getX() const {
        return x_;
    }

    [[nodiscard]] T getY() const {
        return y_;
    }

private:
    T x_;
    T y_;
};

#endif //FER_UI_POINT_H
