/*
    Problem Name: Merge 2 Sorted Linked Lists in Reverse Order
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the heads of two linked lists head1 and head2, where both linked lists are sorted in
    non-decreasing (ascending) order, merge them into a single linked list such that the resulting
    linked list is sorted in non-increasing (descending) order.

    Examples:
    Input: head1 = 1 -> 3, head2 = 2 -> 4
    Output: 4 -> 3 -> 2 -> 1
    Explanation: The merged descending order list is 4 -> 3 -> 2 -> 1.

    Input: head1 = 5 -> 10 -> 15 -> 40, head2 = 2 -> 3 -> 20
    Output: 40 -> 20 -> 15 -> 10 -> 5 -> 3 -> 2

    Constraints:
    1 <= size of LinkedLists <= 10^5
    0 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N + M)
    Space Complexity: O(1) auxiliary space

    Approach 1: Merge Ascending + Reverse Result (O(N + M) Time, O(1) Space - Striver & Love Babbar)
    Approach 2: Optimal Single-Pass Front-Insertion / Prepending (O(N + M) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Merge then Reverse (Approach 1):
       - Merge `head1` and `head2` into an ascending sorted list using standard 2-pointer dummy node merge.
       - Reverse the merged list to get descending order.
       - Time: O(N + M), Space: O(1).

    2. Optimal Front-Insertion / Prepending (Approach 2):
       - Maintain a result head `resHead = nullptr`.
       - Compare `p1` (head1) and `p2` (head2) node values.
       - Pick the SMALLER node, detach it, and PREPEND (front insert) it to `resHead`.
       - Because smaller nodes are prepended first, they get pushed to the back of `resHead`,
         naturally producing a DESCENDING sorted list in a single pass without explicit reversal!
       - Time: O(N + M), Space: O(1).

    DRY RUN:
    Example: head1 = 1 -> 3, head2 = 2 -> 4
    - resHead = nullptr
    - Compare 1 vs 2 -> Pick node(1): prepend to resHead -> resHead = 1 -> nullptr, p1 = node(3)
    - Compare 3 vs 2 -> Pick node(2): prepend to resHead -> resHead = 2 -> 1 -> nullptr, p2 = node(4)
    - Compare 3 vs 4 -> Pick node(3): prepend to resHead -> resHead = 3 -> 2 -> 1 -> nullptr, p1 = nullptr
    - Remaining node(4): prepend to resHead -> resHead = 4 -> 3 -> 2 -> 1 -> nullptr
    - Result: 4 -> 3 -> 2 -> 1.
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
// Approach 1: Merge Ascending + Reverse Result (O(N + M) Time, O(1) Space)
// ============================================================================
class SolutionMergeThenReverse {
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
    Node* mergeResult(Node* node1, Node* node2) {
        Node* dummy = new Node(-1);
        Node* temp = dummy;

        Node* p1 = node1;
        Node* p2 = node2;

        // Step 1: Merge in ascending order
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data <= p2->data) {
                temp->next = p1;
                p1 = p1->next;
            } else {
                temp->next = p2;
                p2 = p2->next;
            }
            temp = temp->next;
        }

        if (p1 != nullptr) temp->next = p1;
        if (p2 != nullptr) temp->next = p2;

        Node* mergedHead = dummy->next;
        delete dummy;

        // Step 2: Reverse merged list to descending order
        return reverseList(mergedHead);
    }
};

// ============================================================================
// Approach 2: Optimal Single-Pass Front-Insertion (O(N + M) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* mergeResult(Node* node1, Node* node2) {
        Node* resHead = nullptr;
        Node* p1 = node1;
        Node* p2 = node2;

        // Compare and prepend the smaller node to resHead
        while (p1 != nullptr && p2 != nullptr) {
            if (p1->data <= p2->data) {
                Node* nextNode = p1->next;
                p1->next = resHead;
                resHead = p1;
                p1 = nextNode;
            } else {
                Node* nextNode = p2->next;
                p2->next = resHead;
                resHead = p2;
                p2 = nextNode;
            }
        }

        // Prepend remaining nodes of list 1
        while (p1 != nullptr) {
            Node* nextNode = p1->next;
            p1->next = resHead;
            resHead = p1;
            p1 = nextNode;
        }

        // Prepend remaining nodes of list 2
        while (p2 != nullptr) {
            Node* nextNode = p2->next;
            p2->next = resHead;
            resHead = p2;
            p2 = nextNode;
        }

        return resHead;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* mergeResult(Node* node1, Node* node2) {
        SolutionOptimal solver;
        return solver.mergeResult(node1, node2);
    }
};
