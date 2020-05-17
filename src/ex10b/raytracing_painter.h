//
// Created by m43 on 15. 05. 2020..
//

#ifndef FER_IRG_RAYTRACING_PAINTER_H
#define FER_IRG_RAYTRACING_PAINTER_H


#include <utility>
#include <vector>
#include <GL/glut.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "raytracing_data_model.h"
#include "../utility/utilities.h"
#include "../utility/rayTracing/ray.h"


using namespace std;
using namespace glm;

RayTracingDataModel dataModel(500, 420, 20, 0.0001);

// TODO might be a good idea to write an abstract painter and an abstract data model...

class RayTracingPainter {
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
        auto scene = dataModel.getScene();
        dvec3 screenCorner = scene->view * scene->h - scene->yAxis * scene->b - scene->xAxis * scene->l;

        glBegin(GL_POINTS);
        for (int x = 0; x < dataModel.getWidth(); x++) {
            for (int y = 0; y < dataModel.getHeight(); y++) {
                dvec3 xyRayDirection =
                        screenCorner
                        + scene->xAxis * (scene->l + scene->r) * (double) x / (double) (dataModel.getWidth() - 1)
                        + scene->yAxis * (scene->t + scene->b) * (double) y / (double) (dataModel.getHeight() - 1);
                auto ray = Ray(scene->eye, xyRayDirection);
                dvec3 color = trace(scene, ray, dataModel.getRecursionDepth());
                color = dvec3(std::min(1., color.r), std::min(1., color.g), std::min(1., color.b));
                glColor3f(color.r, color.g, color.b);
                glVertex2i(x, y);
            }
        }
        glEnd();
    }

    static dvec3 trace(const shared_ptr<Scene> &scene, Ray &ray, int depth) {
        if (depth < 0) {
            return dvec3(0, 0, 0);
        }

        auto intersection = findIntersections(scene, ray);
        if (intersection->hasAnyIntersection()) {
            return determineColor(scene, intersection->object, intersection->point, ray, depth);
        } else {
            return scene->gaIntensity;
        }
    }

    static dvec3
    determineColor(const shared_ptr<Scene> &scene, SceneObject *object, dvec3 point, const Ray &ray, int depth) {
        dvec3 n = normalize(object->getNormalInPoint(point));  // normal in point
        bool isFront = dot(n, ray.d) <= 0;
        if (!isFront) {
            n = -n;
        }
        Material material = isFront ? object->frontMat : object->backMat;

        dvec3 color = scene->gaIntensity * material.ambRGB;
        point = point + n * dataModel.getDelta();
        for (const auto &light: scene->sources) {
            dvec3 pointToSource = light->position - point;
            dvec3 l = normalize(pointToSource);  // point to source normalized
            Ray rayToSource = Ray(point + dataModel.getDelta() * l, l);
            auto intersection = findIntersections(scene, rayToSource);
            if (!intersection->hasAnyIntersection() || length(pointToSource) < intersection->lambda) {
                double difCos = dot(n, l);
                auto r = normalize(2. * n * difCos - l);
                color += light->rgb * material.ambRGB * 0.1; // TODO to add this or not to add it?
                color += light->rgb * material.difRGB * std::max(0., difCos);
                color += light->rgb * material.refRGB * pow((dot(-ray.d, r)), material.n);
            }
        }


        auto reflectedRayDirection = normalize(ray.d - 2. * n * dot(n, ray.d));
        Ray reflectedRay = Ray(point + dataModel.getDelta() * reflectedRayDirection, reflectedRayDirection);
        color += material.kref * trace(scene, reflectedRay, depth - 1);
        return color; // * material.kref
    }

    static shared_ptr<Intersection> findIntersections(const shared_ptr<Scene> &scene, Ray &ray) {
        shared_ptr<Intersection> intersection = make_shared<Intersection>();
        for (const auto &o: scene->objects) {
            o->updateIntersection(*intersection, ray);
        }
        return intersection;
    }

    static void keyPressed(unsigned char key, int, int) {
        switch (key) {
            case '1':
                dataModel.decreaseRecursionDepth();
                glutPostRedisplay();
                break;
            case '2':
                dataModel.increaseRecursionDepth();
                glutPostRedisplay();
                break;
            case 'q':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }
};

#endif //FER_IRG_RAYTRACING_PAINTER_H
