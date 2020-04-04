//
// Created by m43 on 27. 03. 2020..
//

#include <iostream>

using namespace std;


void my_print(string s) {
    cout << s << endl;
}

class B {
public:
    void f() { my_print("f_B"); };
    void f(int i) { my_print("f_B_int"); };
};

class D : public B {
public:
    void f() { my_print("f_D"); };
};


int main() {

    cout << "Hiding nonvirtual functions" << endl;

    B *bp = new D;
    bp->f(); // calls f_B, eventhough D did override that method, but the function was nonvirtual
    bp->f(123);

    D *dp = new D;
    dp->f();
    //dp->f(123); // error!

    return 0;
}