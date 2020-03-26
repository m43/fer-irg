//
// Created by m43 on 16. 03. 2020..
//

#include <memory>
#include <regex>
#include "vector.h"

using namespace std;
using namespace linalg;

Vector::Vector(const vector<double> &values) {
    elements_ = make_shared<vector<double>>(values);
    dimension_ = values.size();
}

Vector::Vector(size_t dimensions) {
    elements_ = make_shared<vector<double>>(dimensions);
    dimension_ = dimensions;
}

Vector::Vector(bool readOnly, const vector<double> &values) {
    readOnly_ = readOnly;
    dimension_ = values.size();
    elements_ = make_shared<vector<double>>(values);
}

Vector::Vector(bool readOnly, const shared_ptr<vector<double>> &values_ptr) {
    readOnly_ = readOnly;
    dimension_ = values_ptr->size();
    elements_ = shared_ptr<vector<double>>(values_ptr);
    // TODO is there any way this could go wrong?
    //      Like can the original smart pointer in any way be destroyed?
    //      The thing that I dont understand: where is the shared
    //      pointer that I create on this line stored and where is the
    //      original shared smart pointer stored
    // My humble opinion is that nothing could go wrong :)
    // But Murphy probably disagrees..
}

// TODO Having &values would not work, right? What if the original values get auto deleted or something like that,
//      but this vector still has the reference to that dead vector? (dangling pointers)
//Vector::Vector(bool readOnly, bool pointToGivenValues, vector<double> &values) {
//    // TODO is this signature OK? should i maybe use "bool &readOnly"?
//    readOnly_ = readOnly;
//    elements_ = pointToGivenValues ? values : vector<double>(values);
//    dimension_ = values.size();
//}

Vector::~Vector() = default;


double Vector::get(int index) {
    throwIfIndexInvalidRange(index);
    return (*elements_)[index];
}

Vector &Vector::set(int index, double value) {
    if (readOnly_)
        throw logic_error("This vector is read only and cannot be changed");

    throwIfIndexInvalidRange(index);
    (*elements_)[index] = value;
    return *this;
}

int Vector::getDimension() {
    return (*elements_).size();
}

unique_ptr<IVector> Vector::clone() {
    // TODO does copying change read only property?
    return make_unique<Vector>(*elements_);
}

unique_ptr<IVector> Vector::newInstance(int dimension) {
    return make_unique<Vector>(vector<double>(dimension, 0));
}

unique_ptr<Vector> Vector::parseSimple(string str) {

    vector<double> values = vector<double>();

    std::istringstream iss(str);
    for (std::string s; iss >> s;)
        values.push_back(stod(s));

    return make_unique<Vector>(values);
}
