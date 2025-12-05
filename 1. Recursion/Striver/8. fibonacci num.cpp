// multiple recursive calls starts here
#include <bits/stdc++.h>
using namespace std;

int fib_counter = 0;

int fibonacci(int n) {
    fib_counter++;
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    int n = 1000;
    cout << fibonacci(n) << endl;
    cout << "count: " << fib_counter << endl;
    return 0;
}