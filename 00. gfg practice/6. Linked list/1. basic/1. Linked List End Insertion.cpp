/*
Problem: Linked List End Insertion

GFG: https://www.geeksforgeeks.org/problems/linked-list-insertion-1587115620/1

Description:
Given the head of a singly linked list and an integer x, insert x at the end
of the linked list and return the head.

Examples:
Input: x = 6, list = 1 -> 2 -> 3 -> 4 -> 5
Output: 1 -> 2 -> 3 -> 4 -> 5 -> 6

Input: x = 1, list = 4 -> 5
Output: 4 -> 5 -> 1

Constraints:
0 <= number of nodes <= 10^5
0 <= node->data, x <= 10^3

Approach:
1) Create a new node with value x.
2) If list is empty, new node becomes head.
3) Otherwise traverse till last node and connect last->next = new node.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Linked List Traversal / Tail Insertion
*/

#include <bits/stdc++.h>
using namespace std;

/*
struct Node {
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
    Node* insertAtEnd(Node* head, int x) {
        Node* newNode = new Node(x);

        if (head == nullptr) {
            return newNode;
        }

        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }

        curr->next = newNode;
        return head;
    }
};

