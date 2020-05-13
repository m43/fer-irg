//
// Created by m43 on 01. 05. 2020..
//

#include <GL/glut.h>
#include "projecting_renderer.h"
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
}

static void display() {
    int width = dataModel.getWidth();
    int height = dataModel.getWidth();
    auto eye = Painter::getEyePosition();

    // Moved this part here so that it is executed when `glutPostRedisplay` is called
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(2 * atan(0.5 / 1) * 180 / M_PIf32, 1. * width / height, 1, 100);
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    Painter::display();
}