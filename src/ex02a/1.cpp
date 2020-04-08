//
// Created by m34 on 14. 03. 2020..
//

#include <iostream>
#include "../utility/utilities.h"

//Include OpenGL header files, so that we can use OpenGL
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else

#include <GL/glut.h> // though, in the laboratory exercise, using freeglut is instructed
//#include <GL/freeglut.h>

#endif

#define VK_ESCAPE 0x1B // ESC key

using namespace std;
using namespace glm;
using namespace ex_utilities;

//*********************************************************************************
//	Start point (Lx[1],Ly[1]) and end point (Lx[2],Ly[2]) of line.
//	Ix - current state (whether 1 or 2 points are currently given)
//*********************************************************************************

GLdouble Lx[2], Ly[2];
GLint Ix;

//*********************************************************************************
//	Main window pointer and starting window size
//*********************************************************************************

GLuint window;
GLuint width = 1280, height = 720;

//*********************************************************************************
//	Function Prototypes.
//*********************************************************************************

void drawScene();

void handleResize(int width, int height);

void handleMouse(int button, int state, int x, int y);

void handleKeypress(unsigned char theKey, int mouseX, int mouseY);

void myLine(GLint xa, GLint ya, GLint xb, GLint yb);

//*********************************************************************************
//	Main program.
//*********************************************************************************

int main(int argc, char **argv) {

    //Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 720); //Set the window size
    glutInitWindowPosition(100, 100);
    glutInit(&argc, argv);

    //Create the window
    window = glutCreateWindow("ex2 - Drawing a line");

    //Set handler functions for drawing, window resize, keypress and mouse movement
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);

    cout << "By using the mouse, pick two points to draw a line\n";
    cout << "To change color, press r, g, or k.\n";

    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
}

//*********************************************************************************
//	Called when the window is resized
//*********************************************************************************

void handleResize(int w, int h) {
    width = w;
    height = h;
    Ix = 0;

    glViewport(0, 0, width, height); // place the viewport

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glColor3f(0.0f, 0.0f, 0.0f);
}

//*********************************************************************************
//	Function called whenever the window must be redrawn
//*********************************************************************************

void drawScene() {
    //glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //background color
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clearing display after last draw
    glFlush();
}

//*********************************************************************************
//	Called to draw a line
//*********************************************************************************

void myLine(GLint xa, GLint ya, GLint xb, GLint yb) {

    // Save the current color
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    glBegin(GL_LINES);
    {
        // Change the color to red and draw the line
        glColor3f(1, 0, 0);
        glVertex2i(xa, ya);
        glVertex2i(xb, yb);

        glVertex2i(xa, ya + 5);
        glVertex2i(xb, yb + 5);
    }
    glEnd();

    // Bring back the original color
    glColor3f(currentColor[0], currentColor[1], currentColor[2]);


    glBegin(GL_POINTS);
    {
        for (pair<GLint, GLint> vertex: bresenham_line_vertices(xa, ya, xb, yb)) {
            glVertex2i(vertex.first, vertex.second);
        }
    }
    glEnd();
}

//*********************************************************************************
//	Called when a key is pressed
//*********************************************************************************

void handleKeypress(unsigned char key, //The key that was pressed
                    int, int) {    //The current mouse coordinates
    switch (tolower(key)) {
        case VK_ESCAPE: //Escape key
            exit(0); //Exit the program
            break;

        case 'r':
            glColor3f(1, 0, 0);
            break;

        case 'g':
            glColor3f(0, 1, 0);
            break;

        case 'b':
            glColor3f(0, 0, 1);
            break;

        case 'k':
            glColor3f(0, 0, 0);
            break;
        default:
            return;
    }

    glRecti(width - 15, height - 15, width, height);
    glFlush();
}

//*********************************************************************************
//	Called when mouse events happen
//*********************************************************************************

void handleMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        //Left mouse button picks the points for the line being drawn

        Lx[Ix] = x;
        Ly[Ix] = height - y;
        Ix = Ix ^ 1;

        if (Ix == 0) {
            // Draw the line if second point picked
            myLine((int) Lx[0], (int) Ly[0], (int) Lx[1], (int) Ly[1]);
        } else {
            // Draw the vertex of the first point
            glVertex2i(x, height - y);
        }

        printf("Point %d: %d %d \n", Ix ^ 1, x, y);
        glFlush();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        //Right mouse button clears the display
        handleResize(width, height);
        printf("Display cleared\n");
    }
}

