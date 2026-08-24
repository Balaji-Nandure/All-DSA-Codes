/*
    Problem Name: Sort Singly Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 147

    Problem Statement:
    Given a singly linked list, sort the list in ascending order.

    Examples:
    Input: 30 -> 23 -> 28 -> 30 -> 11 -> 14 -> 19 -> 16 -> 21 -> 25 -> nullptr
    Output: 11 -> 14 -> 16 -> 19 -> 21 -> 23 -> 25 -> 28 -> 30 -> 30 -> nullptr

    Input: 19 -> 20 -> 16 -> 24 -> 12 -> 29 -> 30 -> nullptr
    Output: 12 -> 16 -> 19 -> 20 -> 24 -> 29 -> 30 -> nullptr

    Constraints:
    0 <= number of nodes <= 10^3
    0 <= node->data <= 10^4

    Expected Complexities:
    Time Complexity: O(N log N)
    Space Complexity: O(log N) stack space (Merge Sort) or O(1) auxiliary space (Insertion Sort).

    Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Insertion Sort on Linked List (O(N^2) Time, O(1) Space - Striver & Love Babbar)
    Approach 3: Divide & Conquer Merge Sort (Optimal O(N log N) Time, O(log N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect values into `vector<int> arr`, sort `arr`, overwrite node values.
       - Time: O(N log N), Space: O(N).

    2. Insertion Sort Approach (Approach 2):
       - Maintain a sorted list anchored by `dummy = new Node(-1)`.
       - For each node `curr`, traverse from `dummy` to find the correct insertion position
         where `prev->next->data >= curr->data`, and insert `curr` between `prev` and `prev->next`.
       - Time: O(N^2), Auxiliary Space: O(1).

    3. Optimal Merge Sort Approach (Approach 3):
       - Split list into two halves using `getMiddle` (staggered slow/fast pointers).
       - Recursively sort both halves and merge them using 2-pointer dummy node merge.
       - Time: O(N log N), Space: O(log N) recursion stack.

    DRY RUN (Insertion Sort):
    Example: 30 -> 23 -> 28
    - dummy(-1) -> nullptr
    - Insert 30: dummy -> 30 -> nullptr
    - Insert 23: prev at dummy (-1 < 23, 30 > 23). Insert 23: dummy -> 23 -> 30 -> nullptr
    - Insert 28: prev moves to 23 (23 < 28, 30 > 28). Insert 28: dummy -> 23 -> 28 -> 30 -> nullptr
    - Result: 23 -> 28 -> 30.
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
// Approach 2: Insertion Sort on Linked List (O(N^2) Time, O(1) Space)
// ============================================================================
class SolutionInsertionSort {
public:
    Node* sortList(Node* head) {
        if (!head || !head->next) return head;

        Node* dummy = new Node(-1);
        Node* curr = head;

        while (curr != nullptr) {
            Node* nextNode = curr->next;
            Node* prev = dummy;

            // Find insertion position in sorted list
            while (prev->next != nullptr && prev->next->data < curr->data) {
                prev = prev->next;
            }

            // Insert curr between prev and prev->next
            curr->next = prev->next;
            prev->next = curr;

            curr = nextNode;
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// ============================================================================
// Approach 3: Divide & Conquer Merge Sort (Optimal O(N log N) Time, O(log N) Space)
// ============================================================================
class SolutionMergeSort {
private:
    Node* getMiddle(Node* head) {
        if (!head) return head;
        Node* slow = head;
        Node* fast = head->next; // First middle node for even lengths
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    Node* merge(Node* left, Node* right) {
        Node* dummy = new Node(-1);
        Node* temp = dummy;

        while (left != nullptr && right != nullptr) {
            if (left->data <= right->data) {
                temp->next = left;
                left = left->next;
            } else {
                temp->next = right;
                right = right->next;
            }
            temp = temp->next;
        }

        if (left != nullptr) temp->next = left;
        else temp->next = right;

        Node* result = dummy->next;
        delete dummy;
        return result;
    }

public:
    Node* sortList(Node* head) {
        if (!head || !head->next) return head;

        Node* mid = getMiddle(head);
        Node* rightHead = mid->next;
        mid->next = nullptr;

        Node* left = sortList(head);
        Node* right = sortList(rightHead);

        return merge(left, right);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* sortList(Node* head) {
        SolutionMergeSort solver;
        return solver.sortList(head);
    }
};
