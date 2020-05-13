//
// Created by m43 on 02. 05. 2020..
//

#include <GL/glut.h>
#include "../utility/utilities.h"
#include "../utility/triangle.h"
#include "../utility/object_model.h"
#include "../ex06b/projecting_renderer.h"
#include "../ex06b/projecting_demo.cpp"
#include "../linalg/irg.h"
#include "../linalg/irg.cpp"


using namespace std;

static void reshape(int width, int height);

static void display();

int main(int argc, char **argv) {
    // Task 7.2
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
//    auto pr = IRG::buildFrustumMatrix(-0.25, 0.25, -0.25, 0.25, 1, 100);
    auto m = tp->nMultiply(*pr);

    Color c = dataModel.getBackgroundColor();
    glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto om = dataModel.getObjectModel();
    auto vertices = om->getVertices();
    auto faces = om->getFaces();

    Painter::setColor(dataModel.getForegroundColor());
    bool checkVisibilityBefore = true;
    bool checkVisibilityAfter = false;
    vector<bool> visibilities;
    switch (dataModel.getAlgorithmNumber()) {
        case 1:
            checkVisibilityBefore = false;
            break;
        case 2:
            visibilities = om->determineFaceVisibilities1(dvec3(eye.get(0), eye.get(1), eye.get(2)));
            break;
        case 3:
            visibilities = om->determineFaceVisibilities2(dvec3(eye.get(0), eye.get(1), eye.get(2)));
            break;
        case 4:
            checkVisibilityBefore = false;
            checkVisibilityAfter = true;
            break;
        default:
            throw logic_error("Invalid algorithm number found in data model.");
    }
    for (unsigned long i = 0; i < faces.size(); i++) {
        auto f = faces[i];
        if (checkVisibilityBefore && !visibilities[i]) {
            continue;
        }
        auto v1 = vertices[f.x];
        auto v2 = vertices[f.y];
        auto v3 = vertices[f.z];
        vector<Point<double>> viewPoints;
        for (auto v: {v1, v2, v3}) {
            auto point_original = make_shared<Vector>(vector<double>{v.x, v.y, v.z, 1});
            auto viewPoint = AbstractVector::toRowMatrix(point_original, false)->nMultiply(*m);
            auto viewPointHomogeneous = AbstractMatrix::toVector(move(viewPoint), false)->nFromHomogeneous();
            viewPoints.push_back(Point(viewPointHomogeneous->get(0), viewPointHomogeneous->get(1)));
        }
        if (!checkVisibilityAfter ||
            Triangle(viewPoints[0], viewPoints[1], viewPoints[2], WHITE_CLOUDS).isAntiClockwise()) {
            glBegin(GL_LINE_LOOP);
            for (auto vp: viewPoints) {
                switch (dataModel.getAlgorithmNumber()) {
                    case 1:
                        glColor3f((vp.getX() + 3) / 4, (vp.getY() + 1) / 2, (vp.getX() + vp.getY() + 7) / 9);
                        break;
                    case 2:
                        glColor3f((viewPoints[0].getX() + 1) / 2, (viewPoints[0].getY() + 1) / 2,
                                  (viewPoints[0].getX() + viewPoints[0].getY() + 1) / 2);
                        break;
                    case 3:
                        glColor3f((vp.getX() + 1) / 2, (vp.getY() + 1) / 2, (vp.getX() + vp.getY() + 2) / 4);
                        break;
                    case 4:
                        glColor3f((vp.getX() + 12) / 13, (vp.getY() + 1) / 2, (vp.getX() + vp.getY() + 2) / 4);
                        break;
                }
                glVertex2f(vp.getX(), vp.getY());
            }
            glEnd();
        }
    }

    glFlush(); // TODO is this needed?
    glutSwapBuffers();
    return;
}
