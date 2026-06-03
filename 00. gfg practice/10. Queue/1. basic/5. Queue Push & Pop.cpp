/*
Problem: Queue Push & Pop

GFG: https://www.geeksforgeeks.org/problems/queue-push-pop/1

Description:
Given an array arr[], implement:
- fillQ(): Enqueue all elements of arr into a queue and return it
- emptyQ(): Dequeue all elements from the queue and print them in a
  single line separated by spaces, followed by a newline

Examples:
Input: arr[] = [1, 2, 3, 4, 5]
Output: 1 2 3 4 5

Input: arr[] = [1, 6, 43, 1, 2, 0, 5]
Output: 1 6 43 1 2 0 5

Constraints:
1 ≤ arr[i] ≤ 10^3

Approach:
For fillQ, iterate through the array and push each element into queue.
For emptyQ, while queue is not empty, print front and pop.

Time Complexity: O(n) for both operations
Space Complexity: O(n) for the queue
*/

#include <bits/stdc++.h>
using namespace std;

queue<int> fillQ(int arr[], int n) {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        q.push(arr[i]);
    }
    return q;
}

void emptyQ(queue<int> &q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}
