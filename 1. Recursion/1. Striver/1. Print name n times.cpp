#include <bits/stdc++.h>
using namespace std;

void f(string name, int n){
    if(n == 0){
        return;
    }
    cout << name << endl;
    f(name, n - 1);
}

int main() {
    string name = "abc";
    int n = 3;

    f(name, n);
}