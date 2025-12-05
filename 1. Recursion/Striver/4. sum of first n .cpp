#include <bits/stdc++.h>
using namespace std;


int f(int n){
    if(n == 0) return 0;
    return n + f(n - 1);
}


signed main() {
    int n = 5;
    int sum = f(n); // which returns the sum of first n numbers;
    cout << "Sum of first " << n << " numbers is " << sum << endl;
    return 0;
}