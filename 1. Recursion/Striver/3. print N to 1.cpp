#include <bits/stdc++.h>
using namespace std;

void f(int n){
    if(n == 0) return;
    // first print n and then print upto n-1
    cout << n << endl;
    f(n - 1);
}

signed main() {
    int n = 5;
    f(n);
    return 0;
}
