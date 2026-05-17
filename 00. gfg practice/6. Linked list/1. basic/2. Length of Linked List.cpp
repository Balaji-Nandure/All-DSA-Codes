/*
Problem: Length of Linked List

GFG: https://www.geeksforgeeks.org/problems/count-nodes-of-linked-list/1

Description:
Given the head of a singly linked list, return its length
(total number of nodes).

Examples:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: 5

Input: 2 -> 4 -> 6 -> 7 -> 5 -> 1 -> 0
Output: 7

Constraints:
1 <= number of nodes <= 4 * 10^4
1 <= node->data <= 10^3

Approach:
Traverse the linked list from head to NULL and count nodes.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Linked List Traversal
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node{
    int data;
    Node* next;
};
*/

class Solution {
  public:
    int getCount(struct Node* head) {
        int count = 0;
        Node* curr = head;

        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }

        return count;
    }
};

