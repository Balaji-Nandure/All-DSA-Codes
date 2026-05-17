/*
Problem: Length of Circular Linked List

GFG: https://www.geeksforgeeks.org/problems/length-of-circular-linked-list/1

Description:
Given head of a circular linked list, return the total number of nodes.
In circular list, tail->next points back to head.

Examples:
Output: 5
Output: 6

Constraints:
1 <= nodes <= 10^3

Approach:
If head is NULL, return 0.
Otherwise:
1) Start count = 1 from head.
2) Move pointer to next node until pointer becomes head again.
3) Increase count at each move.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Circular Linked List Traversal
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node {
    int data;
    Node* next;
};
*/

class Solution {
  public:
    int getLength(Node* head) {
        if (head == nullptr) {
            return 0;
        }

        int count = 1;
        Node* curr = head->next;

        while (curr != head) {
            count++;
            curr = curr->next;
        }

        return count;
    }
};

