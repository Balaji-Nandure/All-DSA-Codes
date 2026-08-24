/*
    Problem Name: Add 1 to a Linked List Number
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given the head of a linked list where each node contains a single digit. The digits together
    represent a number formed by concatenating the node values in order. Add 1 to this number and return
    the head of the modified linked list.

    Examples:
    Input: 4 -> 5 -> 6 -> nullptr
    Output: 4 -> 5 -> 7

    Input: 1 -> 2 -> 3 -> nullptr
    Output: 1 -> 2 -> 4

    Input: 0 -> 0 -> 1 -> nullptr
    Output: 0 -> 0 -> 2

    Input: 9 -> 9 -> 9 -> nullptr
    Output: 1 -> 0 -> 0 -> 0

    Constraints:
    1 <= no. of nodes in head <= 10^5
    0 <= head.node->data <= 9

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space (In-Place Reversal) or O(N) stack space (Recursion).

    Approach 1: Reverse List + Add 1 + Reverse Back (Optimal O(1) Auxiliary Space - Striver & Love Babbar)
    Approach 2: Backtracking Recursion (O(N) Stack Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. In-Place Reversal (Approach 1):
       - Step 1: Reverse the linked list so LSD is at the head.
       - Step 2: Add 1 to the head node. Propagate carry along the list.
         If carry remains at the end (e.g. 999 -> 999+1), append a new node with data `carry`.
       - Step 3: Reverse the list back to restore original MSD-first order.
       - Time: O(N), Auxiliary Space: O(1).

    2. Backtracking Recursion (Approach 2):
       - Recurse to the end of the list (LSD).
       - Base Case (past tail): Return carry = 1.
       - As recursion unwinds back to head:
         * Add returned carry to current node's data: `sum = node->data + carry`.
         * Update `node->data = sum % 10` and return new `carry = sum / 10`.
       - If carry remains after head (e.g. 999), create a new node with data `carry` as the new head.
       - Time: O(N), Stack Space: O(N).
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Reverse List + Add 1 + Reverse Back (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionReversal {
private:
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;

        while (curr != nullptr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }

public:
    Node* addOne(Node* head) {
        if (!head) return new Node(1);

        // Step 1: Reverse list to process LSD first
        head = reverseList(head);

        // Step 2: Add 1 and propagate carry
        Node* curr = head;
        int carry = 1;

        while (curr != nullptr) {
            int sum = curr->data + carry;
            curr->data = sum % 10;
            carry = sum / 10;

            if (carry == 0) break;

            // If carry remains at the last node, append a new node
            if (curr->next == nullptr && carry > 0) {
                curr->next = new Node(carry);
                carry = 0;
                break;
            }

            curr = curr->next;
        }

        // Step 3: Reverse list back to original MSD-first order
        return reverseList(head);
    }
};

// ============================================================================
// Approach 2: Backtracking Recursion (O(N) Call Stack Space - Striver & Love Babbar)
// ============================================================================
class SolutionRecursion {
private:
    int addHelper(Node* temp) {
        // Base Case: Past the tail node, return carry 1
        if (temp == nullptr) {
            return 1;
        }

        int carry = addHelper(temp->next);
        int sum = temp->data + carry;
        temp->data = sum % 10;

        return sum / 10;
    }

public:
    Node* addOne(Node* head) {
        int carry = addHelper(head);

        // If carry remains at head (e.g., 999 -> 1000), prepend new head node
        if (carry > 0) {
            Node* newHead = new Node(carry);
            newHead->next = head;
            return newHead;
        }

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* addOne(Node* head) {
        SolutionReversal solver;
        return solver.addOne(head);
    }
};

// ============================================================================
// Helper Functions for Testing
// ============================================================================

// Helper to create a linked list from a vector
Node* createList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for (size_t i = 1; i < values.size(); i++) {
        curr->next = new Node(values[i]);
        curr = curr->next;
    }
    return head;
}

// Helper to print linked list
void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << "\n";
}

int main() {
    // Example 1: 4 -> 5 -> 6
    // Expected Output: 4 -> 5 -> 7
    Node* head1 = createList({4, 5, 6});
    cout << "Example 1 Input: ";
    printList(head1);

    SolutionReversal solver1;
    Node* res1 = solver1.addOne(head1);
    cout << "Example 1 Add 1 (Reversal): ";
    printList(res1);
    cout << "\n";

    // Example 2: 9 -> 9 -> 9
    // Expected Output: 1 -> 0 -> 0 -> 0
    Node* head2 = createList({9, 9, 9});
    cout << "Example 2 Input: ";
    printList(head2);

    SolutionRecursion solver2;
    Node* res2 = solver2.addOne(head2);
    cout << "Example 2 Add 1 (Recursion): ";
    printList(res2);

    return 0;
}
