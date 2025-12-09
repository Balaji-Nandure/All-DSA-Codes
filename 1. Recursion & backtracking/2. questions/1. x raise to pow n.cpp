#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long

const int MOD = 1e9 + 7;
const int INF = LLONG_MAX >> 1;

/*
Problem: X raised to the power N
Calculate x raised to the power n (x^n) using recursion.

We need to implement both:
1. Linear approach: O(n) time complexity
2. Logarithmic approach: O(log n) time complexity using binary exponentiation
*/

// Linear approach - O(n) time complexity
int powerLinear(int x, int n) {
    // Base case: any number raised to 0 is 1
    if (n == 0) return 1;
    
    // Recursive case: x^n = x * x^(n-1)
    return x * powerLinear(x, n - 1);
}

// Logarithmic approach - O(log n) time complexity
// Using binary exponentiation (divide and conquer)
int powerLog(int x, int n) {
    // Base case: any number raised to 0 is 1
    if (n == 0) return 1;
    
    // If n is even: x^n = (x^(n/2))^2
    // If n is odd: x^n = x * (x^((n-1)/2))^2
    
    int halfPower = powerLog(x, n / 2);
    int result = halfPower * halfPower;
    
    // If n is odd, multiply by x one more time
    if (n % 2 == 1) {
        result = result * x;
    }
    
    return result;
}




signed main() {
    int x = 2;
    int n = 10;
    
    // Linear approach
    int ansLinear = powerLinear(x, n);
    
    // Logarithmic approach
    int ansLog = powerLog(x, n);

    
    cout << "Linear approach (O(n)):     " << ansLinear << endl;
    cout << "Logarithmic approach (O(log n)): " << ansLog << endl;
    
    return 0;
}

