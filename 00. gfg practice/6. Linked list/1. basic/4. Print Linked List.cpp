/*
Problem: Print Linked List

GFG: https://www.geeksforgeeks.org/problems/print-linked-list-elements/1

Description:
Given the head of a singly linked list, return a vector containing all node
values in the same order.

Examples:
Input: 1 -> 2 -> 3 -> 4 -> 5
Output: [1, 2, 3, 4, 5]

Input: 10 -> 20 -> 30 -> 40 -> 50 -> 60
Output: [10, 20, 30, 40, 50, 60]

Constraints:
1 <= number of nodes <= 10^5
1 <= node value <= 10^6

Approach:
Traverse from head to NULL and keep pushing each node's data into answer.

Time Complexity: O(N)
Space Complexity: O(N) for output vector

Pattern: Linked List Traversal
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
    vector<int> displayList(Node *head) {
        vector<int> ans;
        Node* curr = head;

        while (curr != nullptr) {
            ans.push_back(curr->data);
            curr = curr->next;
        }

        return ans;
    }
};

