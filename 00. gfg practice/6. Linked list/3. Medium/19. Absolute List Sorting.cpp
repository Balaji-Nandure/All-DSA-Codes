/*
    Problem Name: Absolute List Sorting
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a singly linked list sorted in ascending order based on the absolute values of nodes,
    sort the linked list in actual non-decreasing (ascending) order.

    Examples:
    Input: 1 -> -2 -> -3 -> 4 -> -5 -> nullptr
    Output: -5 -> -3 -> -2 -> 1 -> 4 -> nullptr
    Explanation: Sorted by actual value: -5 < -3 < -2 < 1 < 4.

    Input: 5 -> -10 -> nullptr
    Output: -10 -> 5 -> nullptr
    Explanation: Sorted by actual value: -10 < 5.

    Constraints:
    1 <= no. of nodes <= 10^5
    -10^5 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Single Pass In-Place Prepending of Negative Nodes (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect values into `vector<int> arr`, sort `arr`, overwrite node values.
       - Time: O(N log N), Space: O(N).

    2. Optimal Single Pass Prepending (Approach 2):
       - Key Observation: The list is ALREADY sorted by absolute values!
         * Positive numbers are ALREADY in correct relative ascending order (e.g. 1 -> 4).
         * Negative numbers appear in increasing magnitude order (|-2| < |-3| < |-5|), meaning their
           actual values are in DECREASING order (-2 > -3 > -5).
       - Algorithm: Maintain `prev` (starts at `head`) and `curr` (starts at `head->next`).
         * If `curr->data < 0`: Detach `curr` from its position (`prev->next = curr->next`) and PREPEND it
           to `head` (`curr->next = head; head = curr`).
         * If `curr->data >= 0`: Simply advance `prev = curr`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 1 -> -2 -> -3 -> 4 -> -5
    - head = 1, prev = 1, curr = -2
    - curr(-2) < 0: Detach -2, prepend to head -> List: -2 -> 1 -> -3 -> 4 -> -5. head = -2, curr = -3
    - curr(-3) < 0: Detach -3, prepend to head -> List: -3 -> -2 -> 1 -> 4 -> -5. head = -3, curr = 4
    - curr(4) >= 0: prev = 4, curr = -5
    - curr(-5) < 0: Detach -5, prepend to head -> List: -5 -> -3 -> -2 -> 1 -> 4. head = -5, curr = nullptr
    - Result: -5 -> -3 -> -2 -> 1 -> 4.
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
// Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionVectorSort {
public:
    Node* sortList(Node* head) {
        if (!head || !head->next) return head;

        vector<int> arr;
        Node* curr = head;
        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        sort(arr.begin(), arr.end());

        curr = head;
        int i = 0;
        while (curr != nullptr) {
            curr->data = arr[i++];
            curr = curr->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 2: Single Pass In-Place Prepending (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* sortList(Node* head) {
        if (!head || !head->next) return head;

        Node* prev = head;
        Node* curr = head->next;

        while (curr != nullptr) {
            // If current node is negative, move it to the front (prepend)
            if (curr->data < 0) {
                prev->next = curr->next; // Detach curr
                curr->next = head;       // Link curr to current head
                head = curr;             // Update head to curr
                curr = prev->next;       // Advance curr
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* sortList(Node* head) {
        SolutionOptimal solver;
        return solver.sortList(head);
    }
};
