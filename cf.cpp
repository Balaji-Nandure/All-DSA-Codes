#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

void pid(int n) {
    // Base case
    if (n == 0) return;

    // Pre-order work → INCREASING PART
    cout << n << " ";  // print n while going DOWN the stack
    pid(n - 1);        // this prints 1 to n-1


    // Post-order work → DECREASING PART
    // print n again while coming UP the stack
    cout << n << " ";
}

signed main() {
    while(true){
        int n = 10;
    }
}