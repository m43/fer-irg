//
// Created by m34 on 14. 03. 2020..
//

#ifndef FER_IRG_UTILITIES_H
#define FER_IRG_UTILITIES_H

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/geometric.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bits/stdc++.h>
#include <iomanip>
#include <GL/gl.h>

using namespace glm;

namespace ex_utilities {

    std::string pretty_print_matrix(const double *pSource, int rows, int columns) {
        std::ostringstream oss;

        oss << "┌" << std::string(columns * 10 + 2 - 2, ' ') << "┐\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (j != 0) {
                    oss << " ";
                } else {
                    oss << "│";
                }
                oss << std::setw(9) << std::setprecision(2) << pSource[i + j * columns];
                //Note that rows are columns are kept in sequence in memory in GLM's implementation
            }
            oss << " │\n";
        }
        oss << "└" << std::string(columns * 10 + 2 - 2, ' ') << "┘\n";

        return oss.str();
    }

    dvec3 solve_equation_system(dvec3 a, dvec3 b, dvec3 c, dvec3 t) {
        double d = determinant(dmat3(a, b, c));
        double d1 = determinant(dmat3(t, b, c));
        double d2 = determinant(dmat3(a, t, c));
        double d3 = determinant(dmat3(a, b, t));

        double x = d1 / d;
        double y = d2 / d;
        double z = d3 / d;

        return dvec3(x, y, z);
    }

    dvec3 solve_equation_system(dmat3 matrix, dvec3 result) {
        return inverse(matrix) * result;
    }

    std::vector<std::pair<GLint, GLint>> bresenham_line_vertices(GLint xa, GLint ya, GLint xb, GLint yb) {

        std::vector<std::pair<GLint, GLint>> result_vertices = std::vector<std::pair<GLint, GLint>>();

        bool flippedAxes = false;
        if (abs(xb - xa) < abs(yb - ya)) {
            flippedAxes = true;

            GLint temp = xa;
            xa = ya;
            ya = temp;

            temp = xb;
            xb = yb;
            yb = temp;
        }

        if (xb < xa) {
            GLint temp = xa;
            xa = xb;
            xb = temp;

            temp = ya;
            ya = yb;
            yb = temp;
        }

        GLint deltaX = xb - xa;
        GLint deltaY = yb - ya;

        // Floors and stairs are used to avoid floating point calculations - everything is multiplied by deltaX*2 in the end
        GLint stairsPerFloor =
                abs(deltaX) * 2; // number of stairs per floor (not total number of stairs), for example 9*2=18
        GLint numberOfFloors = abs(deltaY); // number of floors, for example 4

        /*
        □□□□□□□□□□□□□□□□□□□□□□□□□
        □□□□□□□□□□□□□□□□■□□□□□□□□
        □□□□□□□□□□□□□□□□■□□□□□□□□
        □□□□□□□□□□□□□□□□■□□□□□□□□
        □□□□□□□□■■■■■■■■■□□□□□□□□
        □□□□□□□□□□□□□□□□□□□□□□□□□
        */

        // If there are 4 floors, you can make 4*2 = 8 stairs at once when going up. That's your walking speed
        GLint walkingSpeed = numberOfFloors * 2;
        // Each step makes "walkingSpeed" stairs and as there are deltaX steps, one makes a total of deltaX * walkingSpeed
        // stairs, which is deltaX*deltaY*2 = 4*9*2 = 72
        // SIDENOTE:
        // The total number of stairs is: 4 floors * 18 stairs per floor gives 72
        // It can also be calculated like this: GLint totalStairs = numberOfFloors * stairsPerFloor;

        GLint currentStairInFloor = stairsPerFloor / 2;
        // One starts off in the middle of the floor, because pixel center is not really a whole number
        // For example:
        //      pixel (3,3) center could correspond to (3.5,3.5)
        //      pixel (0,0) center could correspond to (0.5,0.5)
        // So we put the walking person
        // If the next floor is entered, the currentStairInFloor is reset

        GLint yi = ya; // yi is the current y coordinate of the pixel being drawn
        for (int xi = xa; xi <= xb; xi++) { // xi is the current x coordinate of the pixel being drawn
            if (currentStairInFloor >= stairsPerFloor) { // Not sure whether >= or > should be written
                currentStairInFloor -= stairsPerFloor;
                if (deltaY > 0) {
                    yi += 1;
                } else {
                    yi -= 1;
                }
            }
            currentStairInFloor += walkingSpeed;

            if (!flippedAxes) {
                result_vertices.push_back(std::make_pair(xi, yi));
            } else {
                result_vertices.push_back(std::make_pair(yi, xi));
            }
        }

        return result_vertices;
    }
}

#endif //FER_IRG_UTILITIES_H