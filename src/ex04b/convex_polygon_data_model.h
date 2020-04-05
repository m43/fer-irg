//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_UI_CONVEX_POLYGON_DATA_MODEL_H
#define FER_UI_CONVEX_POLYGON_DATA_MODEL_H

#include <vector>
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/line.h"
#include "../utility/polygon.h"

using namespace std;

class ConvexPolygonDataModel {
public:
    ConvexPolygonDataModel(const Color &foregroundColor, const Color &backgroundColorWithoutConvexityCheck,
                           const Color &backgroundColorWithConvexityCheck, int width, int height)
            : foregroundColor_(foregroundColor),
              backgroundColorWithoutConvexityCheck_(backgroundColorWithoutConvexityCheck),
              backgroundColorWithConvexityCheck_(backgroundColorWithConvexityCheck), width_(width), height_(height) {}


    [[nodiscard]] const Color &getForegroundColor() const {
        return foregroundColor_;
    }

    void setForegroundColor(const Color &foregroundColor) {
        foregroundColor_ = foregroundColor;
    }

    [[nodiscard]] const Color &getBackgroundColor() const {
        return kFlag_ ? backgroundColorWithConvexityCheck_ : backgroundColorWithoutConvexityCheck_;
    }


    [[nodiscard]] const Color &getbackgroundColorWithoutConvexityCheck() const {
        return backgroundColorWithoutConvexityCheck_;
    }

    void setbackgroundColorWithoutConvexityCheck(const Color &backgroundColorWithoutConvexityCheck) {
        backgroundColorWithoutConvexityCheck_ = backgroundColorWithoutConvexityCheck;
    }

    [[nodiscard]] const Color &getbackgroundColorWithConvexityCheck() const {
        return backgroundColorWithConvexityCheck_;
    }

    void setbackgroundColorWithConvexityCheck(const Color &backgroundColorWithConvexityCheck) {
        backgroundColorWithConvexityCheck_ = backgroundColorWithConvexityCheck;
    }

    [[nodiscard]] const Polygon &getPolygon() const {
        return currentPolygon_;
    }

    [[nodiscard]] const Point<int> &getLastMousePosition() const {
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

    [[nodiscard]] bool isPFlag() const {
        return pFlag_;
    }

    void switchPFlag() {
        pFlag_ = !pFlag_;
        cout << "P flag is " << pFlag_ << endl;
    }

    [[nodiscard]] bool isKFlag() const {
        return kFlag_;
    }

    void switchKFlag() {
        if (state_ == DRAWING) {
            kFlag_ = !kFlag_;
            cout << "K flag is " << kFlag_ << endl;
        }
    }

    [[nodiscard]] bool isDrawing() const {
        return state_ == DRAWING;
    }

    [[nodiscard]] bool isExamining() const {
        return state_ == EXAMINING_POINTS;
    }

    void switchState() {
        if (state_ == DRAWING) {
            if (currentPolygon_.getVertices().size() < 3) {
                cout << "Cannot switch state if number of vertices is less than 3" << endl;
                return;
            }

            state_ = EXAMINING_POINTS;
        } else {
            state_ = DRAWING;
            currentPolygon_ = Polygon();
            kFlag_ = false;
            pFlag_ = false;
        };
    }

    bool mousePress(int x, int y) {
        if (state_ == DRAWING) {
            if (kFlag_) {
                if (!currentPolygon_.addPointIfStillConvex(Point(x, y))) {
                    cout << "Point could not be added because it makes the polygon concave." << endl;
                };
            } else {
                currentPolygon_.addPoint(Point(x, y));
            }
        } else {
            if (currentPolygon_.getConvexityType() == CONCAVE) {
                cout << "Cannot determine relationship between point and polygon if the polygon is concave." << endl;
            } else {
                RelativePositionToPolygon position = currentPolygon_.getRelativePosition(Point(x, y));
                string position_string = position == INSIDE ? "inside" : position == OUTSIDE ? "outside" : "at edge";
                cout << "Point (" << x << ", " << y << ") is " << position_string << " of polygon." << endl;
            }
        }

        return true;
    }

    bool mouseMoved(int x, int y) {
        lastMousePosition_ = Point(x, y);
        return state_ == DRAWING;
    }

private:
    enum ConvexPolygonState {
        DRAWING, EXAMINING_POINTS
    };

    Color foregroundColor_;
    Color backgroundColorWithoutConvexityCheck_;
    Color backgroundColorWithConvexityCheck_;
    ConvexPolygonState state_ = DRAWING;
    Polygon currentPolygon_;
    Point<int> lastMousePosition_ = Point<int>(0, 0);
    int width_;
    int height_;
    bool pFlag_{};
    bool kFlag_{};
};


#endif //FER_UI_CONVEX_POLYGON_DATA_MODEL_H
