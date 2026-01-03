/*
Problem:
Print numbers from 1 to N and then from N to 1 using recursion.

Input:  n = 5
Output: 
1 2 3 4 5 
5 4 3 2 1

Approach:
- Use recursion to first print from 1 to n (increasing order).
- Use recursion to print from n to 1 (decreasing order).
*/

#include <iostream>
using namespace std;

void printIncreasing(int n) {
    if (n == 0) return;
    printIncreasing(n - 1);
    cout << n << " ";
}

void printDecreasing(int n) {
    if (n == 0) return;
    cout << n << " ";
    printDecreasing(n - 1);
}