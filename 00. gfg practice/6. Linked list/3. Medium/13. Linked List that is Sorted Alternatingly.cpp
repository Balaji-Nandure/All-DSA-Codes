/*
    Problem Name: Linked List that is Sorted Alternatingly
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Linked List where nodes at odd positions are sorted in ascending order and nodes at even
    positions are sorted in descending order, sort the entire linked list in non-decreasing (ascending) order.

    Examples:
    Input: 13 -> 99 -> 21 -> 80 -> 50 -> nullptr
    Output: 13 -> 21 -> 50 -> 80 -> 99 -> nullptr
    Explanation: Odd position elements (13, 21, 50) are ascending, even position elements (99, 80) are descending.
                 After sorting: 13 -> 21 -> 50 -> 80 -> 99.

    Input: 1 -> 9 -> 2 -> 8 -> 3 -> 7 -> nullptr
    Output: 1 -> 2 -> 3 -> 7 -> 8 -> 9 -> nullptr

    Constraints:
    1 <= no. of nodes <= 10^4
    0 <= node->data <= 10^4

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Copy to Vector & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Split Odd/Even + Reverse Descending + Merge Sorted (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Copy (Approach 1):
       - Store list values into `vector<int> arr`, sort `arr`, overwrite node values.
       - Time: O(N log N), Space: O(N).

    2. Optimal 3-Step Deconstruction & Merge (Approach 2):
       - Step 1 (Split): Separate list into `ascHead` (odd position nodes, ascending) and
         `descHead` (even position nodes, descending).
       - Step 2 (Reverse): Reverse `descHead` so that it also becomes sorted in ascending order.
       - Step 3 (Merge): Merge the two sorted ascending linked lists using standard 2-pointer merge with dummy node.
       - Time: O(N), Space: O(1).

    DRY RUN:
    Example: 1 -> 9 -> 2 -> 8 -> 3 -> 7
    - Step 1 (Split):
      ascHead: 1 -> 2 -> 3
      descHead: 9 -> 8 -> 7
    - Step 2 (Reverse descHead):
      Reversed descHead: 7 -> 8 -> 9
    - Step 3 (Merge 1->2->3 and 7->8->9):
      Compare 1 vs 7 -> 1
      Compare 2 vs 7 -> 2
      Compare 3 vs 7 -> 3
      Remaining -> 7 -> 8 -> 9
      Result: 1 -> 2 -> 3 -> 7 -> 8 -> 9.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Copy to Vector & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionVectorSort {
public:
    Node* sort(Node* head) {
        if (!head || !head->next) return head;

        vector<int> arr;
        Node* curr = head;
        while (curr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        std::sort(arr.begin(), arr.end());

        curr = head;
        int i = 0;
        while (curr) {
            curr->data = arr[i++];
            curr = curr->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 2: Split + Reverse Descending + Merge Sorted (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
private:
    // Helper to reverse a linked list
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

    // Helper to merge two ascending sorted linked lists
    Node* merge(Node* head1, Node* head2) {
        Node* dummy = new Node(-1);
        Node* temp = dummy;

        while (head1 != nullptr && head2 != nullptr) {
            if (head1->data <= head2->data) {
                temp->next = head1;
                head1 = head1->next;
            } else {
                temp->next = head2;
                head2 = head2->next;
            }
            temp = temp->next;
        }

        if (head1 != nullptr) temp->next = head1;
        if (head2 != nullptr) temp->next = head2;

        Node* result = dummy->next;
        delete dummy;
        return result;
    }

public:
    Node* sort(Node* head) {
        if (!head || !head->next) return head;

        Node* ascHead = head;
        Node* descHead = head->next;

        Node* pAsc = ascHead;
        Node* pDesc = descHead;

        // Step 1: Split into ascending (odd) and descending (even) sublists
        while (pAsc != nullptr && pAsc->next != nullptr) {
            pAsc->next = pAsc->next->next;
            pAsc = pAsc->next;

            if (pDesc != nullptr && pDesc->next != nullptr) {
                pDesc->next = pDesc->next->next;
                pDesc = pDesc->next;
            }
        }

        // Step 2: Reverse descending sublist to make it ascending
        descHead = reverseList(descHead);

        // Step 3: Merge the two sorted ascending sublists
        return merge(ascHead, descHead);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* sort(Node* head) {
        SolutionOptimal solver;
        return solver.sort(head);
    }

    void sort(Node** head) {
        if (head && *head) {
            *head = sort(*head);
        }
    }
};
