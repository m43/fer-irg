//
// Created by m43 on 03. 04. 2020..
//

#include <iostream>
#include <utility>
#include <vector>
#include <GL/glut.h>

using namespace std;

class DataModel;

class Point;

class Triangle;

//class Square;

void reshape(int width, int height);

void display();

void renderDataModel();

void keyPressed(unsigned char key, int x, int y);

void mousePressedOrReleased(int button, int state, int x, int y);

void mouseMovedOrDragged(int x, int y);

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

    vector<float> asVector() {
        return vector({r_, g_, b_, a_});
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
const Color CLOUDS = Color::fromIntRGBValues(236, 240, 241, 1.0);
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
vector<Color> DEFAULT_PALETTE = vector<Color>(
        {RED_ALIZARIN, BLUE_PETER_RIVER, ORANGE, ORANGE_CARROT, YELLOW_SUN_FLOWER, GREEN_EMERALD, PURPLE_WISTERIA,
         TURQUOISE, CLOUDS});


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

//class Square {
//public:
//
//private:
//    Point p_;
//    int width_;
//    int height_;
//    Color color_;
//};

enum DataModelState {
    CLEAR, FIRST_CLICK, SECOND_CLICK
};

class DataModel {
public:
    explicit DataModel(vector<Color> palette, Color foregroundColor, Color backgroundColor, int height, int width)
            : foregroundColor_(foregroundColor), backgroundColor_(backgroundColor), palette_(std::move(palette)),
              width_(width),
              height_(height) {};

    [[nodiscard]] DataModelState getState() const {
        return state_;
    }

    [[nodiscard]] const vector<Triangle> &getTriangles() const {
        return triangles_;
    }

    void setTriangles(const vector<Triangle> &triangles) {
        triangles_ = triangles;
    }

    [[nodiscard]] const Point &getFirstClick() const {
        return firstClick_;
    }

    void setFirstClick(const Point &firstClick) {
        firstClick_ = firstClick;
    }

    [[nodiscard]] const Point &getSecondClick() const {
        return secondClick_;
    }

    void setSecondClick(const Point &secondClick) {
        secondClick_ = secondClick;
    }

    [[nodiscard]] const Point &getLastMousePosition() const {
        return lastMousePosition_;
    }

    void setLastMousePosition(const Point &lastMousePosition) {
        lastMousePosition_ = lastMousePosition;
    }

    [[nodiscard]] const Color &getCurrentColor() const {
        return palette_[currentColorIndex_];
    }

    void setCurrentColor(const Color &currentColor) {
        palette_[currentColorIndex_] = currentColor;
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

    bool mousePress(int x, int y) {
        if (state_ == SECOND_CLICK) {
            state_ = CLEAR;
            // TODO is this triangle created on the stack?
            triangles_.emplace_back(firstClick_, secondClick_, Point(x, y), palette_[currentColorIndex_]);
            return true;
        }

        if (state_ == CLEAR) {
            state_ = FIRST_CLICK;
            firstClick_ = Point(x, y);
        } else {
            state_ = SECOND_CLICK;
            secondClick_ = Point(x, y);
        }
        return false;
    }

    bool mouseMoved(int x, int y) {
        lastMousePosition_ = Point(x, y);
        return state_ != CLEAR;
    }

    bool nextColor() {
        currentColorIndex_ = (currentColorIndex_ + 1) % palette_.size();
        return true;
    }

    bool previousColor() {
        currentColorIndex_ = (currentColorIndex_ + palette_.size() - 1) % palette_.size();
        return true;
    }

    [[nodiscard]] const vector<Color> &getPalette() const {
        return palette_;
    }

    void setPalette(const vector<Color> &palette) {
        palette_ = palette;
    }

    [[nodiscard]] const Color &getForegroundColor() const {
        return foregroundColor_;
    }

    void setForegroundColor(const Color &foregroundColor) {
        foregroundColor_ = foregroundColor;
    }

    [[nodiscard]] const Color &getBackgroundColor() const {
        return backgroundColor_;
    }

    void setBackgroundColor(const Color &backgroundColor) {
        backgroundColor_ = backgroundColor;
    }

private:
    DataModelState state_ = CLEAR;
    vector<Triangle> triangles_ = vector<Triangle>();
    Color foregroundColor_;
    Color backgroundColor_;
    vector<Color> palette_ = vector<Color>();
    Point firstClick_ = Point(0, 0);
    Point secondClick_ = Point(0, 0);
    Point lastMousePosition_ = Point(0, 0);
    unsigned long currentColorIndex_ = 0;
    int width_;
    int height_;
};

// TODO go global
DataModel dataModel(DEFAULT_PALETTE, DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR, 540, 360);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Book - 01");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyPressed);
    glutMouseFunc(mousePressedOrReleased);
    glutMotionFunc(mouseMovedOrDragged);
    glutPassiveMotionFunc(mouseMovedOrDragged);
    glutMainLoop();
}

void glSetColor(Color color) {
    glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
}

void display() {
    Color c = dataModel.getBackgroundColor();
    glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    renderDataModel();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glDisable(GL_DEPTH_TEST);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width - 1, height - 1, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    dataModel.setHeight(height);
    dataModel.setWidth(width);
}

void renderDataModel() {
    glBegin(GL_TRIANGLES);
    for (auto t: dataModel.getTriangles()) {
        glSetColor(t.getColor());
        glVertex2i(t.getA().getX(), t.getA().getY());
        glVertex2i(t.getB().getX(), t.getB().getY());
        glVertex2i(t.getC().getX(), t.getC().getY());
        // TODO maybe a line of foreground color around the triangles..
    }
    glEnd();

    glBegin(GL_QUADS);
    auto c = dataModel.getCurrentColor();
    glColor4f(c.getR(), c.getG(), c.getB(), c.getA());
    glVertex2i(dataModel.getWidth(), 0);
    glVertex2i(dataModel.getWidth(), 15);
    glVertex2i(dataModel.getWidth() - 15, 15);
    glVertex2i(dataModel.getWidth() - 15, 0);
    glEnd();

    switch (dataModel.getState()) {
        case FIRST_CLICK: {
            glBegin(GL_LINE);
            glSetColor(dataModel.getCurrentColor());
            Point p1 = dataModel.getFirstClick();
            Point p2 = dataModel.getLastMousePosition();
            glVertex2i(p1.getX(), p1.getY());
            glVertex2i(p2.getX(), p2.getY());
            glEnd();
            break;
        }
        case SECOND_CLICK: {
            glBegin(GL_TRIANGLES);
            glSetColor(dataModel.getCurrentColor());
            Point p1 = dataModel.getFirstClick();
            Point p2 = dataModel.getSecondClick();
            Point p3 = dataModel.getLastMousePosition();
            glVertex2i(p1.getX(), p1.getY());
            glVertex2i(p2.getX(), p2.getY());
            glVertex2i(p3.getX(), p3.getY());
            glEnd();
            break;
        }
        default:
            break;
    }
}

void keyPressed(unsigned char key, int, int) {
    switch (key) {
        case 'n':
            if (dataModel.nextColor()) {
                glutPostRedisplay();
            }
            break;
        case 'p':
            if (dataModel.previousColor()) {
                glutPostRedisplay();
            }
            break;
        case 'q':
            exit(EXIT_SUCCESS);
    }
}

void mousePressedOrReleased(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (dataModel.mousePress(x, y)) {
            glutPostRedisplay();
        }
    }
}

void mouseMovedOrDragged(int x, int y) {
    if (dataModel.mouseMoved(x, y)) {
        glutPostRedisplay();
    }
}

