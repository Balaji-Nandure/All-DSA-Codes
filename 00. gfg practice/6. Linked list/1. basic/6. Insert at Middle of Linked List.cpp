/*
Problem: Insert at Middle of Linked List

GFG: https://www.geeksforgeeks.org/problems/insert-in-middle-of-linked-list/1

Description:
Given head of a singly linked list and value x, insert x in the middle.
As per problem statement, insert after the current middle node.

Examples:
Input: 1->2->4, x = 3
Output: 1->2->3->4

Input: 10->20->40->50, x = 30
Output: 10->20->30->40->50

Constraints:
0 <= number of nodes <= 10^5
0 <= node->data, x <= 10^3

Approach (Slow/Fast Pointer):
1) If list is empty, new node becomes head.
2) Use slow and fast pointers starting at head.
   - slow moves by 1 step
   - fast moves by 2 steps
3) When fast reaches end, slow is at middle.
4) Insert new node after slow.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Linked List Two Pointers
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
    Node* insertInMiddle(Node* head, int x) {
        Node* newNode = new Node(x);

        if (head == nullptr) {
            return newNode;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        newNode->next = slow->next;
        slow->next = newNode;

        return head;
    }
};

