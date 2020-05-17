//
// Created by m43 on 16. 05. 2020..
//

#include <iostream>
#include <GL/glut.h>
#include "mandelbrot_painter.h"

using namespace std;


int main(int argc, char **argv) {
    cout << "*****************************************" << endl;
    cout << "*************** MANDELBROT **************" << endl;
    cout << "*****************************************" << endl;

    cout << "\n### DRAWING ALGORITHM ###\n";
    cout << "\tPress 1 to use algorithm 1.\n";
    cout << "\tPress 2 to use algorithm 2.\n";
    cout << "\tPress 3 to increase max recursion limit.\n";
    cout << "\tPress 4 to decrease max recursion limit.\n";

    cout << "### COLORING ALGORITHM ###\n";
    cout << "\tPress b to use color algorithm \"black&white\"\n";
    cout << "\tPress v to use color algorithm \"blues\"\n";
    cout << "\tPress c to use color algorithm \"colorful\"\n";

    cout << "### ZOOMING ###\n";
    cout << "\tPress anywhere using mouse to zoom in at that point. The old panel dimensions will be saved.\n";
    cout << "\tPress x to restore last saved panel dimensions.\n";
    cout << "\tPress ESC to restore initial panel state.\n";
    cout << "\tUse arrow keys the eye position above the drawing panel.\n";

    cout << "\nPress q to quit.\n\n";


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(1080, 300);
    glutCreateWindow("Exercise 11B - Mandelbrot");

    glutDisplayFunc(MandelbrotPainter::display);
    glutReshapeFunc(MandelbrotPainter::reshape);
    glutKeyboardFunc(MandelbrotPainter::keyPressed);
    glutSpecialFunc(MandelbrotPainter::specialKeyPressed);
    glutMouseFunc(MandelbrotPainter::mousePressedOrReleased);
    glutMainLoop();
}