//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_CONVEX_POLYGON_PAINTER_H
#define FER_IRG_CONVEX_POLYGON_PAINTER_H

#include <utility>
#include <vector>
#include <GL/glut.h>
#include "../utility/utilities.h"
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/triangle.h"
#include "convex_polygon_data_model.h"

using namespace std;

// TODO Not good to define it like a global variable. I defined it like this only to be able to use it from static
//      member function of the ConvexPolygonPainter class below.
ConvexPolygonDataModel dataModel(BLACK, WHITE_CLOUDS, GREEN_EMERALD, 720, 445);

// TODO might be a good idea to write an abstract painter and an abstract data model...

/**
 * Class models an convex polygon painter function that provides the functionality of rendering convex polygons.
 * The necessary information for about the polygons is taken from the an ConvexPolygonDataModel.
 */
// TODO is there a better name then Painter? Or is it rather good enough?
class ConvexPolygonPainter {
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

        glBegin(GL_QUADS);
        setColor(dataModel.getForegroundColor());
        glVertex2i(dataModel.getWidth(), 0);
        glVertex2i(dataModel.getWidth(), 15);
        glVertex2i(dataModel.getWidth() - 15, 15);
        glVertex2i(dataModel.getWidth() - 15, 0);
        glEnd();

        auto po = dataModel.getPolygon();
        auto vertices = po.getVertices();

        if (dataModel.isDrawing()) {
            if (vertices.size() == 1) {
                drawLine(vertices.back(), dataModel.getLastMousePosition(), dataModel.getForegroundColor());
            } else if (vertices.size() > 1) {
                // TODO Task for me.
                //  Remodel Polygon in order to draw polygons with an extra point that is not part of the polygon.
                //  This way I copy the polygon each time in order to append the lastMousePoistion point to the
                //  vertices.
                Polygon poCopy = Polygon(po.getVertices());

                if (dataModel.isKFlag()) {
                    poCopy.addPointIfStillConvex(dataModel.getLastMousePosition());
                } else {
                    poCopy.addPoint(dataModel.getLastMousePosition());
                }

                drawMyPolygon(poCopy, dataModel.getForegroundColor(), dataModel.isPFlag());
            }
        } else {
            drawMyPolygon(po, dataModel.getForegroundColor(), dataModel.isPFlag());
        }
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case 'k':
                dataModel.switchKFlag();
                glutPostRedisplay();
                break;
            case 'p':
                dataModel.switchPFlag();
                glutPostRedisplay();
                break;
            case 'n':
                dataModel.switchState();
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

    static void drawLine(Point<int> p1, Point<int> p2, Color c) {
        glBegin(GL_LINES);
        setColor(c);
        glVertex2i(p1.getX(), p1.getY());
        glVertex2i(p2.getX(), p2.getY());
        glEnd();
    }

    static void drawPolygon(const Polygon &po, Color c, bool fill) {
        if (fill) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        glBegin(GL_POLYGON);
        setColor(c);
        for (Point p: po.getVertices()) {
            glVertex2i(p.getX(), p.getY());
        }
        glEnd();
    }

    static void drawMyPolygon(Polygon &po, Color c, bool fill) {
        if (fill) {
            glBegin(GL_LINES);

            ConvexityType convexity = po.getConvexityType();
            auto isLeft = [&convexity](Edge<int> edge) {
                return (convexity == CONVEX_CLOCKWISE) == edge.pointsUp();
            };

            int ymin = po.getYmin();
            int ymax = po.getYmax();
            int xmin = po.getXmin();
            int xmax = po.getXmax();

            for (int y = ymin; y <= ymax; y++) {
                double l = xmin;
                double r = xmax;
                for (const Edge<int> &e: po.getEdges()) {
                    if (e.getA() != 0) {
                        int y1 = e.getStart().getY();
                        int y2 = e.getEnd().getY();
                        if ((y > y1 && y > y2) || (y < y1 && y < y2)) {
                            continue;
                        }
                        double intersectionX = (-e.getB() * y - e.getC()) / (double) e.getA();
                        if (isLeft(e)) {
                            l = std::max(l, intersectionX);
                        } else {
                            r = std::min(r, intersectionX);
                        }
                    } else {
                        if (e.getB() == 0) {
                            continue;
                        }
                        if (e.getStart().getY() == y) {
                            if (e.getStart().getX() < e.getEnd().getX()) {
                                l = std::max(l, (double) e.getStart().getX());
                                r = std::min(r, (double) e.getEnd().getX());
                            } else {
                                l = std::max(l, (double) e.getEnd().getX());
                                r = std::min(r, (double) e.getStart().getX());
                            }
                            break;
                        }
                    }
                }
                if (l <= r) {
                    glVertex2i(round(l), y);
                    glVertex2i(round(r), y);
                }
            }
            glEnd();
        }

        glBegin(GL_LINES);
        setColor(c);

        auto vertices = po.getVertices();
        auto lastVertex = vertices.back();
        for (Point p: vertices) {
            glVertex2i(lastVertex.getX(), lastVertex.getY());
            glVertex2i(p.getX(), p.getY());
            lastVertex = p;
        }
        glEnd();
    }
};

#endif //FER_IRG_CONVEX_POLYGON_PAINTER_H
