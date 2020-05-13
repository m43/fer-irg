//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_BEZIER_DATA_MODEL_H
#define FER_IRG_BEZIER_DATA_MODEL_H

#include <utility>
#include <vector>
#include <cmath>

#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/line.h"
#include "../utility/polygon.h"
#include "../utility/bezier.h"

using namespace std;

class BezierDataModel {
public:

    BezierDataModel(vector<Color> colorPalette, int width, int height)
            : palette_(std::move(colorPalette)), width_(width), height_(height) {
        int i = 0;
        backgroundColor_ = i++ % palette_.size();
        approximationCurveColor_ = i++ % palette_.size();
        interpolationCurveColor_ = i++ % palette_.size();
        crossColor_ = i++ % palette_.size();
        lineStripColor_ = i++ % palette_.size();
    }

    [[nodiscard]] const Color &getApproximationCurveColor() const {
        return palette_[approximationCurveColor_];
    }

    void switchApproximationCurveColor() {
        approximationCurveColor_ += 1;
        approximationCurveColor_ %= palette_.size();
    }

    [[nodiscard]] const Color &getInterpolationCurveColor() const {
        return palette_[interpolationCurveColor_];
    }

    void switchInterpolationCurveColor() {
        interpolationCurveColor_ += 1;
        interpolationCurveColor_ %= palette_.size();
    }

    [[nodiscard]] const Color &getCrossColor() const {
        return palette_[crossColor_];
    }

    void switchCrossColor() {
        crossColor_ += 1;
        crossColor_ %= palette_.size();
    }

    [[nodiscard]] const Color &getLineStripColor() const {
        return palette_[lineStripColor_];
    }

    void switchLineStripColor() {
        lineStripColor_ += 1;
        lineStripColor_ %= palette_.size();
    }

    [[nodiscard]] const Color &getBackgroundColor() const {
        return palette_[backgroundColor_];
    }

    void switchBackgroundColor() {
        backgroundColor_ += 1;
        backgroundColor_ %= palette_.size();
    }

    [[nodiscard]] shared_ptr<BezierCurve> getBezier() const {
        return bezier_;
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

    bool mousePress(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            bezier_->addPoint(Point<double>(x, y));
            return true;
        }

        if (button == GLUT_RIGHT_BUTTON) {
            if (state == GLUT_DOWN) {
                if (!down_) {
                    down_ = true;
                    indexOfClosestPoint_ = -1;
                    const auto points = bezier_->getPoints();
                    for (unsigned long i = 0; i < points.size(); i++) {
                        if (pow(points[i].getX() - x, 2) + pow(points[i].getY() - y, 2) < 100) {
                            indexOfClosestPoint_ = (int) i;
                            break;
                        }
                    }
                }
                if (indexOfClosestPoint_ == -1) {
                    return false;
                } else {
                    bezier_->updatePoint(indexOfClosestPoint_, Point<double>(x, y));
                    return true;
                }
            } else {
                down_ = false;
                return false;
            }
        }

        return false;
    }

    bool mouseMoved(int x, int y) {
        if (!down_ || indexOfClosestPoint_ == -1) {
            return false;
        } else {
            bezier_->updatePoint(indexOfClosestPoint_, Point<double>(x, y));
            return true;
        }
    }

    void resetCurve() {
        bezier_->reset();
    }

private:
    vector<Color> palette_;
    int approximationCurveColor_;
    int interpolationCurveColor_;
    int crossColor_;
    int lineStripColor_;
    int backgroundColor_;
    shared_ptr<BezierCurve> bezier_ = make_shared<BezierCurve>();
    bool down_ = false;
    int indexOfClosestPoint_ = -1;
    int width_;
    int height_;
};


#endif //FER_IRG_BEZIER_DATA_MODEL_H
