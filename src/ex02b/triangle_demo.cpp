//
// Created by m43 on 03. 04. 2020..
//

#include <GL/glut.h>
#include "triangle_painter.cpp"

using namespace std;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Exercise 2B");
    glutDisplayFunc(TrianglePainter::display);
    glutReshapeFunc(TrianglePainter::reshape);
    glutKeyboardFunc(TrianglePainter::keyPressed);
    glutMouseFunc(TrianglePainter::mousePressedOrReleased);
    glutMotionFunc(TrianglePainter::mouseMovedOrDragged);
    glutPassiveMotionFunc(TrianglePainter::mouseMovedOrDragged);

    glutMainLoop();
}