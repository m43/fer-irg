//
// Created by m43 on 08. 04. 2020..
//

#include <GL/glut.h>
#include "../utility/point.h"
#include "../utility/color.h"
#include "triangle_data_model.h"

TriangleDataModel dataModel(DEFAULT_PALETTE, DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR, 540, 360);


class TrianglePainter {
public:
    // TODO how to use a non-static member function as the function argument for glut methods like glutDisplayFunc?
    // explicit TrianglePainter(TriangleDataModel dataModel) : dataModel(std::move(dataModel)) {}

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
        glBegin(GL_TRIANGLES);
        for (auto t: dataModel.getTriangles()) {
            setColor(t.getColor());
            glVertex2i(t.getA().getX(), t.getA().getY());
            glVertex2i(t.getB().getX(), t.getB().getY());
            glVertex2i(t.getC().getX(), t.getC().getY());
            // maybe a line of foreground color around the triangles..
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
                glBegin(GL_LINES);
                setColor(dataModel.getCurrentColor());
                Point p1 = dataModel.getFirstClick();
                Point p2 = dataModel.getLastMousePosition();
                glVertex2i(p1.getX(), p1.getY());
                glVertex2i(p2.getX(), p2.getY());
                glEnd();
                break;
            }
            case SECOND_CLICK: {
                glBegin(GL_TRIANGLES);
                setColor(dataModel.getCurrentColor());
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

    static void keyPressed(unsigned char key, int, int) {
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

//private:
//    TriangleDataModel dataModel;
};