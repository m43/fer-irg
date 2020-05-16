//
// Created by m43 on 14. 05. 2020..
//

#include <GL/glut.h>
#include "raytracing_painter.h"
#include "../utility/rayTracing/scene.h"

using namespace std;
using namespace raytracing;

int main(int argc, char **argv) {
    cout << "**********************************************" << endl;
    cout << "*************** RAYTRACING DEMO **************" << endl;
    cout << "**********************************************" << endl;

    string path;
    if (argc == 2) {
        path = argv[1];
    } else {
        cout << "Please enter path to file:\n";
        getline(cin, path);
    }
    dataModel.setScene(Scene::loadScene(path));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(1080,300);
    glutCreateWindow("Exercise 8B");

    glutDisplayFunc(RayTracingPainter::display);
    glutReshapeFunc(RayTracingPainter::reshape);
    glutKeyboardFunc(RayTracingPainter::keyPressed);

    glutMainLoop();
}