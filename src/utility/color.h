//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_COLOR_H
#define FER_IRG_COLOR_H

#include <vector>

class Color {
public:
    Color(const float r, const float g, const float b, const float a) : r_(r), g_(g), b_(b), a_(a) {}

    [[nodiscard]] float getR() const {
        return r_;
    }

    [[nodiscard]] float getG() const {
        return g_;
    }

    [[nodiscard]] float getB() const {
        return b_;
    }

    [[nodiscard]] float getA() const {
        return a_;
    }

    std::vector<float> asVector() {
        return std::vector({r_, g_, b_, a_});
    }

    static Color fromIntRGBValues(int r, int g, int b, float a) {
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a);
    }

private:
    float r_;
    float g_;
    float b_;
    float a_;
};

// TODO is there any way do define this const instances inside the Color class? Like in Java?
const Color WHITE_CLOUDS = Color::fromIntRGBValues(236, 240, 241, 1.0);
const Color BLACK = Color(0, 0, 0, 0);
Color BLUE_PETER_RIVER = Color::fromIntRGBValues(52, 152, 219, 1.0);
const Color RED_ALIZARIN = Color::fromIntRGBValues(231, 76, 60, 1.0);
const Color ORANGE = Color::fromIntRGBValues(243, 156, 18, 1.0);
const Color ORANGE_CARROT = Color::fromIntRGBValues(230, 126, 34, 1.0);
const Color YELLOW_SUN_FLOWER = Color::fromIntRGBValues(241, 196, 15, 1.0);
const Color PURPLE_WISTERIA = Color::fromIntRGBValues(142, 68, 173, 1.0);
const Color GREEN_EMERALD = Color::fromIntRGBValues(46, 204, 113, 1.0);
const Color TURQUOISE = Color::fromIntRGBValues(26, 188, 156, 1.0);
Color DEFAULT_BACKGROUND_COLOR = BLACK;
Color DEFAULT_FOREGROUND_COLOR = BLUE_PETER_RIVER;
std::vector<Color> DEFAULT_PALETTE = std::vector<Color>(
        {RED_ALIZARIN, BLUE_PETER_RIVER, ORANGE, ORANGE_CARROT, YELLOW_SUN_FLOWER, GREEN_EMERALD, PURPLE_WISTERIA,
         TURQUOISE, WHITE_CLOUDS});


#endif //FER_IRG_COLOR_H
