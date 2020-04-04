//
// Created by m43 on 27. 03. 2020..
//

#include <iostream>

using namespace std;

// example code from https://itanium-cxx-abi.github.io/cxx-abi/cxx-vtable-ex.html
// but I tweeked some stuff..

void my_print(string s){
    cout << s << endl;
}

struct A {
    virtual void f () { my_print("fA");}
    virtual void g () { my_print("gA");};
    void h () { my_print("hA");};
    int ia = 0;
};

struct B: public virtual A {
    void f () override { my_print("fB");};
    static void h () { my_print("hB");};
    int ib = 1;
};

struct C: public virtual A {
    void g () override { my_print("gC");};
    void h () { my_print("hC");};
    int ic = 2;
};

struct D: public B, public C {
    int id = 3;
    void h () { my_print("hD");};
};

int main() {
    D d{};

    // Init the pointers
    D *pd = &d;

    A *pa_in_d = pd;
    B *pb_in_d = pd;
    C *pc_in_d = pd;

    A *pa_in_b_in_d = pb_in_d;
    A *pa_in_c_in_d = pc_in_d;

    // Calling the functions
    pd->f();
    pd->g();
    pd->h();

    pa_in_d->f();
    pa_in_d->g();
    pa_in_d->h();

    pb_in_d->f();
    pb_in_d->g();
    pb_in_d->h();

    pc_in_d->f();
    pc_in_d->g();
    pc_in_d->h();

    pa_in_b_in_d->f();
    pa_in_b_in_d->g();
    pa_in_b_in_d->h();
    pa_in_c_in_d->f();
    pa_in_c_in_d->g();
    pa_in_c_in_d->h();

    cout << pd << endl;
    return 0;
}