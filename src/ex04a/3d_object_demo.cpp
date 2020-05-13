//
// Created by m43 on 05. 04. 2020..
//

#include <GL/glut.h>
#include <utility>
#include "../utility/utilities.h"
#include "../utility/object_model.h"
#include "3d_object_renderer.h"

using namespace std;

/*
/mnt/terra/xoding/fer-irg/src/objects/kocka.obj
0 0 0
-0.25 -0.25 -0.25
0.62 -0.71 0.89
0.99 0.99 0.99
-0.99 -0.99 -0.99
0.99 0.99 -0.99
0 -1 -1
-1 -1 -1
1 1 1
-0.3 0.9 0.3
0.3 0.9 -0.3
2 2 2
3 3 3
-2 -2 -2
-2 2 -2
-1.1 -1.1 -1.1
1 1 1.0001
1 1 1.0000001
quit

/mnt/terra/xoding/fer-irg/src/objects/dragon.obj
0.3 0.3 0.3
quit


/mnt/terra/xoding/fer-irg/src/objects/bird.obj
0.3 0.3 0.3
quit
 */

int main(int argc, char **argv) {
    cout << "**********************************************" << endl;
    cout << "************** OBJECT MODEL DEMO *************" << endl;
    cout << "**********************************************" << endl;


    cout << "Please enter path to file:\n";
    string line;
    getline(cin, line);
    cout << "Loading file \"" << line << "\"...\n";
    shared_ptr<ObjectModel> om = ObjectModel::loadFromFile(line);
    cout << "File loaded. Found " << om->getVertices().size() << " vertices and " << om->getFaces().size()
         << " faces.\n";

    auto n_result = om->normalize();
    cout << "Object normalization performed." << endl;
    printf("xmin: %f\nxmax: %f\nymin: %f\nymax: %f\nzmin: %f\nzmax: %f\n", n_result.xmin_, n_result.xmax_,
           n_result.ymin_,
           n_result.ymax_, n_result.zmin_, n_result.zmax_);
    cout << "Scaling factor " << n_result.scalingFactor_ << endl;
    printf("Object center: (%f,%f,%f)\n\n", n_result.center_.x, n_result.center_.y, n_result.center_.z);

    cout << "**********************************************" << endl;
    cout << "**************** LINE TESTING ****************" << endl;
    cout << "**********************************************" << endl;

    cout << "NOTE: This program assumes that the user wants to enter a test point in the "
            "coordinate system that is the result of all the transformations applied to "
            "the orginal object (aka after translating and scaling)." << endl << endl;

    cout << "Please specify the coordinates of the test point as three numbers seperated by spaces"
            "(all in range [-1,1]) or just enter \'q\' (followed by an enter) to continue to OpenGL:" << endl;

    while (true) {

        getline(cin, line);
        if (*line.c_str() == 'q') {
            break;
        }

        dvec3 test_point;
        istringstream iss(line);
        iss >> test_point.x >> test_point.y >> test_point.z;
        printf("The testing point (%f, %f, %f) is ***%s*** of object\n", test_point.x, test_point.y, test_point.z,
               om->testIfPointInsideAfterTransformation(test_point) ? "INSIDE" : "OUTSIDE");
    }

    // om->dumpToObj(line + ".BACKUP.obj"); // Save the model to a file aka dump
    dataModel.setObjectModel(move(om));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(dataModel.getWidth(), dataModel.getHeight());
    glutInitWindowPosition(540, 240);
    glutCreateWindow("Exercise 4A");
    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(Painter::display);
    glutReshapeFunc(Painter::reshape);
    glutKeyboardFunc(Painter::keyPressed);
    glutMouseFunc(Painter::mousePressedOrReleased);
    glutMotionFunc(Painter::mouseMovedOrDragged);
    glutPassiveMotionFunc(Painter::mouseMovedOrDragged);
    glutSpecialFunc(Painter::specialKeyPressed);

    glutMainLoop();
}
