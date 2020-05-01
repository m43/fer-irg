//
// Created by m43 on 05. 04. 2020..
//

#ifndef FER_IRG_OBJECT_MODEL_H
#define FER_IRG_OBJECT_MODEL_H

#include <fstream>
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <math.h>

using namespace std;
using namespace glm;

class ObjectModelNormalizationResults {
public:
    double xmin_, xmax_, ymin_, ymax_, zmin_, zmax_;
    vector<dvec4> planes_;
    double scalingFactor_;
    dvec3 center_;
};

class ObjectModel {
public:
    ObjectModel() {}

    ObjectModel(const vector<dvec3> &vertices, const vector<ivec3> &faces) : vertices_(vertices), faces_(faces) {}

    ObjectModel(int numberOfVerticesToAllocate, int numberOfFacesToAllocate) {
        vertices_.reserve(numberOfVerticesToAllocate);
        faces_.reserve(numberOfFacesToAllocate);
    }

    void dumpToObj(string path);

    const ObjectModelNormalizationResults &normalize();

    void addVertex(dvec3 v) {
        normalized_ = false;
        vertices_.emplace_back(v);
    }

    void addFace(ivec3 f) {
        normalized_ = false;
        for (int i = 2; i >= 0; i--) {
            if (f[i] > (int) vertices_.size()) {
                throw invalid_argument("Cannot add face with index of vertex that has not been added yet.");
            }
        }
        faces_.emplace_back(f);
    }

    const vector<dvec3> &getVertices() const {
        return vertices_;
    }

    const vector<ivec3> &getFaces() const {
        return faces_;
    }

    static shared_ptr<ObjectModel> loadFromFile(string path);

    shared_ptr<ObjectModel> copy() {
        return make_shared<ObjectModel>(vertices_, faces_);
    }

    bool testIfPointInsideAfterTransformation(dvec3 test_point);

private:
    vector<dvec3> vertices_;
    vector<ivec3> faces_;
    bool normalized_;
    ObjectModelNormalizationResults normalizationResults_;
};

tuple<int, int, int> readNumberOfLines(string path) {
    ifstream infile(path);
    if (!infile) {
        throw invalid_argument("Nothing here.");
    }

    string line;
    int commentsNumber = 0, verticesNumber = 0, facesNumber = 0;
    while (getline(infile, line)) {
        istringstream iss(line);
        char ch;

        iss >> ch;
        switch (ch) {
            case '#': {
                commentsNumber++;
                break;
            }
            case 'v': {
                verticesNumber++;
                break;
            }
            case 'f': {
                facesNumber++;
                break;
            }
            default: {
                break;
            }
        }
    }

    infile.close();
    return make_tuple(commentsNumber, verticesNumber, facesNumber);
}

shared_ptr<ObjectModel> ObjectModel::loadFromFile(string path) {
    tuple<int, int, int> lines = readNumberOfLines(path);
    shared_ptr<ObjectModel> om = make_shared<ObjectModel>(get<1>(lines), get<2>(lines));

    ifstream infile(path);
    if (!infile) {
        throw invalid_argument("Nothing here.");
    }

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
            case 'v': {
                dvec3 v;
                if (!(iss >> v.x >> v.y >> v.z)) {
                    throw invalid_argument("Each line starting with char v should have 3 double indexes");
                }
                om->addVertex(v);
                break;
            }
            case 'f': {
                ivec3 face;
                if (iss >> face.x >> face.y >> face.z) {
                    face.x--;
                    face.y--;
                    face.z--;
                } else {
                    throw invalid_argument("Each line starting with char f should have 3 integer indexes");
                }
                om->addFace(face);
                break;
            }
            default: {
                throw invalid_argument("Problem while parsing line: \"" + line + "\"");
                break;
            }
        }
    }

    infile.close();
    return om;
}

const ObjectModelNormalizationResults &ObjectModel::normalize() {
    if (normalized_) {
        return normalizationResults_;
    }

    normalizationResults_ = ObjectModelNormalizationResults();
    normalizationResults_.planes_.reserve(faces_.size());

    auto v0 = vertices_.back();
    normalizationResults_.xmin_ = normalizationResults_.xmax_ = v0.x;
    normalizationResults_.ymin_ = normalizationResults_.ymax_ = v0.y;
    normalizationResults_.zmin_ = normalizationResults_.zmax_ = v0.z;


    for (auto v: vertices_) {
        normalizationResults_.xmin_ = std::min(normalizationResults_.xmin_, v.x);
        normalizationResults_.xmax_ = std::max(normalizationResults_.xmax_, v.x);
        normalizationResults_.ymin_ = std::min(normalizationResults_.ymin_, v.y);
        normalizationResults_.ymax_ = std::max(normalizationResults_.ymax_, v.y);
        normalizationResults_.zmin_ = std::min(normalizationResults_.zmin_, v.z);
        normalizationResults_.zmax_ = std::max(normalizationResults_.zmax_, v.z);
    }

    double deltaX = normalizationResults_.xmax_ - normalizationResults_.xmin_;
    double deltaY = normalizationResults_.ymax_ - normalizationResults_.ymin_;
    double deltaZ = normalizationResults_.zmax_ - normalizationResults_.zmin_;

    normalizationResults_.center_ = dvec3(normalizationResults_.xmin_ + deltaX / 2,
                                          normalizationResults_.ymin_ + deltaY / 2,
                                          normalizationResults_.zmin_ + deltaZ / 2);
    normalizationResults_.scalingFactor_ = 2 / std::max(deltaX, std::max(deltaY, deltaZ));

    for (auto f: faces_) {
        auto v1 = vertices_[f.x];
        auto v2 = vertices_[f.y];
        auto v3 = vertices_[f.z];

        dvec4 plane;

        plane.x = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
        plane.y = -(v2.x - v1.x) * (v3.z - v1.z) + (v2.z - v1.z) * (v3.x - v1.x);
        plane.z = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
        plane.w = -v1.x * plane.x - v1.y * plane.y - v1.z * plane.z;

        normalizationResults_.planes_.push_back(plane);
    }

    return normalizationResults_;
}

void ObjectModel::dumpToObj(string path) {
    ofstream outfile(path);
    for (auto v: vertices_) {
        outfile << "v " << v.x << " " << v.y << " " << v.z << "\n";
    }
    for (auto f: faces_) {
        outfile << "f " << f.x + 1 << " " << f.y + 1 << " " << f.z + 1 << "\n";

    }
    outfile.close();
}

bool ObjectModel::testIfPointInsideAfterTransformation(dvec3 test_point) {
    auto n_result = normalize();

    test_point /= n_result.scalingFactor_;
    test_point += n_result.center_;

    for (auto plane: n_result.planes_) {
        double r = plane.x * test_point.x + plane.y * test_point.y + plane.z * test_point.z + plane.w;
        if (r > 0) return false;
    }

    return true;
}

#endif //FER_IRG_OBJECT_MODEL_H
