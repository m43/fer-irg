//
// Created by m43 on 04. 04. 2020..
//

#include <GL/glut.h>
#include "bezier_painter.h"

using namespace std;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(600, 300);
    glutCreateWindow("Exercise 8B");

    glutDisplayFunc(BezierPainter::display);
    glutReshapeFunc(BezierPainter::reshape);
    glutKeyboardFunc(BezierPainter::keyPressed);
    glutMouseFunc(BezierPainter::mousePressedOrReleased);
    glutMotionFunc(BezierPainter::mouseMovedOrDragged);
    glutPassiveMotionFunc(BezierPainter::mouseMovedOrDragged);

    glutMainLoop();
}