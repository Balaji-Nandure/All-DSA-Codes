/*
    Problem Name: Insert in Sorted Circular Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a sorted circular linked list, insert a new node with value `data` into this circular linked list
    so that it remains a sorted circular linked list.

    Examples:
    Input: head = 1 -> 2 -> 4 (circular), data = 2
    Output: 1 -> 2 -> 2 -> 4 (circular)
    Explanation: Insert 2 between 2 and 4.

    Input: head = 1 -> 4 -> 7 -> 9 (circular), data = 5
    Output: 1 -> 4 -> 5 -> 7 -> 9 (circular)
    Explanation: Insert 5 between 4 and 7.

    Constraints:
    2 <= number of nodes <= 10^6
    0 <= node->data <= 10^6
    0 <= data <= 10^6

    Expected Complexities:
    Time Complexity: O(N), single pass to find insertion point.
    Space Complexity: O(1) auxiliary space.

    Love Babbar / Striver Approach:
    Single-Pass Traversal with Boundary Pointer Insertion

    INTUITION & STRATEGY:
    1. Case 1 (Empty List):
       - If `head == nullptr`, create `newNode`, set `newNode->next = newNode`, return `newNode`.
    2. Case 2 (Insertion BEFORE Head / New Minimum):
       - If `data < head->data`:
         * Traverse to the last node `curr` (where `curr->next == head`).
         * Link `newNode->next = head` and `curr->next = newNode`.
         * Return `newNode` as the new head of the circular list.
    3. Case 3 (Insertion in Middle or End):
       - Traverse `curr = head` while `curr->next != head` AND `curr->next->data < data`.
       - Insert `newNode` between `curr` and `curr->next`:
         `newNode->next = curr->next;`
         `curr->next = newNode;`
       - Return `head`.

    DRY RUN:
    Example: head = 1 -> 4 -> 7 -> 9, data = 5
    - head->data = 1, data = 5 (data >= head->data, move to Case 3).
    - curr = node(1): curr->next->data = 4 < 5 -> move curr to node(4).
    - curr = node(4): curr->next->data = 7 >= 5 -> stop loop!
    - Insert newNode(5) between node(4) and node(7):
      newNode->next = curr->next (7);
      curr->next = newNode (5);
    - Output: 1 -> 4 -> 5 -> 7 -> 9 (circular).
*/

#include <iostream>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Single-Pass Traversal (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    Node* sortedInsert(Node* head, int data) {
        Node* newNode = new Node(data);

        // Case 1: Empty List
        if (head == nullptr) {
            newNode->next = newNode;
            return newNode;
        }

        // Case 2: Node to be inserted before head (new minimum)
        if (data < head->data) {
            Node* curr = head;
            while (curr->next != head) {
                curr = curr->next;
            }
            newNode->next = head;
            curr->next = newNode;
            return newNode; // New minimum becomes new head
        }

        // Case 3: Node to be inserted in the middle or end
        Node* curr = head;
        while (curr->next != head && curr->next->data < data) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* sortedInsert(Node* head, int data) {
        SolutionOptimal solver;
        return solver.sortedInsert(head, data);
    }
};
