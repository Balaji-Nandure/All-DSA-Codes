/*
    Problem Name: Swap Kth nodes from ends
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 1721

    Problem Statement:
    Given the head of a singly linked list and an integer k. Swap the kth node (1-based index) from the
    beginning and the kth node from the end of the linked list. Return the head of the final list.
    If k is greater than the total number of nodes or swapping is not possible, return the original list.

    Examples:
    Input: head = 1 -> 2 -> 3 -> 4 -> 5, k = 1
    Output: 5 -> 2 -> 3 -> 4 -> 1
    Explanation: 1st node from start is 1, 1st node from end is 5. Swap values -> 5 -> 2 -> 3 -> 4 -> 1.

    Input: head = 1 -> 2 -> 3 -> 4 -> 5, k = 2
    Output: 1 -> 4 -> 3 -> 2 -> 5
    Explanation: 2nd node from start is 2, 2nd node from end is 4. Swap values -> 1 -> 4 -> 3 -> 2 -> 5.

    Constraints:
    1 <= list size <= 10^4
    1 <= node->data <= 10^6
    1 <= k <= 10^4

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Two Pass Length Count (O(N) Time, O(1) Space - Striver & Love Babbar)
    Approach 2: Single Pass 2-Pointer Technique (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Two Pass Approach (Approach 1):
       - Pass 1: Count total length N of the linked list.
       - If k > N or k <= 0, return `head`.
       - Pass 2: Find kth node from start `firstK` at index `k` and kth node from end `secondK` at index `N - k + 1`.
       - Swap node values `swap(firstK->data, secondK->data)`.
       - Time: O(N), Space: O(1).

    2. Single Pass 2-Pointer Technique (Approach 2):
       - Step 1: Advance `fast` pointer `k - 1` steps from `head` to reach kth node from start.
         If `fast == nullptr`, `k > N`, return `head`.
       - Set `firstK = fast`.
       - Step 2: Initialize `secondK = head`. Advance both `fast` and `secondK` simultaneously
         until `fast->next == nullptr`. Now `secondK` is at the kth node from the end.
       - Step 3: Swap values `swap(firstK->data, secondK->data)`.
       - Time: O(N), Space: O(1).

    DRY RUN:
    Example: 1 -> 2 -> 3 -> 4 -> 5, k = 2
    - Step 1: Advance fast by k-1 = 1 step.
      fast points to node(2). firstK = node(2).
    - Step 2: secondK = head = node(1).
      Advance fast and secondK simultaneously:
      * fast = node(3), secondK = node(2)
      * fast = node(4), secondK = node(3)
      * fast = node(5) [fast->next is null], secondK = node(4).
      secondK points to node(4).
    - Step 3: Swap values of firstK (2) and secondK (4).
    - Result List: 1 -> 4 -> 3 -> 2 -> 5.
*/

#include <iostream>
#include <algorithm>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Two Pass Length Count (O(N) Time, O(1) Space)
// ============================================================================
class SolutionTwoPass {
public:
    Node* swapKth(Node* head, int k) {
        if (!head || k <= 0) return head;

        // Pass 1: Count length
        int num = 0;
        Node* curr = head;
        while (curr) {
            num++;
            curr = curr->next;
        }

        if (k > num) return head;

        // If kth node from start and end are the same node
        if (2 * k - 1 == num) return head;

        Node* firstK = head;
        for (int i = 1; i < k; i++) {
            firstK = firstK->next;
        }

        Node* secondK = head;
        for (int i = 1; i < num - k + 1; i++) {
            secondK = secondK->next;
        }

        swap(firstK->data, secondK->data);
        return head;
    }
};

// ============================================================================
// Approach 2: Single Pass 2-Pointer Technique (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* swapKth(Node* head, int k) {
        if (!head || k <= 0) return head;

        Node* fast = head;
        // Move fast pointer k - 1 steps to reach kth node from start
        for (int i = 1; i < k; i++) {
            if (!fast) return head; // k > length of list
            fast = fast->next;
        }

        if (!fast) return head; // k > length of list

        Node* firstK = fast;
        Node* secondK = head;

        // Move fast to tail while advancing secondK to find kth node from end
        while (fast->next != nullptr) {
            fast = fast->next;
            secondK = secondK->next;
        }

        swap(firstK->data, secondK->data);
        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* swapKth(Node* head, int k) {
        SolutionOptimal solver;
        return solver.swapKth(head, k);
    }

    Node* swapk(Node* head, int num, int k) {
        return swapKth(head, k);
    }
};
