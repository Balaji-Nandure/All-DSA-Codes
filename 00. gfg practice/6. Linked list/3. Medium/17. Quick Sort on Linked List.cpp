/*
    Problem Name: Quick Sort on Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a singly linked list, sort the linked list in non-decreasing order using the
    Quick Sort algorithm and return the head of the sorted list.

    Examples:
    Input: 3 -> 5 -> 2 -> 4 -> nullptr
    Output: 2 -> 3 -> 4 -> 5 -> nullptr

    Input: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> nullptr
    Output: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> nullptr

    Constraints:
    1 <= size of linked list <= 10^5
    -10^9 <= node->data <= 10^9

    Expected Complexities:
    Time Complexity: O(N log N) average, O(N^2) worst case.
    Space Complexity: O(log N) recursive call stack space.

    Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Partitioning Quick Sort on Linked List (Optimal O(N log N) Avg Time, O(log N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Traverse list, copy all values to `vector<int> arr`, sort `arr`, overwrite node values.
       - Time: O(N log N), Space: O(N).

    2. Optimal Linked List Quick Sort (Approach 2):
       - Pick `head` as `pivot`.
       - Partition remaining nodes into 3 separate lists using dummy nodes (`new Node(-1)`):
         * `leftDummy`: Nodes with `data < pivot->data`
         * `equalDummy`: Nodes with `data == pivot->data`
         * `rightDummy`: Nodes with `data > pivot->data`
       - Recursively sort `leftHead` and `rightHead`:
         `leftHead = quickSort(leftDummy->next);`
         `rightHead = quickSort(rightDummy->next);`
       - Concatenate: `leftHead` -> `equalHead` -> `rightHead`.
       - Return head of the concatenated list.
       - Time: O(N log N) average, Space: O(log N) recursion stack space.

    DRY RUN:
    Example: 3 -> 5 -> 2 -> 4
    - Pivot = 3
    - Partitioning:
      left: 2 -> nullptr
      equal: 3 -> nullptr
      right: 5 -> 4 -> nullptr
    - Recursive Calls:
      quickSort(2) -> 2
      quickSort(5 -> 4) -> 4 -> 5
    - Concatenate (2) + (3) + (4 -> 5):
      Result: 2 -> 3 -> 4 -> 5.
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
    Node* quickSort(Node* head) {
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
// Approach 2: Optimal Linked List Quick Sort (O(N log N) Avg Time, O(log N) Space)
// ============================================================================
class SolutionQuickSort {
public:
    Node* quickSort(Node* head) {
        // Base Case: 0 or 1 element is already sorted
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* pivot = head;

        // Dummy nodes for 3 partitions (User Preferred Heap Allocation)
        Node* leftDummy = new Node(-1);
        Node* equalDummy = new Node(-1);
        Node* rightDummy = new Node(-1);

        Node* left = leftDummy;
        Node* equal = equalDummy;
        Node* right = rightDummy;

        Node* curr = head;

        // Step 1: Partition nodes into left (< pivot), equal (== pivot), and right (> pivot)
        while (curr != nullptr) {
            if (curr->data < pivot->data) {
                left->next = curr;
                left = left->next;
            } else if (curr->data == pivot->data) {
                equal->next = curr;
                equal = equal->next;
            } else {
                right->next = curr;
                right = right->next;
            }
            curr = curr->next;
        }

        left->next = nullptr;
        equal->next = nullptr;
        right->next = nullptr;

        // Step 2: Recursively sort left and right partitions
        Node* sortedLeft = quickSort(leftDummy->next);
        Node* sortedRight = quickSort(rightDummy->next);
        Node* equalHead = equalDummy->next;

        delete leftDummy;
        delete rightDummy;

        // Step 3: Concatenate sortedLeft + equalHead + sortedRight
        if (sortedLeft != nullptr) {
            Node* tail = sortedLeft;
            while (tail->next != nullptr) {
                tail = tail->next;
            }
            tail->next = equalHead;
            equal->next = sortedRight;
            delete equalDummy;
            return sortedLeft;
        } else {
            equal->next = sortedRight;
            delete equalDummy;
            return equalHead;
        }
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* quickSort(Node* head) {
        SolutionQuickSort solver;
        return solver.quickSort(head);
    }
};
