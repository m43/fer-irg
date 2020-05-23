//
// Created by m43 on 02. 05. 2020..
//

#include <GL/glut.h>
#include "../ex06b/projecting_renderer.h"
#include "../ex06b/projecting_demo.cpp"

using namespace std;

static void reshape(int width, int height);

static void display();

static void renderDataModel();

int main(int argc, char **argv) {
    // Task 7.1
    dataModel.setFill(true);
    demo(argc, argv, reshape, display);
    return 0;
}

static void reshape(int width, int height) {
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
    glFrustum(-0.5 * width / height, 0.5 * width / height, -0.5, 0.5, 1, 100);
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);


    Color c = dataModel.getBackgroundColor();
    glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    renderDataModel();
    glutSwapBuffers();
}

static void renderDataModel() {
    auto om = dataModel.getObjectModel();
    auto vertices = om->getVertices();
    auto faces = om->getFaces();

    glPolygonMode(GL_FRONT, GL_LINE);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    Painter::drawRainbowTriangleFromFace(faces, vertices);

    glFlush(); // TODO is this needed?
}
