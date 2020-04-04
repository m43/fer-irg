//
// Created by m43 on 04. 04. 2020..
//

#ifndef FIRST_LINE_PAINTER_H
#define FIRST_LINE_PAINTER_H


#include <utility>
#include <vector>
#include <GL/glut.h>
#include "../utility/utilities.h"
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/triangle.h"
#include "line_data_model.h"

using namespace std;

// TODO not good to define it like this and then use from static member fucnction below.
//      same problem as with triangle_painter
LineDataModel dataModel(DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR, 540, 360);


class LinePainter {
public:
    static void display() {
        Color c = dataModel.getBackgroundColor();
        glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        renderDataModel();
        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width - 1, height - 1, 0, 0, 1);
        glMatrixMode(GL_MODELVIEW);

        dataModel.setHeight(height);
        dataModel.setWidth(width);
    }

    static void renderDataModel() {
        for (auto l: dataModel.getLines()) {
            Point p1 = l.getStart();
            Point p2 = l.getEnd();

            drawMyLine(p1, p2, dataModel.getForegroundColor());

            if (dataModel.isControled()) {
                int delta = (p2.getY() - p1.getY()) > 0 ? -4 : 4;
                drawLine(Point(p1.getX() + delta, p1.getY()), Point(p2.getX() + delta, p2.getY()), RED_ALIZARIN);
            }
        }

        glBegin(GL_QUADS);
        setColor(dataModel.getForegroundColor());
        glVertex2i(dataModel.getWidth(), 0);
        glVertex2i(dataModel.getWidth(), 15);
        glVertex2i(dataModel.getWidth() - 15, 15);
        glVertex2i(dataModel.getWidth() - 15, 0);
        glEnd();

        if (dataModel.isFirstClickMade()) {
            Point p1 = dataModel.getFirstClick();
            Point p2 = dataModel.getLastMousePosition();

            drawMyLine(p1, p2, dataModel.getForegroundColor());
//            drawLine(p1, p2, dataModel.getForegroundColor());

            if (dataModel.isControled()) {
                int delta = (p2.getY() - p1.getY()) > 0 ? -4 : 4;
                drawLine(Point(p1.getX() + delta, p1.getY()), Point(p2.getX() + delta, p2.getY()), RED_ALIZARIN);
            }
        }
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case 'k':
                dataModel.setControl(!dataModel.isControled());
                glutPostRedisplay();
                break;
            case 'o':
                dataModel.setSlicing(!dataModel.isSlicing());
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    static void mousePressedOrReleased(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            if (dataModel.mousePress(x, y)) {
                glutPostRedisplay();
            }
        }
    }

    static void mouseMovedOrDragged(int x, int y) {
        if (dataModel.mouseMoved(x, y)) {
            glutPostRedisplay();
        }
    }

protected:
    static void setColor(Color color) {
        glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
    }

    static void drawLine(Point p1, Point p2, Color c) {
        glBegin(GL_LINES);
        setColor(c);
        glVertex2i(p1.getX(), p1.getY());
        glVertex2i(p2.getX(), p2.getY());
        glEnd();
    }

    static void drawMyLine(Point p1, Point p2, Color c) {
        GLint xa = p1.getX();
        GLint ya = p1.getY();
        GLint xb = p2.getX();
        GLint yb = p2.getY();

        setColor(c);
        glBegin(GL_POINTS);
        {
            for (pair<GLint, GLint> vertex: ex_utilities::bresenham_line_vertices(xa, ya, xb, yb)) {
                glVertex2i(vertex.first, vertex.second);
            }
        }
        glEnd();
    }
};

#endif //FIRST_LINE_PAINTER_H
