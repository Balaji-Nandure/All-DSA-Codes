/*
Problem: Identical Linked Lists

GFG: https://www.geeksforgeeks.org/problems/identical-linked-lists/1

Description:
Given heads of two singly linked lists, return true if both lists are
identical (same length and same data at each corresponding position),
otherwise return false.

Examples:
head1: 1->2->3->4->5->6, head2: 99->59->42->20 => false
head1: 1->2->3->4->5,   head2: 1->2->3->4->5   => true

Constraints:
1 <= length of lists <= 10^5
1 <= node values <= 10^5

Approach:
Traverse both lists together:
- If any pair of node values differ, return false.
- After loop, both must reach NULL together.

Time Complexity: O(min(n, m)) then final NULL check => O(n + m) worst-case
Space Complexity: O(1)

Pattern: Linked List Two-Pointer Traversal
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
    bool areIdentical(Node *head1, Node *head2) {
        Node* p1 = head1;
        Node* p2 = head2;

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data != p2->data) {
                return false;
            }

            p1 = p1->next;
            p2 = p2->next;
        }

        return (p1 == nullptr && p2 == nullptr);
    }
};

