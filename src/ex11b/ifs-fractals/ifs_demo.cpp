//
// Created by m43 on 16. 05. 2020..
//

#include <iostream>
#include <GL/glut.h>
#include "ifs_painter.h"

using namespace std;


int main(int argc, char **argv) {
    cout << "*******************************************" << endl;
    cout << "*************** IFS FRACTALS **************" << endl;
    cout << "*******************************************" << endl;

    cout << "\tPress 1 to decrease depth limit.\n";
    cout << "\tPress 2 to increase depth limit.\n";
    cout << "\tPress 3 to decrease number of points by 10000.\n";
    cout << "\tPress 4 to increase number of points by 10000.\n";
    cout << "\tPress q to quit.\n\n";


    string path;
    if (argc == 2) {
        path = argv[1];
        cout << "Loading configuration from path '" << path << "'" << endl;
    } else {
        cout << "Please enter path to file:\n";
        getline(cin, path);
    }

    auto ifs = make_shared<IfsFractal>(path);
    dataModel = make_shared<IfsDataModel>(600, 600, ifs);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(dataModel->getWidth(), dataModel->getHeight());
    glutInitWindowPosition(1080, 300);
    glutCreateWindow("Exercise 11B - IFS fractals");

    glutDisplayFunc(IfsPainter::display);
    glutReshapeFunc(IfsPainter::reshape);
    glutKeyboardFunc(IfsPainter::keyPressed);
    glutMainLoop();
}