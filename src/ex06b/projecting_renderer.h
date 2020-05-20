//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_3D_OBJECT_RENDERER_CPP
#define FER_IRG_3D_OBJECT_RENDERER_CPP

#include <vector>
#include <cmath>
#include <GL/glut.h>

#include "projecting_data_model.h"
#include "../utility/point.h"
#include "../utility/color.h"
#include "../utility/object_model.h"
#include "../utility/triangle.h"

// international love TODO remove global variables!
const double initAngle = atan(1. / 3);
const double r = 1 / sin(initAngle);
DataModel dataModel = DataModel(
        BLUE_PETER_RIVER, DEFAULT_BACKGROUND_COLOR,
        540, 445, initAngle, 5. / 180 * M_PIf32);

class Painter {
public:

    static vector<double> getEyePosition() {
        return vector<double>{r * cos(dataModel.getAngle()), 4, r * sin(dataModel.getAngle())};
    }

    static void display() {
        Color c = dataModel.getBackgroundColor();
        glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        renderDataModel();
        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        int mini = std::min(width, height);
        double scale = 1.1f / (double) mini;
        glOrtho(-scale * width, scale * width, -scale * height, scale * height, -2, 2);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        dataModel.setHeight(height);
        dataModel.setWidth(width);
    }

    static void renderDataModel() {
        auto om = dataModel.getObjectModel();
        auto vertices = om->getVertices();
        auto faces = om->getFaces();

        if (dataModel.shouldFill()) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            drawRainbowTriangleFromFace(faces, vertices);
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        setColor(WHITE_CLOUDS);
        for (auto f: faces) {
            glBegin(GL_LINE_LOOP);
            auto v1 = vertices[f.x];
            auto v2 = vertices[f.y];
            auto v3 = vertices[f.z];
            glVertex3d(v1.x, v1.y, v1.z);
            glVertex3d(v2.x, v2.y, v2.z);
            glVertex3d(v3.x, v3.y, v3.z);
            glEnd();
        }

//        glFlush(); // TODO is this needed?
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case '1':
                dataModel.setAlgorithmNumber(1);
                glutPostRedisplay();
                break;
            case '2':
                dataModel.setAlgorithmNumber(2);
                glutPostRedisplay();
                break;
            case '3':
                dataModel.setAlgorithmNumber(3);
                glutPostRedisplay();
                break;
            case '4':
                dataModel.setAlgorithmNumber(4);
                glutPostRedisplay();
                break;
            case 'f':
                dataModel.switchFill();
                glutPostRedisplay();
                break;
            case 'r':
                dataModel.incrementAngle();
                glutPostRedisplay();
                break;
            case 'l':
                dataModel.decrementAngle();
                glutPostRedisplay();
                break;
            case 27:
                dataModel.resetAngle();
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    static void setColor(Color color) {
        glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
    }

    static inline void
    drawTriangleFromFace(const vector<ivec3> &faces, vector<dvec3> vertices, Color color) {
        setColor(color);
        glBegin(GL_TRIANGLES);
        for (auto f: faces) {
            auto v1 = vertices[f.x];
            auto v2 = vertices[f.y];
            auto v3 = vertices[f.z];
            glVertex3d(v1.x, v1.y, v1.z);
            glVertex3d(v2.x, v2.y, v2.z);
            glVertex3d(v3.x, v3.y, v3.z);
        }
        glEnd();
    }

    static inline void
    drawRainbowTriangleFromFace(const vector<ivec3> &faces, vector<dvec3> vertices) {
        glBegin(GL_TRIANGLES);
        for (auto f: faces) {
            auto v1 = vertices[f.x];
            auto v2 = vertices[f.y];
            auto v3 = vertices[f.z];
            glColor3f((v1.x + 1) / 2, (v1.y + 1) / 2, (v1.z + 1) / 2);
            glVertex3d(v1.x, v1.y, v1.z);
            glColor3f((v2.x + 1) / 2, (v2.y + 1) / 2, (v2.z + 1) / 2);
            glVertex3d(v2.x, v2.y, v2.z);
            glColor3f((v3.x + 1) / 2, (v3.y + 1) / 2, (v3.z + 1) / 2);
            glVertex3d(v3.x, v3.y, v3.z);
        }
        glEnd();
    }

    static inline void
    drawCenteredRainbowTriangleFromFace(const vector<ivec3> &faces, vector<dvec3> vertices) {
        glBegin(GL_TRIANGLES);
        for (auto f: faces) {
            auto v1 = vertices[f.x];
            auto v2 = vertices[f.y];
            auto v3 = vertices[f.z];
            glColor3f((v1.x + v2.x + v3.x + 3) / 6, (v1.y + v2.y + v3.y + 3) / 6, (v1.z + v2.z + v3.z + 3) / 6);
            glVertex3d(v1.x, v1.y, v1.z);
            glVertex3d(v2.x, v2.y, v2.z);
            glVertex3d(v3.x, v3.y, v3.z);
        }
        glEnd();
    }
};


#endif //FER_IRG_3D_OBJECT_RENDERER_CPP
