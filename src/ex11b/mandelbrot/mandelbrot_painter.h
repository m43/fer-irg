//
// Created by m43 on 16. 05. 2020..
//

#ifndef FER_IRG_MANDELBROT_PAINTER_H
#define FER_IRG_MANDELBROT_PAINTER_H

#include <iostream>
#include <complex>
#include <utility>
#include <vector>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "../../utility/utilities.h"
#include "../../utility/color.h"
#include "mandelbrot_data_model.h"


using namespace std;
using namespace glm;
//double cx = -0.7454265;
//double cy = 0.113009;
//double www = 4.;
//double www = 4. / 5;
//double www = 4./pow(5,3);
//double www = 4./pow(5,4);
//double www = 4. / pow(5, 5);
//double www = 4./pow(5,6);
//double www = 4./pow(5,7);
//double www = 4./pow(5,8);
//double www = 4./pow(5,9);
//const ComplexPlaneDimensions cp_init(cy - www / 2, cy + www / 2, cx - www / 2, cx + www / 2);
const ComplexPlaneDimensions cp_init(-1.2, 1.2, -2, 1);
MandelbrotDataModel dataModel(720, 600, 16, cp_init, 0.1, 16);

class MandelbrotPainter {
public:

    static void display() {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        renderDataModel();
        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        dataModel.setHeight(height);
        dataModel.setWidth(width);

        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static void renderDataModel() {
        int w = dataModel.getWidth();
        int h = dataModel.getHeight();

        auto cp = dataModel.getComplexPlaneDimensions();
        auto limit = dataModel.getRecursionDepth();
        auto du = cp.umax - cp.umin;
        auto dv = cp.vmax - cp.vmin;

        glBegin(GL_POINTS);
        for (int x = 0; x < w; x++) {
            for (int y = 0; y < h; y++) {
                double u = x / (double) w * du + cp.umin;
                double v = y / (double) h * dv + cp.vmin;

                int depth;
                if (dataModel.getAlgorithm() == 1) {
                    depth = divergence_test1(complex<double>(u, v), limit);
                } else {
                    depth = divergence_test2(complex<double>(u, v), limit);
                }

                if (dataModel.getPalette() == 1) {
                    if (depth == -1) {
                        setColor(BLACK);
                    } else {
                        setColor(WHITE_CLOUDS);
                    }
                } else if (dataModel.getPalette() == 2) {
                    if (depth == -1) {
                        setColor(BLACK);
                    } else if (limit < 16) {
                        int r = (depth - 1) / (double) (limit - 1) * 255 + 0.5;
                        int g = 255 - r;
                        int b = ((depth - 1) % (limit / 2)) * 255 / (limit / 2);
                        glColor3f(r / 255., g / 255., b / 255.);
                    } else {
                        int lim = limit < 32 ? limit : 32;
                        int r = (depth - 1) * 255 / lim;
                        int g = ((depth - 1) % (lim / 4)) * 255 / (lim / 4);
                        int b = ((depth - 1) % (lim / 8)) * 255 / (lim / 8);
                        glColor3f(r / 255., g / 255., b / 255.);
                    }
                } else {
                    if (depth == -1) {
                        setColor(BLUE_PETER_RIVER);
                    } else {
                        //glColor3f((double) depth / limit, 1 - (double) depth / limit, 0.8 - (double) depth / limit);
                        glColor3f(BLACK.getR() + BLUE_PETER_RIVER.getR() * (double) depth / limit,
                                  BLACK.getG() + BLUE_PETER_RIVER.getG() * (double) depth / limit,
                                  BLACK.getB() + BLUE_PETER_RIVER.getB() * (double) depth / limit);
                    }
                }

                glVertex2i(x, y);
            }
        }
        glEnd();
    }

    static int divergence_test1(complex<double> c, int limit) {
        complex<double> z = 0;
        for (int i = 1; i <= limit; i++) {
            z = z * z + c;
            if (norm(z) > 4) return i;
        }
        return -1;
    }

    static int divergence_test2(complex<double> c, int limit) {
        complex<double> z = 0;
        for (int i = 1; i <= limit; i++) {
            z = z * z * z + c;
            if (norm(z) > 4) return i;
        }
        return -1;
    }

    static void specialKeyPressed(int key, int, int) {
        switch (key) {
            case GLUT_KEY_RIGHT:
                dataModel.moveRight();
                glutPostRedisplay();
                break;
            case GLUT_KEY_LEFT:
                dataModel.moveLeft();
                glutPostRedisplay();
                break;
            case GLUT_KEY_UP:
                dataModel.moveUp();
                glutPostRedisplay();
                break;
            case GLUT_KEY_DOWN:
                dataModel.moveDown();
                glutPostRedisplay();
                break;
            default:
                break;
        }
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case '1':
                dataModel.setAlgorithm(1);
                glutPostRedisplay();
                break;
            case '2':
                dataModel.setAlgorithm(2);
                glutPostRedisplay();
                break;
            case '3':
                dataModel.decreaseRecursionDepth();
                cout << "Recursion limit decreased. New depth: " << dataModel.getRecursionDepth() << endl;
                glutPostRedisplay();
                break;
            case '4':
                dataModel.increaseRecursionDepth();
                cout << "Recursion limit increased. New depth: " << dataModel.getRecursionDepth() << endl;
                glutPostRedisplay();
                break;
            case 'b':
                dataModel.pickPalette(1);
                cout << "Using \"black&white\" color palette\n";
                glutPostRedisplay();
                break;
            case 'c':
                dataModel.pickPalette(2);
                cout << "Using \"colorful\" color palette\n";
                glutPostRedisplay();
                break;
            case 'v':
                dataModel.pickPalette(3);
                cout << "Using \"blues\" color palette\n";
                glutPostRedisplay();
                break;
            case 'x':
                dataModel.popComplexPlane();
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            case '\x1B':
                dataModel.resetComplexPlane();
                glutPostRedisplay();
                break;
            default:
                break;
        }
    }

    static void mousePressedOrReleased(int button, int state, int x, int y) {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            dataModel.mousePress(x, y);
            glutPostRedisplay();
        }
    }

    static void setColor(Color color) {
        glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
    }
};

#endif //FER_IRG_MANDELBROT_PAINTER_H
