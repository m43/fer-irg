//
// Created by m43 on 01. 05. 2020..
//

#include <GL/glut.h>
#include <math.h>
#include "../utility/utilities.h"
#include "../utility/object_model.h"
#include "../utility/3d_object_renderer.h"
#include "projecting_demo.cpp"

using namespace std;

static void reshape(int width, int height);

static void display();

int main(int argc, char **argv) {
    demo(argc, argv, reshape, display);
    return 0;
}

static void reshape(int width, int height) {
    // Task 6.2
    dataModel.setHeight(height);
    dataModel.setWidth(width);

    glViewport(0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(2 * atan(0.5 / 1) * 180 / 3.141592653589793, 1. * width / height, 1, 100);
    gluLookAt(3, 4, 1, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);
}

static void display() {
    return;
}