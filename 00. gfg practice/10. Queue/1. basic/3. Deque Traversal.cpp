/*
Problem: Deque Traversal

GFG: https://www.geeksforgeeks.org/problems/deque-traversal/1

Description:
Given a deque dq containing integer elements, traverse the dq and print
its elements separated by space. Print a newline at the end.

Examples:
Input: dq = [1, 2, 3, 4, 5]
Output: 1 2 3 4 5

Input: dq = [1]
Output: 1

Approach:
Use a range-based for loop to iterate over the deque and print each
element followed by a space, then print a newline at the end.

Time Complexity: O(n) where n is the size of the deque.
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

void printDeque(deque<int> &dq) {
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    deque<int> dq1 = {1, 2, 3, 4, 5};
    cout << "Input: dq = [1, 2, 3, 4, 5]" << endl;
    cout << "Output: ";
    printDeque(dq1);

    deque<int> dq2 = {1};
    cout << "Input: dq = [1]" << endl;
    cout << "Output: ";
    printDeque(dq2);

    return 0;
}
