/*
Problem: Modular Node in Linked List

GFG: https://www.geeksforgeeks.org/problems/modular-node/1

Description:
Given head of a singly linked list and integer k, return data of the last node
whose 1-based position is divisible by k. If no such node exists, return -1.

Examples:
19->28->37->46->55, k = 2 => 46
1->2->3->4->5->6->7, k = 10 => -1

Constraints:
1 <= number of nodes <= 10^5
1 <= node->data, k <= 10^5

Approach:
Traverse with position counter (1-based):
- Whenever pos % k == 0, update answer with current node's data.
After traversal, answer stores the last modular node.

Time Complexity: O(N)
Space Complexity: O(1)

Pattern: Linked List Traversal
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
    int modularNode(Node* head, int k) {
        int pos = 1;
        int ans = -1;
        Node* curr = head;

        while (curr != nullptr) {
            if (pos % k == 0) {
                ans = curr->data;
            }
            curr = curr->next;
            pos++;
        }

        return ans;
    }
};

