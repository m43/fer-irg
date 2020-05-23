//
// Created by m43 on 14. 05. 2020..
//

#ifndef FER_IRG_SCENE_H
#define FER_IRG_SCENE_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <bits/stdc++.h>
#include <iomanip>
#include <math.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "material.h"
#include "light.h"
#include "scene_object.h"
#include "patch.h"
#include "sphere.h"

using namespace std;
using namespace glm;

namespace raytracing {

    class Scene {
    public:
        Scene(const dvec3 &eye, const dvec3 &view, const dvec3 &viewUp,
              double h, double xAngle, double yAngle, const dvec3 &gaIntensity,
              const vector<shared_ptr<Light>> &sources, const vector<shared_ptr<SceneObject>> &objects)
                : eye(eye), view(view), viewUp(viewUp), h(h), xAngle(xAngle), yAngle(yAngle), gaIntensity(gaIntensity),
                  sources(sources), objects(objects) {
            normalizeAndComputeKS();
        }

        dvec3 eye;
        dvec3 view;
        dvec3 viewUp;
        double h;
        double xAngle;
        double yAngle;
        dvec3 gaIntensity = dvec3(0, 0, 0);

        dvec3 xAxis;
        dvec3 yAxis;
        double l;
        double r;
        double t;
        double b;

        vector<shared_ptr<Light>> sources;
        vector<shared_ptr<SceneObject>> objects;

        void addLightSource(const shared_ptr<Light> light) {
            sources.push_back(light); // TODO check
        }

        void addSceneObject(const shared_ptr<SceneObject> object) {
            objects.push_back(object); // TODO check
        }


        static shared_ptr<Scene> loadScene(string path);

    private:
        void normalizeAndComputeKS() {
            view = normalize(view);
            viewUp = normalize(viewUp);
            // TODO check if viewup and view vectors are parallel
            xAxis = normalize(cross(view, viewUp));
            yAxis = normalize(cross(xAxis, view));  // TODO normalize should not be necessary here. check
            l = r = h * tan(xAngle / 2 * M_PIf32 / 180);
            t = b = h * tan(yAngle / 2 * M_PIf32 / 180);
        }
    };

    shared_ptr<Scene> Scene::loadScene(string path) {
        ifstream infile(path);
        if (!infile) {
            throw invalid_argument("Nothing here. " + path);
        }

        dvec3 eye;
        dvec3 view;
        dvec3 viewUp;
        double h;
        double xa;
        double ya;
        dvec3 ga;
        auto lights = vector<shared_ptr<Light>>();
        auto objects = vector<shared_ptr<SceneObject>>();

        bool eyeFound = false;
        bool viewFound = false;
        bool viewUpFound = false;
        bool hFound = false;
        bool xaFound = false;
        bool yaFound = false;
        bool gaFound = false;

        string line;
        while (getline(infile, line)) {
            line.erase(find_if(line.rbegin(), line.rend(), [](int ch) {
                return !isspace(ch);
            }).base(), line.end());

            if (line.size() == 0) {
                continue;
            }

            istringstream iss(line);
            char ch;

            iss >> ch;
            switch (ch) {
                case '#': {
                    break;
                }
                case 'e': {
                    if (eyeFound) {
                        throw invalid_argument("Eye already defined. Redefined here: '" + line + "'");
                    }
                    eyeFound = true;
                    if (!(iss >> eye.x >> eye.y >> eye.z)) {
                        throw invalid_argument(
                                "Each line starting with char e should have 3 doubles. Line: '" + line + "'");
                    }
                    break;
                }
                case 'v': {
                    iss >> noskipws >> ch >> skipws;

                    if (ch == 'u') {
                        if (viewUpFound) {
                            throw invalid_argument("View up already defined. Line: '" + line + "'");
                        }
                        viewUpFound = true;
                        if (!(iss >> viewUp.x >> viewUp.y >> viewUp.z)) {
                            throw invalid_argument(
                                    "Each line starting with char v should have 3 doubles. Line: '" + line + "'");
                        }
                    } else {
                        if (viewFound) {
                            throw invalid_argument("View already defined. Line: '" + line + "'");
                        }
                        viewFound = true;
                        if (!(iss >> view.x >> view.y >> view.z)) {
                            throw invalid_argument(
                                    "Each line starting with 'vu' should have 3 doubles. Line: '" + line + "'");
                        }
                    }
                    break;
                }
                case 'h': {
                    if (hFound) {
                        throw invalid_argument("'H' already defined. Line: '" + line + "'");
                    }
                    hFound = true;
                    if (!(iss >> h)) {
                        throw invalid_argument(
                                "Each line starting with char h should have 1 double. Line: '" + line + "'");
                    }
                    break;
                }
                case 'x': {
                    iss >> ch;
                    if (ch != 'a') {
                        throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                    }
                    if (xaFound) {
                        throw invalid_argument("'xa' already defined. Line: '" + line + "'");
                    }
                    xaFound = true;
                    if (!(iss >> xa)) {
                        throw invalid_argument(
                                "Each line starting with 'xa' should have 1 double. Line: '" + line + "'");
                    }
                    break;
                }
                case 'y': {
                    iss >> noskipws >> ch >> skipws;
                    if (ch != 'a') {
                        throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                    }
                    if (yaFound) {
                        throw invalid_argument("'ya' already defined in. Line: '" + line + "'");
                    }
                    yaFound = true;
                    if (!(iss >> ya)) {
                        throw invalid_argument(
                                "Each line starting with 'ya' should have 1 double. Line: '" + line + "'");
                    }
                    break;
                }
                case 'g': {
                    iss >> noskipws >> ch >> skipws;
                    if (ch != 'a') {
                        throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                    }
                    if (gaFound) {
                        throw invalid_argument("'ga' already defined in. Line: '" + line + "'");
                    }
                    gaFound = true;
                    if (!(iss >> ga.x >> ga.y >> ga.z)) {
                        throw invalid_argument(
                                "Each line starting with 'ga' should have 3 doubles. Line: '" + line + "'");
                    }
                    break;
                }
                case 'i': {
                    dvec3 position;
                    dvec3 color;
                    if (!(iss >> position.x >> position.y >> position.z >> color.r >> color.g >> color.b)) {
                        throw invalid_argument("Each line starting with char i should have 6 doubles. Line: '" + line
                                               + "'");
                    }
                    lights.emplace_back(make_shared<Light>(dvec3(position.x, position.y, position.z), color));
                    break;
                }
                case 'o': {
                    iss >> ch;
                    if (ch == 's') {
                        // sphere: cx cy cz r ar ag ab dr dg db rr rg rb n kref
                        double cx, cy, cz, r, ar, ag, ab, dr, dg, db, rr, rg, rb, n, kref;
                        if (!(iss >> cx >> cy >> cz >> r
                                  >> ar >> ag >> ab
                                  >> dr >> dg >> db
                                  >> rr >> rg >> rb
                                  >> n >> kref)) {
                            throw invalid_argument("Invalid sphere definition. Line: '" + line + "'");
                        }
                        objects.push_back(
                                make_shared<Sphere>(
                                        Material(ar, ag, ab, dr, dg, db, rr, rg, rb, n, kref),
                                        dvec3(cx, cy, cz), r));
                    } else if (ch == 'p') {
                        double cx, cy, cz, v1x, v1y, v1z, v2x, v2y, v2z, wi, he, ar, ag, ab, dr, dg, db, rr, rg, rb, n, kref, ar2, ag2, ab2, dr2, dg2, db2, rr2, rg2, rb2, n2, kref2;
                        if (!(iss >> cx >> cy >> cz >> v1x >> v1y >> v1z >> v2x >> v2y >> v2z >> wi >> he
                                  >> ar >> ag >> ab
                                  >> dr >> dg >> db
                                  >> rr >> rg >> rb
                                  >> n >> kref
                                  >> ar2 >> ag2 >> ab2
                                  >> dr2 >> dg2 >> db2
                                  >> rr2 >> rg2 >> rb2
                                  >> n2 >> kref2
                        )) {
                            throw invalid_argument("Invalid patch definition. Line: '" + line + "'");
                        }
                        objects.push_back(make_shared<Patch>(
                                Material(ar, ag, ab, dr, dg, db, rr, rg, rb, n, kref),
                                Material(ar2, ag2, ab2, dr2, dg2, db2, rr2, rg2, rb2, n2, kref2),
                                dvec3(cx, cy, cz),
                                dvec3(v1x, v1y, v1z),
                                dvec3(v2x, v2y, v2z),
                                wi, he
                        ));
                    } else {
                        throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                    }
                    break;
                }
                default: {
                    throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                    break;
                }
            }
        }
        infile.close();

        if (!(eyeFound && viewFound && viewUpFound && hFound && xaFound && yaFound && gaFound)) {
            throw invalid_argument("Definition not complete, scene cannot be loaded.");
        }

        return make_shared<Scene>(eye, view, viewUp, h, xa, ya, ga, lights, objects);
    }

}
#endif //FER_IRG_SCENE_H
