/*
 * Problem: Print Name N Times
 *
 * Basic recursion problem to understand recursion flow.
 * Print a given name exactly N times using recursion.
 *
 * Time: O(n) - we make n recursive calls
 * Space: O(n) - recursion stack depth is n
 */

#include <bits/stdc++.h>
using namespace std;

void f(string name, int n){
    // Base case: when n becomes 0, stop recursion
    if(n == 0){
        return;
    }
    // Print the name first (before recursive call)
    // This ensures we print in the order: name, name, name...
    cout << name << endl;
    // Recursive call with n-1 (moving towards base case)
    f(name, n - 1);
}

int main() {
    string name = "abc";
    int n = 3;

    f(name, n);
}