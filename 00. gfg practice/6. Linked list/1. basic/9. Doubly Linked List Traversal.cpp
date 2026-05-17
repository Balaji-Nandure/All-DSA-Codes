/*
Problem: Doubly Linked List Traversal

GFG: https://www.geeksforgeeks.org/problems/doubly-linked-list-traversal/1

Description:
Given head of a doubly linked list, return its elements as an array
(forward traversal order).

Note:
Driver code may print returned values in forward and reverse direction.

Examples:
1<->2<->3<->4<->5 -> [1, 2, 3, 4, 5]
34<->22            -> [34, 22]
1                  -> [1]

Constraints:
1 <= n <= 10^3
0 <= node value <= 10^3

Approach:
Traverse from head using next pointer and push each node's data into vector.

Time Complexity: O(N)
Space Complexity: O(N) for output vector

Pattern: Doubly Linked List Traversal
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node {
    int data;
    Node* next;
    Node* prev;
};
*/

class Solution {
  public:
    vector<int> displayList(Node* head) {
        vector<int> ans;
        Node* curr = head;

        while (curr != nullptr) {
            ans.push_back(curr->data);
            curr = curr->next;
        }

        return ans;
    }
};

