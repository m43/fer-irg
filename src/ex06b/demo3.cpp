//
// Created by m43 on 01. 05. 2020..
//

#include <GL/glut.h>
#include "../utility/utilities.h"
#include "../utility/object_model.h"
#include "projecting_renderer.h"
#include "projecting_demo.cpp"
#include "../linalg/irg.h"
#include "../linalg/irg.cpp"


using namespace std;

static void reshape(int width, int height);

static void display();

int main(int argc, char **argv) {
    // Task 6.3
    demo(argc, argv, reshape, display);
    return 0;
}

static void reshape(int width, int height) {
    dataModel.setHeight(height);
    dataModel.setWidth(width);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

static void display() {
    auto eye = Vector(Painter::getEyePosition());
    auto center = Vector(vector<double>{0, 0, 0});
    auto viewUp = Vector(vector<double>{0, 1, 0});
    auto tp = IRG::lookAtMatrix(eye, center, viewUp);
    auto pr = IRG::buildFrustumMatrix(-0.5, 0.5, -0.5, 0.5, 1, 100);
    auto m = tp->nMultiply(*pr);

    Color c = dataModel.getBackgroundColor();
    glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto om = dataModel.getObjectModel();
    auto vertices = om->getVertices();
    auto faces = om->getFaces();

    for (auto &v: vertices) {
        auto point_original = make_shared<Vector>(vector<double>{v.x, v.y, v.z, 1});
        auto viewPoint = AbstractVector::toRowMatrix(point_original, false)->nMultiply(*m);
        auto viewPointHomogeneous = AbstractMatrix::toVector(move(viewPoint), false)->nFromHomogeneous();
        v.x = viewPointHomogeneous->get(0);
        v.y = viewPointHomogeneous->get(1);
    }

    Painter::setColor(dataModel.getForegroundColor());
    for (auto f: faces) {
        glBegin(GL_LINE_LOOP);
        auto v1 = vertices[f.x];
        auto v2 = vertices[f.y];
        auto v3 = vertices[f.z];
        for (auto v: {v1, v2, v3}) {
            glVertex2f(v.x, v.y);
        }
        glEnd();
    }

    glFlush(); // TODO is this needed?
    glutSwapBuffers();
    return;
}
