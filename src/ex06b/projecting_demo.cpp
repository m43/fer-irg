//
// Created by m43 on 01. 05. 2020..
//

#include <GL/glut.h>
#include <utility>
#include <math.h>
#include "../utility/utilities.h"
#include "../utility/object_model.h"
#include "projecting_renderer.h"

using namespace std;

/*
/mnt/terra/xoding/fer-irg/src/objects/kocka.obj
/mnt/terra/xoding/fer-irg/src/objects/dragon.obj
/mnt/terra/xoding/fer-irg/src/objects/bird.obj
 */

void demo(int argc, char **argv, void (*reshape)(int, int), void (*display)()) {
    cout << "**********************************************" << endl;
    cout << "*************** PROJECTING DEMO **************" << endl;
    cout << "**********************************************" << endl;

    string path;
    if (argc == 2) {
        path = argv[1];
    } else {
        cout << "Please enter path to file:\n";
        getline(cin, path);
    }

    cout << "Loading file \"" << path << "\"...\n";
    shared_ptr<ObjectModel> om = ObjectModel::loadFromFile(path);
    cout << "File loaded. Found " << om->getVertices().size() << " vertices and " << om->getFaces().size()
         << " faces.\n";

    auto n_result = om->normalize();
    cout << "Object normalization performed." << endl;
    printf("xmin: %f\nxmax: %f\nymin: %f\nymax: %f\nzmin: %f\nzmax: %f\n", n_result.xmin_, n_result.xmax_,
           n_result.ymin_,
           n_result.ymax_, n_result.zmin_, n_result.zmax_);
    cout << "Scaling factor " << n_result.scalingFactor_ << endl;
    printf("Object center: (%f,%f,%f)\n\n", n_result.center_.x, n_result.center_.y, n_result.center_.z);

    printf("USAGE INSTRUCTIONS:\n");
    printf(" Press 1/2/3/4 to pick drawing algorithm (if available)\n");
    printf(" Press 'f' to turn on fill (if available)\n");
    printf(" Press 'r' or 'l' to rotate the object right or left\n");
    printf(" Press 'q' or ESC to quit\n");


    dataModel.setObjectModel(move(om));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(540, 240);
    glutCreateWindow("m43");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(Painter::keyPressed);

    glutMainLoop();
}
