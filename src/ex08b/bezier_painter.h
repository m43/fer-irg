//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_BEZIER_PAINTER_H
#define FER_IRG_BEZIER_PAINTER_H

#include <utility>
#include <vector>
#include <GL/glut.h>
#include "../utility/utilities.h"
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/triangle.h"
#include "bezier_data_model.h"

using namespace std;

// TODO Not good to define it like a global variable. I defined it like this only to be able to use it from static
//      member function of the ConvexPolygonPainter class below.
BezierDataModel dataModel(
        vector<Color>{BLACK, ORANGE_CARROT, GREEN_EMERALD, YELLOW_SUN_FLOWER, BLUE_PETER_RIVER, RED_ALIZARIN, ORANGE,
                      GREEN_EMERALD, PURPLE_WISTERIA, TURQUOISE, WHITE_CLOUDS}, 720, 445);

// TODO might be a good idea to write an abstract painter and an abstract data model...

/**
 * Class models an convex polygon painter function that provides the functionality of rendering convex polygons.
 * The necessary information for about the polygons is taken from the an ConvexPolygonDataModel.
 */
// TODO is there a better name then Painter? Or is it rather good enough?
class BezierPainter {
public:

    // TODO how to use a non-static member function as the function argument for glut methods like glutDisplayFunc?
    //      If non-static member functions could be used in a cleanly, then I could just pass the data model as an
    //      argument of the painter constructor

    static void display() {
        Color c = dataModel.getBackgroundColor();
        glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        renderDataModel();
        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        dataModel.setHeight(height);
        dataModel.setWidth(width);

        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width - 1, height - 1, 0, 0, 1);

        glMatrixMode(GL_MODELVIEW);
    }

    static void renderDataModel() {

        auto bezer = dataModel.getBezier();
        const auto points = bezer->getPoints();

        if (points.size() >= 2) {
            glBegin(GL_LINE_STRIP);
            setColor(dataModel.getLineStripColor());
            for (unsigned long i = 0; i < points.size(); i++) {
                glVertex2f(points[i].getX(), points[i].getY());
            }
            glEnd();
            drawCurve(1000, dataModel.getApproximationCurveColor(), false, *bezer);
            drawCurve(1000, dataModel.getInterpolationCurveColor(), true, *bezer);
        }

        for (auto p : points) {
            drawCross(p, dataModel.getCrossColor());
        }
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case 'r':
                dataModel.resetCurve();
                glutPostRedisplay();
                break;
            case '1':
                dataModel.switchBackgroundColor();
                glutPostRedisplay();
                break;
            case '2':
                dataModel.switchApproximationCurveColor();
                glutPostRedisplay();
                break;
            case '3':
                dataModel.switchInterpolationCurveColor();
                glutPostRedisplay();
                break;
            case '4':
                dataModel.switchLineStripColor();
                glutPostRedisplay();
                break;
            case '5':
                dataModel.switchCrossColor();
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    static void mousePressedOrReleased(int button, int state, int x, int y) {
        if (dataModel.mousePress(button, state, x, y)) {
            glutPostRedisplay();
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

    static void drawCross(Point<double> center, Color color, int size = 3) {
        drawLine(
                Point<double>(center.getX() - size, center.getY() - size),
                Point<double>(center.getX() + size, center.getY() + size), color
        );
        drawLine(
                Point<double>(center.getX() - size, center.getY() + size),
                Point<double>(center.getX() + size, center.getY() - size), color
        );
    }

    static void drawLine(Point<double> p1, Point<double> p2, Color color) {
        setColor(color);
        glBegin(GL_LINES);
        glVertex2f(p1.getX(), p1.getY());
        glVertex2f(p2.getX(), p2.getY());
        glEnd();
    }

    static void drawCurve(int points, Color color, bool shouldInterpolate, BezierCurve &bezier) {
        if (points <= 0) {
            throw invalid_argument("Number of points must be positive!");
        }

        setColor(color);
        glBegin(GL_LINE_STRIP);
        Point<double> p = Point<double>(0, 0);
        for (int i = 0; i <= points; i++) {
            double t = i / (double) points;
            if (shouldInterpolate) {
                p = bezier.interpolate(t);
            } else {
                p = bezier.approximate(t);
            }
            glVertex2f(p.getX(), p.getY());
        }
        glEnd();
    }
};

#endif //FER_IRG_BEZIER_PAINTER_H
