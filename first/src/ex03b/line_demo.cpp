//
// Created by m43 on 04. 04. 2020..
//

#include <GL/glut.h>
#include "line_painter.h"

using namespace std;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Exercise 3B");
    glutDisplayFunc(LinePainter::display);
    glutReshapeFunc(LinePainter::reshape);
    glutKeyboardFunc(LinePainter::keyPressed);
    glutMouseFunc(LinePainter::mousePressedOrReleased);
    glutMotionFunc(LinePainter::mouseMovedOrDragged);
    glutPassiveMotionFunc(LinePainter::mouseMovedOrDragged);

    glutMainLoop();
}