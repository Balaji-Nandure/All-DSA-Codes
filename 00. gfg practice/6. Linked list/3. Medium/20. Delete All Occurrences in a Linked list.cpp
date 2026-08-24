/*
    Problem Name: Delete All Occurrences in a Linked list
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a singly linked list `head` and an integer `x`, delete all occurrences of key `x` from the linked list
    and return the head of the modified list.

    Examples:
    Input: 2 -> 2 -> 1 -> 4 -> 4 -> nullptr, x = 4
    Output: 2 -> 2 -> 1 -> nullptr
    Explanation: After deleting all occurrences of 4, remaining list is 2 -> 2 -> 1.

    Input: 1 -> 2 -> 2 -> 3 -> 2 -> 3 -> nullptr, x = 2
    Output: 1 -> 3 -> 3 -> nullptr
    Explanation: After deleting all occurrences of 2, remaining list is 1 -> 3 -> 3.

    Constraints:
    1 <= size of linked list <= 10^5
    1 <= x, node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Filter & Rebuild (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Dummy Node Single Pass Traversal (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect values `!= x` into `vector<int> filtered`.
       - Reconstruct a linked list from `filtered`.
       - Time: O(N), Space: O(N).

    2. Optimal Dummy Pointer Traversal (Approach 2):
       - Create a `dummy = new Node(-1)` node pointing to `head` (handles head node deletion easily!).
       - Maintain `prev = dummy` and `curr = head`.
       - Traverse list:
         * If `curr->data == x`, unlink `curr` (`prev->next = curr->next`), free memory `delete curr`,
           and advance `curr = prev->next`.
         * Else, advance `prev = curr` and `curr = curr->next`.
       - Return `dummy->next`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 1 -> 2 -> 2 -> 3 -> 2 -> 3, x = 2
    - dummy(-1) -> 1 -> 2 -> 2 -> 3 -> 2 -> 3
    - curr(1) != 2: prev = 1, curr = 2
    - curr(2) == 2: prev(1)->next = 2, delete 2, curr = 2
    - curr(2) == 2: prev(1)->next = 3, delete 2, curr = 3
    - curr(3) != 2: prev = 3, curr = 2
    - curr(2) == 2: prev(3)->next = 3, delete 2, curr = 3
    - curr(3) != 2: prev = 3, curr = nullptr
    - Result: 1 -> 3 -> 3 -> nullptr.
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
// Approach 1: Vector Filter & Rebuild (O(N) Time, O(N) Space)
// ============================================================================
class SolutionVectorFilter {
public:
    Node* deleteAllOccurrences(Node* head, int x) {
        if (!head) return nullptr;

        vector<int> filtered;
        Node* curr = head;

        while (curr != nullptr) {
            if (curr->data != x) {
                filtered.push_back(curr->data);
            }
            curr = curr->next;
        }

        if (filtered.empty()) return nullptr;

        Node* dummy = new Node(-1);
        Node* temp = dummy;
        for (int val : filtered) {
            temp->next = new Node(val);
            temp = temp->next;
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// ============================================================================
// Approach 2: Dummy Node Single Pass Traversal (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* deleteAllOccurrences(Node* head, int x) {
        if (!head) return nullptr;

        Node* dummy = new Node(-1);
        dummy->next = head;

        Node* prev = dummy;
        Node* curr = head;

        while (curr != nullptr) {
            if (curr->data == x) {
                prev->next = curr->next; // Unlink node
                Node* toDelete = curr;
                curr = curr->next;       // Advance curr
                delete toDelete;         // Free memory
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* deleteAllOccurrences(Node* head, int x) {
        SolutionOptimal solver;
        return solver.deleteAllOccurrences(head, x);
    }

    void deleteAllOccurrences(Node** head_ref, int x) {
        if (head_ref && *head_ref) {
            *head_ref = deleteAllOccurrences(*head_ref, x);
        }
    }
};
