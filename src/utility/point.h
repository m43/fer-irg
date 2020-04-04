//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_UI_POINT_H
#define FER_UI_POINT_H

class Point {
public:
    Point(int x, int y) : x_(x), y_(y) {}

    [[nodiscard]] int getX() const {
        return x_;
    }

    [[nodiscard]] int getY() const {
        return y_;
    }

private:
    int x_;
    int y_;
};

#endif //FER_UI_POINT_H
