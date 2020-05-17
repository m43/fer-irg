//
// Created by m43 on 17. 05. 2020..
//

#ifndef FER_IRG_IFS_PAINTER_H
#define FER_IRG_IFS_PAINTER_H

#include <iostream>
#include <complex>
#include <utility>
#include <vector>
#include <random>
#include <cmath>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "../../utility/utilities.h"
#include "../../utility/color.h"
#include "ifs_data_model.h"


using namespace std;
using namespace glm;

shared_ptr<IfsDataModel> dataModel;

class IfsPainter {
public:
    static void display() {
        setColor(BLACK);
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
        renderDataModel();
        glutSwapBuffers();
    }

    static void reshape(int width, int height) {
        dataModel->setHeight(height);
        dataModel->setWidth(width);

        glDisable(GL_DEPTH_TEST);
        glViewport(0, 0, (GLsizei) width, (GLsizei) height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, width, 0, height);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    static void renderDataModel() {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, 1);
        auto ifs = dataModel->getIfs();

        glBegin(GL_POINTS);
        setColor(BLUE_PETER_RIVER);
        for (int i = 0; i < ifs->n; i++) {
            double x = 0;
            double y = 0;
            for (int j = 0; j < ifs->depth; j++) {
                double randomNumber = dist(mt);
                for (const auto &row: ifs->functionRows) {
                    if (randomNumber >= row.pi) {
                        randomNumber -= row.pi;
                    } else {
                        double newX = row.a * x + row.b * y + row.e;
                        double newY = row.c * x + row.d * y + row.f;
                        x = newX;
                        y = newY;
                        break;
                    }
                }
            }
            x = x * ifs->eta1 + ifs->eta2;
            y = y * ifs->eta3 + ifs->eta4;
            glVertex2i((int) x, (int) y);
        }
        glEnd();
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case '1':
                dataModel->decreaseRecursionDepth();
                cout << "Depth: " << dataModel->getIfs()->depth << endl;
                glutPostRedisplay();
                break;
            case '2':
                dataModel->increaseRecursionDepth();
                cout << "Depth: " << dataModel->getIfs()->depth << endl;
                glutPostRedisplay();
                break;
            case '3':
                dataModel->decreaseNumberOfPoints(10000);
                cout << "Number of points: " << dataModel->getIfs()->n << endl;
                glutPostRedisplay();
                break;
            case '4':
                dataModel->increaseNumberOfPoints(10000);
                cout << "Number of points: " << dataModel->getIfs()->n << endl;
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
};

#endif //FER_IRG_IFS_PAINTER_H
