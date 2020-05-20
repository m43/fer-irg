//
// Created by m43 on 04. 04. 2020..
//

#include <GL/glut.h>
#include "bezier_painter.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "********************************************" << endl;
    cout << "*************** BEZIER CURVES **************" << endl;
    cout << "********************************************" << endl;

    cout << "\n### COLORING ###\n";
    cout << "\tPress 1 to switch background color.\n";
    cout << "\tPress 2 to switch approximation curve color.\n";
    cout << "\tPress 3 to switch interpolation curve color.\n";
    cout << "\tPress 4 to switch line strip color.\n";
    cout << "\tPress 5 to switch cross color.\n";

    cout << "### INTERACTION USING MOUSE ###\n";
    cout << "\tPress anywhere with left mouse click to add an point.\n";
    cout << "\tPress and drag any of the points using right mouse button.\n";
    cout << "\tPress r to reset all curve points.\n";

    cout << "\nPress q to quit.\n\n";

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