//
// Created by m43 on 04. 04. 2020..
//

#ifndef FER_IRG_3D_OBJECT_RENDERER_CPP
#define FER_IRG_3D_OBJECT_RENDERER_CPP

#include <GL/glut.h>
#include <vector>
#include "point.h"
#include "color.h"
#include "object_model.h"
#include "triangle.h"
#include "3d_object_data_model.h"

// international love TODO remove global variables!
DataModel dataModel = DataModel(DEFAULT_FOREGROUND_COLOR, DEFAULT_BACKGROUND_COLOR, 540, 445);

class Painter {
public:

    static void display() {
        Color c = dataModel.getBackgroundColor();
        glClearColor(c.getR(), c.getG(), c.getB(), c.getA());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        auto n_result = dataModel.getObjectModel()->normalize();
        glScalef(n_result.scalingFactor_, n_result.scalingFactor_, n_result.scalingFactor_);

        glRotatef(dataModel.getRotateX(), 1, 0, 0);
        glRotatef(dataModel.getRotateY(), 0, 1, 0);

        glTranslatef(-n_result.center_.x, -n_result.center_.y, -n_result.center_.z);

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

        dataModel.setHeight(height);
        dataModel.setWidth(width);
    }

    static void renderDataModel() {
        auto om = dataModel.getObjectModel();
        auto vertices = om->getVertices();
        auto faces = om->getFaces();

        if (dataModel.shouldFill()) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            drawTriangleFromFace(faces, vertices, ORANGE);
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

        glFlush(); // TODO is this needed?
    }

    static void specialKeyPressed(int key, int, int) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                dataModel.rotateY(5);
                glutPostRedisplay();
                break;
            case GLUT_KEY_LEFT:
                dataModel.rotateY(-5);
                glutPostRedisplay();
                break;
            case GLUT_KEY_UP:
                dataModel.rotateX(5);
                glutPostRedisplay();
                break;
            case GLUT_KEY_DOWN:
                dataModel.rotateX(-5);
                glutPostRedisplay();
                break;
            default:
                break;
        }
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case 'f':
                dataModel.switchFill();
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    static void mousePressedOrReleased(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            if (dataModel.mousePress(x, y)) {
                glutPostRedisplay();
            }
        }
    }

    static void mouseMovedOrDragged(int x, int y) {
        if (dataModel.mouseMoved(x, y)) {
            glutPostRedisplay();
        }
    }

protected:
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
            glColor3f((v1.x + 1) / 2, (v1.y + 1) / 2, (v1.z + 1) / 2);
            glVertex3d(v1.x, v1.y, v1.z);
            glVertex3d(v2.x, v2.y, v2.z);
            glVertex3d(v3.x, v3.y, v3.z);
        }
        glEnd();
    }

    static void drawBox() {
        // this box was a playground..

        // front
        setColor(GREEN_EMERALD);
        glBegin(GL_POLYGON);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glEnd();

        // top
        setColor(YELLOW_SUN_FLOWER);
        glBegin(GL_POLYGON);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glEnd();


        // right
        setColor(BLUE_PETER_RIVER);
        glBegin(GL_POLYGON);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glEnd();

        // left
        setColor(ORANGE_CARROT);
        glBegin(GL_POLYGON);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glEnd();

        // top
        setColor(RED_ALIZARIN);
        glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glEnd();

        // bottom
        glBegin(GL_POLYGON);
        setColor(WHITE_CLOUDS);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glEnd();
    }
};


#endif //FER_IRG_3D_OBJECT_RENDERER_CPP
