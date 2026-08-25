/*
    Problem Name: Reverse Alternate K in Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a linked list and an integer k, reverse every alternate group of k nodes,
    starting with the first group.
    If the number of nodes left at the end is fewer than k, handle them according to the alternation pattern.

    Examples:
    Input: head = 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> nullptr, k = 2
    Output: 2 -> 1 -> 3 -> 4 -> 6 -> 5 -> nullptr
    Explanation: Group 1 (1,2) reversed -> 2->1. Group 2 (3,4) skipped -> 3->4. Group 3 (5,6) reversed -> 6->5.

    Input: head = 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> nullptr, k = 3
    Output: 3 -> 2 -> 1 -> 4 -> 5 -> 6 -> 8 -> 7 -> nullptr
    Explanation: Group 1 (1,2,3) reversed -> 3->2->1. Group 2 (4,5,6) skipped -> 4->5->6. Group 3 (7,8) reversed -> 8->7.

    Constraints:
    1 <= number of nodes, node->data <= 10^5
    1 <= k <= N

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(N/k) recursive call stack space or O(1) iterative auxiliary space.

    Approach 1: Backtracking Recursion (O(N) Time, O(N/k) Stack Space - Striver & Love Babbar)
    Approach 2: Iterative with Dummy Node (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Backtracking Recursion (Approach 1):
       - Step 1: Reverse first `k` nodes using standard 3-pointer reversal (`prev`, `curr`, `nextNode`).
       - Step 2: Connect `head->next = curr` (since original head is now tail of reversed group).
       - Step 3: Skip next `k - 1` nodes to reach the tail of the skipped group.
       - Step 4: Recursively call `kAltReverse(curr->next, k)` for remaining list.
       - Return `prev` (new head of the reversed first group).
       - Time: O(N), Space: O(N/k) stack space.

    2. Iterative with Dummy Node (Approach 2):
       - Maintain `dummy = new Node(-1)` pointing to `head`, `prevTail = dummy`, and boolean flag `shouldReverse = true`.
       - Outer loop while `curr != nullptr`:
         * If `shouldReverse` is true: Reverse next `k` nodes, update `prevTail->next`, and advance `prevTail`.
         * If `shouldReverse` is false: Simply advance `curr` and `prevTail` `k` steps forward without reversing.
         * Toggle `shouldReverse = !shouldReverse`.
       - Return `dummy->next`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
    - Group 1 (reverse 2 nodes): 1 -> 2 becomes 2 -> 1. prev = node(2), curr = node(3), head = node(1).
      Link head(1)->next = curr(3).
    - Skip Group 2 (2 nodes): Move curr from 3 to 4.
    - Recurse on remaining list starting from curr->next(5):
      Group 3 (reverse 2 nodes): 5 -> 6 becomes 6 -> 5.
    - Result: 2 -> 1 -> 3 -> 4 -> 6 -> 5 -> nullptr.
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
// Approach 1: Backtracking Recursion (O(N) Time, O(N/k) Stack Space)
// ============================================================================
class SolutionRecursive {
public:
    Node* kAltReverse(Node* head, int k) {
        if (head == nullptr) return nullptr;

        Node* prev = nullptr;
        Node* curr = head;
        Node* nextNode = nullptr;
        int count = 0;

        // Step 1: Reverse first k nodes
        while (curr != nullptr && count < k) {
            nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
            count++;
        }

        // Step 2: Link original head (now tail of reversed group) to current (start of next group)
        if (head != nullptr) {
            head->next = curr;
        }

        // Step 3: Skip next k - 1 nodes to reach tail of the skipped group
        count = 0;
        while (curr != nullptr && count < k - 1) {
            curr = curr->next;
            count++;
        }

        // Step 4: Recursively call for the rest of the list
        if (curr != nullptr) {
            curr->next = kAltReverse(curr->next, k);
        }

        // Return new head of the reversed group
        return prev;
    }
};

// ============================================================================
// Approach 2: Iterative with Dummy Node (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionIterative {
public:
    Node* kAltReverse(Node* head, int k) {
        if (head == nullptr || k <= 1) return head;

        Node* dummy = new Node(-1);
        dummy->next = head;

        Node* prevTail = dummy;
        Node* curr = head;
        bool shouldReverse = true;

        while (curr != nullptr) {
            if (shouldReverse) {
                Node* groupStart = curr;
                Node* prev = nullptr;
                int count = 0;

                while (curr != nullptr && count < k) {
                    Node* nextNode = curr->next;
                    curr->next = prev;
                    prev = curr;
                    curr = nextNode;
                    count++;
                }

                prevTail->next = prev;
                groupStart->next = curr;
                prevTail = groupStart;
            } else {
                int count = 0;
                while (curr != nullptr && count < k) {
                    prevTail = curr;
                    curr = curr->next;
                    count++;
                }
            }

            shouldReverse = !shouldReverse; // Toggle alternation
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* kAltReverse(Node* head, int k) {
        SolutionIterative solver;
        return solver.kAltReverse(head, k);
    }
};
