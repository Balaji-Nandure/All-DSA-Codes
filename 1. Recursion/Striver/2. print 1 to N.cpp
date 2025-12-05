#include <bits/stdc++.h>
using namespace std;

void f(int n){
    if(n == 0) return;
    // first print upto n-1 and then print n
    f(n - 1);
    cout << n << endl;
}

signed main() {
    int n = 5;
    f(n);
    return 0;
}