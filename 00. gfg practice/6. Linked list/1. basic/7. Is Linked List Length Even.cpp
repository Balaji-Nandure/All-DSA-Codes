/*
Problem: Is Linked List Length Even

GFG: https://www.geeksforgeeks.org/problems/check-whether-the-length-of-given-linked-list-is-even-or-odd/1

Description:
Given head of a linked list, return true if length is even, otherwise false.

Examples:
12->52->10->47->95->0 => true  (length 6)
9->4->3              => false (length 3)

Constraints:
1 <= number of nodes <= 10^5
1 <= node values <= 10^5

Approach:
Traverse the list and toggle parity:
- Start with even = true (length 0 is even)
- For each node, flip even
At the end, even tells whether length is even.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Linked List Traversal / Parity Tracking
*/

#include <bits/stdc++.h>
using namespace std;

/*
class Node {
  public:
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    bool isEven(Node* head) {
        // code here
        while (head != nullptr && head->next != nullptr) {
            head = head->next->next;
            
        }
        return head == nullptr;
    }
};

