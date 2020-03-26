//
// Created by m34 on 16. 03. 2020..
//

#include <iostream>
#include "abstract_vector.h"
#include "abstract_matrix.h"
#include "abstract_vector.cpp"
#include "abstract_matrix.cpp"
#include "i_matrix.h"
#include "i_vector.h"
#include "vector.h"
#include "matrix.h"
#include "vector.cpp"
#include "matrix.cpp"

using namespace std;
using namespace linalg;

class Hero {
public:
    Hero(const string &name) : name_(name) {};

    bool canFly() {
        return name_ == "superman";
    };

    bool canHisFriendFly(Hero &his_friend) {
        return his_friend.canFly();
    };

protected:
    string name_;
};

class SuperMan : public Hero {
public:

    SuperMan() : Hero("superman") {};

    int altitude() {
        return altitude_;
    }

    void goHigher(uint h) {
        altitude_ += h;
    }

private:
    int altitude_ = 0;
};

class VectorArchive {
public:
    explicit VectorArchive(vector<int> &v) : firstArchivedVector(v) {
    }

    void printFirst() {
        for (const int &i: firstArchivedVector) {
            cout << i << " ";
        }
        cout << "\n";
    }

private:
    vector<int> &firstArchivedVector;

};

class MyClass {
public:
    vector<int> elements_;

    MyClass(int number_of_elements) : elements_(vector<int>(number_of_elements)) {
        for (int i = 1; i <= number_of_elements; i++) {
            elements_[i] = i; // just so that the vector is not entirely empty..
        }
    }
};

void printVector(vector<int> *v) {
    cout << "[ ";
    for (const int &i: *v) {
        cout << i << " ";
    }
    cout << "]\n";
}

int main() {

    vector<int> *outsideVectorPointer;

    {
        MyClass maClass(100);
        outsideVectorPointer = &maClass.elements_;

        cout << "Inside" << endl;
        printVector(outsideVectorPointer);
    }

    cout << "Outside 1" << endl;
    printVector(outsideVectorPointer);

    vector<int> vector2(10000); // Vector that might overwrite the original, just to check..

    cout << "Outside 2" << endl;
    printVector(outsideVectorPointer);


    cout << "Demo" << endl;
    cout << "Lets play around a bit" << endl;

    Hero mike = Hero("Mike");
    cout << "This is Mike and Mike is a hero. He " << (mike.canFly() ? "can" : "cannot") << " fly\n";

    SuperMan superman = SuperMan();
    cout << "This is Superman and Superman is also a hero. He " << (superman.canFly() ? "can" : "cannot") << " fly\n";

    cout << "Mike has a friend (superman!) and his friend " << (mike.canHisFriendFly(superman) ? "can" : "cannot")
         << " fly\n";

    int *iptr = new int(3);
    shared_ptr<int> s2;
    {
        shared_ptr<int> s1 = shared_ptr<int>(iptr);
        s2 = shared_ptr<int>(iptr);

        cout << "Inside" << endl;
        cout << "s1 is:" << *s1 << endl;
        cout << "s2 is:" << *s2 << endl;
        cout << endl;
    }

    cout << "Outside" << endl;
    cout << "s1 is now dead" << endl;
    cout << "s2 is:" << *s2 << endl;
    cout << endl;

    vector<int> *maInts;
    VectorArchive *va;
    {
        vector<int> myVector(100);
        myVector.push_back(101);
        myVector[0] = 1;
        maInts = &myVector;
        va = new VectorArchive(myVector);
        myVector[9] = 10;

        cout << "Initial" << endl;
        cout << maInts->size() << endl;
        maInts->push_back(300);
        cout << maInts->at(0) << endl;
        va->printFirst();
        cout << endl;
    }

    cout << "First time" << endl;
    cout << maInts->size() << endl;
    maInts->push_back(300);
    cout << maInts->at(0) << endl;
    va->printFirst();
    cout << endl;

//    int a = 50, b = 50, c = 50, d = 50;
//    vector<int> thisOneMightOverwriteTheOldOne(100);
//    for (int i = 0; i < 100; i++) {
//        thisOneMightOverwriteTheOldOne[i] = i + a + b + c + d;
//    }

    cout << "Second time" << endl;
    cout << maInts->size() << endl;
    maInts->push_back(300);
    cout << maInts->at(0) << endl;
    va->printFirst();
    cout << endl;

    return 0;
}