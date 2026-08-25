/*
    Problem Name: Linked List in Zig-Zag fashion
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a singly linked list, rearrange the nodes to form a zig-zag pattern:
    a <= b >= c <= d >= e <= f ...
    Only swapping of adjacent node data/pointers is allowed. Return the head of the modified list.

    Examples:
    Input: 1 -> 2 -> 3 -> 4 -> nullptr
    Output: 1 -> 3 -> 2 -> 4 -> nullptr
    Explanation: Arranged as 1 <= 3 >= 2 <= 4.

    Input: 11 -> 15 -> 20 -> 5 -> 10 -> nullptr
    Output: 11 -> 20 -> 5 -> 15 -> 10 -> nullptr
    Explanation: Arranged as 11 <= 20 >= 5 <= 15 >= 10.

    Constraints:
    1 <= number of nodes <= 10^3
    1 <= node->data <= 10^4

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Storage & Adjacent Swap (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Single Pass Flag Traversal (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect node data into `vector<int> arr`.
       - Use a boolean `flag = true` (where `true` expects `<=`, `false` expects `>=`).
       - Traverse `i` from 0 to N-2:
         * If `flag` is true and `arr[i] > arr[i+1]`: `swap(arr[i], arr[i+1])`.
         * If `flag` is false and `arr[i] < arr[i+1]`: `swap(arr[i], arr[i+1])`.
         * Toggle `flag = !flag`.
       - Overwrite node data in linked list with `arr`.
       - Time: O(N), Space: O(N).

    2. Optimal Single Pass Flag Traversal (Approach 2):
       - Traverse list directly with `curr` and boolean `flag = true`.
       - For each node:
         * If `flag == true` (expects `curr->data <= curr->next->data`), and `curr->data > curr->next->data`:
           swap `curr->data` and `curr->next->data`.
         * If `flag == false` (expects `curr->data >= curr->next->data`), and `curr->data < curr->next->data`:
           swap `curr->data` and `curr->next->data`.
       - Toggle `flag = !flag` and move `curr = curr->next`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 11 -> 15 -> 20 -> 5 -> 10
    - curr = 11, next = 15, flag = true  (11 <= 15 OK) -> flag = false, curr = 15
    - curr = 15, next = 20, flag = false (15 < 20 Violation!) -> swap(15, 20) -> List: 11->20->15->5->10, flag = true, curr = 15
    - curr = 15, next = 5,  flag = true  (15 > 5 Violation!) -> swap(15, 5)  -> List: 11->20->5->15->10, flag = false, curr = 15
    - curr = 15, next = 10, flag = false (15 >= 10 OK) -> flag = true, curr = 10
    - End of list.
    - Result: 11 -> 20 -> 5 -> 15 -> 10.
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
// Approach 1: Vector Storage & Adjacent Swap (O(N) Time, O(N) Space)
// ============================================================================
class SolutionVector {
public:
    Node* zigZag(Node* head) {
        if (!head || !head->next) return head;

        vector<int> arr;
        Node* curr = head;
        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        bool flag = true; // true means <=, false means >=
        for (size_t i = 0; i < arr.size() - 1; i++) {
            if (flag) {
                if (arr[i] > arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            } else {
                if (arr[i] < arr[i + 1]) {
                    swap(arr[i], arr[i + 1]);
                }
            }
            flag = !flag;
        }

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
// Approach 2: Single Pass Flag Traversal (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* zigZag(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        bool flag = true; // true indicates '<=', false indicates '>='
        Node* curr = head;

        while (curr != nullptr && curr->next != nullptr) {
            if (flag) {
                // If a <= b is expected, but a > b, swap values
                if (curr->data > curr->next->data) {
                    swap(curr->data, curr->next->data);
                }
            } else {
                // If a >= b is expected, but a < b, swap values
                if (curr->data < curr->next->data) {
                    swap(curr->data, curr->next->data);
                }
            }

            flag = !flag;      // Toggle expected condition
            curr = curr->next; // Move to next node
        }

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* zigZag(Node* head) {
        SolutionOptimal solver;
        return solver.zigZag(head);
    }
};
