//
// Created by m43 on 02. 04. 2020..
//

#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> a(3, vector<int>(10, 9));
    vector<vector<int>> b;
    //b = a;
    b = vector<vector<int>>(a);
    b[0][0] = 1;
    b[1][1] = 2;

    cout << "a has [0][0]=" << a[0][0] << " and [0][1]=" << a[0][1] << " and [1][0]=" << a[1][0] << " and [1][1]="
         << a[1][1] << endl;
    cout << "b has [0][0]=" << b[0][0] << " and [0][1]=" << b[0][1] << " and [1][0]=" << b[1][0] << " and [1][1]="
         << b[1][1] << endl;
}