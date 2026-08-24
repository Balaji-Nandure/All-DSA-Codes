/*
    Problem Name: Sorted Insert in DLL
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a sorted doubly linked list in ascending order and an element x, insert the element x into
    the correct position in the sorted Doubly Linked List (DLL) so that it remains sorted.

    Examples:
    Input: LinkedList = 3 -> 5 -> 8 -> 10 -> 12, x = 9
    Output: 3 -> 5 -> 8 -> 9 -> 10 -> 12
    Explanation: Node 9 is inserted between 8 and 10.

    Input: LinkedList = 1 -> 4 -> 10 -> 11, x = 15
    Output: 1 -> 4 -> 10 -> 11 -> 15
    Explanation: Node 15 is inserted at the end of the list.

    Constraints:
    1 <= number of nodes <= 10^3
    1 <= node->data, x <= 10^4

    Expected Complexities:
    Time Complexity: O(N), single pass traversal.
    Space Complexity: O(1) auxiliary space.

    Love Babbar / Striver Doubly Linked List Insertion Approach:

    INTUITION & STRATEGY:
    1. Case 1 (Empty List or Insert Before Head):
       - If `head == nullptr`, return `new Node(x)`.
       - If `x <= head->data`, insert `newNode` before `head`:
         `newNode->next = head;`
         `head->prev = newNode;`
         Return `newNode` as the new head.
    2. Case 2 & 3 (Insert Middle or End):
       - Traverse `curr = head` while `curr->next != nullptr` AND `curr->next->data < x`.
       - Insert `newNode` between `curr` and `curr->next`:
         * `newNode->next = curr->next;`
         * `newNode->prev = curr;`
         * If `curr->next != nullptr`, `curr->next->prev = newNode;`
         * `curr->next = newNode;`
       - Return `head`.

    DRY RUN:
    Example: 3 <-> 5 <-> 8 <-> 10 <-> 12, x = 9
    - x = 9 > head->data (3), move to Case 2.
    - curr = node(3): curr->next->data = 5 < 9 -> move curr to node(5).
    - curr = node(5): curr->next->data = 8 < 9 -> move curr to node(8).
    - curr = node(8): curr->next->data = 10 >= 9 -> stop loop!
    - Insert newNode(9) between node(8) and node(10):
      newNode->next = node(10);
      newNode->prev = node(8);
      node(10)->prev = newNode(9);
      node(8)->next = newNode(9);
    - Output: 3 <-> 5 <-> 8 <-> 9 <-> 10 <-> 12.
*/

#include <iostream>

using namespace std;

// Definition for Doubly Linked List Node
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// ============================================================================
// Approach 1: Single Pass Pointer Updates (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    Node* sortedInsert(Node* head, int x) {
        Node* newNode = new Node(x);

        // Case 1: Empty List
        if (head == nullptr) {
            return newNode;
        }

        // Case 2: Insert before Head (New Minimum)
        if (x <= head->data) {
            newNode->next = head;
            head->prev = newNode;
            return newNode; // New Head
        }

        // Case 3: Insert in Middle or End
        Node* curr = head;
        while (curr->next != nullptr && curr->next->data < x) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        newNode->prev = curr;

        if (curr->next != nullptr) {
            curr->next->prev = newNode;
        }

        curr->next = newNode;

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* sortedInsert(Node* head, int x) {
        SolutionOptimal solver;
        return solver.sortedInsert(head, x);
    }
};
