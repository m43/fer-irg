//
// Created by m43 on 04. 04. 2020..
//

#include <GL/glut.h>
#include "convex_polygon_painter.h"

using namespace std;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(600, 300);
    glutCreateWindow("Exercise 4B");

    glutDisplayFunc(ConvexPolygonPainter::display);
    glutReshapeFunc(ConvexPolygonPainter::reshape);
    glutKeyboardFunc(ConvexPolygonPainter::keyPressed);
    glutMouseFunc(ConvexPolygonPainter::mousePressedOrReleased);
    glutMotionFunc(ConvexPolygonPainter::mouseMovedOrDragged);
    glutPassiveMotionFunc(ConvexPolygonPainter::mouseMovedOrDragged);

    glutMainLoop();
}