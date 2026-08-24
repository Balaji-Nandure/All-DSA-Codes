/*
    Problem Name: Rearrange a linked list (Odd Even Linked List)
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 328

    Problem Statement:
    Given a singly linked list, rearrange it in a way that all odd position nodes are together
    followed by all even position nodes (1-based indexing). Preserve the relative order of nodes.

    Examples:
    Input: 1 -> 2 -> 3 -> 4 -> nullptr
    Output: 1 -> 3 -> 2 -> 4 -> nullptr
    Explanation: Odd position nodes (1, 3) followed by even position nodes (2, 4).

    Input: 1 -> 2 -> 3 -> 4 -> 5 -> nullptr
    Output: 1 -> 3 -> 5 -> 2 -> 4 -> nullptr
    Explanation: Odd position nodes (1, 3, 5) followed by even position nodes (2, 4).

    Constraints:
    1 <= number of nodes <= 10^4
    0 <= node->data <= 10^3

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Storage & Value Copy (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: In-Place Odd-Even Pointer Linking (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Traverse list, push odd-indexed values to `odds` and even-indexed values to `evens`.
       - Overwrite node values sequentially with `odds` then `evens`.
       - Time: O(N), Space: O(N).

    2. Optimal Pointer Linking (Approach 2):
       - Maintain `odd` pointer starting at `head` and `even` pointer starting at `head->next`.
       - Keep reference to `evenHead = even`.
       - In each step:
         * `odd->next = even->next` and move `odd = odd->next`.
         * `even->next = odd->next` and move `even = even->next`.
       - When loop terminates (`even == nullptr || even->next == nullptr`), attach `odd->next = evenHead`.
       - Time: O(N), Space: O(1).

    DRY RUN:
    Example: 1 -> 2 -> 3 -> 4 -> 5
    - Initial: odd = 1, even = 2, evenHead = 2
    - Iteration 1:
      odd->next = 3, odd = 3  (Odd sublist: 1 -> 3)
      even->next = 4, even = 4 (Even sublist: 2 -> 4)
    - Iteration 2:
      odd->next = 5, odd = 5  (Odd sublist: 1 -> 3 -> 5)
      even->next = nullptr, even = nullptr (Even sublist: 2 -> 4 -> nullptr)
    - Loop ends (even is nullptr).
    - Connect: odd(5)->next = evenHead(2).
    - Result: 1 -> 3 -> 5 -> 2 -> 4 -> nullptr.
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
// Approach 1: Vector Storage & Value Copy (O(N) Time, O(N) Space)
// ============================================================================
class SolutionVector {
public:
    void rearrange(Node* head) {
        if (!head || !head->next) return;

        vector<int> odds, evens;
        Node* curr = head;
        int index = 1;

        while (curr != nullptr) {
            if (index % 2 != 0) odds.push_back(curr->data);
            else evens.push_back(curr->data);
            curr = curr->next;
            index++;
        }

        curr = head;
        for (int val : odds) {
            curr->data = val;
            curr = curr->next;
        }
        for (int val : evens) {
            curr->data = val;
            curr = curr->next;
        }
    }
};

// ============================================================================
// Approach 2: In-Place Odd-Even Pointer Linking (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    void rearrange(Node* head) {
        if (head == nullptr || head->next == nullptr) return;

        Node* odd = head;
        Node* even = head->next;
        Node* evenHead = even;

        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;
            odd = odd->next;

            even->next = odd->next;
            even = even->next;
        }

        // Attach even list at the end of odd list
        odd->next = evenHead;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    void rearrange(Node* head) {
        SolutionOptimal solver;
        solver.rearrange(head);
    }
};
