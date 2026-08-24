/*
    Problem Name: Remove All Duplicates in a Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 82

    Problem Statement:
    Given the head of a sorted linked list, remove all nodes that have duplicate values, retaining ONLY
    nodes whose values appear exactly once in the original list. Return the head of the updated list.

    Examples:
    Input: 23 -> 28 -> 28 -> 35 -> 49 -> 49 -> nullptr
    Output: 23 -> 35 -> nullptr
    Explanation: 28 and 49 appear more than once, so both are completely removed.

    Input: 11 -> 11 -> 75 -> 75 -> nullptr
    Output: nullptr (Empty list)
    Explanation: All elements in the list have duplicates.

    Constraints:
    1 <= node->data <= 10^9
    1 <= number of nodes <= 10^5

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Frequency Map Counter (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Single Pass Dummy Pointer Traversal (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Frequency Map Approach (Approach 1):
       - Pass 1: Count frequency of each node value using `unordered_map<int, int> freq`.
       - Pass 2: Re-link nodes whose `freq[val] == 1` using a dummy node.
       - Time: O(N), Space: O(N).

    2. Optimal Dummy Pointer Traversal (Approach 2):
       - Use a `dummy` node (`new Node(-1)`) pointing to `head` and a `prev` pointer initialized to `dummy`.
       - Traverse `curr = head`:
         * If `curr` matches `curr->next`, skip all nodes with that same value in an inner loop.
           Link `prev->next = curr->next` to drop all duplicate instances.
         * Otherwise, `curr` is unique! Advance `prev = prev->next`.
       - Return `dummy->next`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 23 -> 28 -> 28 -> 35 -> 49 -> 49
    - dummy(-1) -> 23 -> 28 -> 28 -> 35 -> 49 -> 49
    - curr = 23 (no duplicate): prev moves to 23.
    - curr = 28 (duplicate found): skip both 28s -> prev(23)->next = 35.
    - curr = 35 (no duplicate): prev moves to 35.
    - curr = 49 (duplicate found): skip both 49s -> prev(35)->next = nullptr.
    - Result: 23 -> 35 -> nullptr.
*/

#include <iostream>
#include <unordered_map>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Frequency Map Counter (O(N) Time, O(N) Space)
// ============================================================================
class SolutionMapFrequency {
public:
    Node* removeAllDuplicates(Node* head) {
        if (!head || !head->next) return head;

        unordered_map<int, int> freq;
        Node* curr = head;
        while (curr != nullptr) {
            freq[curr->data]++;
            curr = curr->next;
        }

        Node* dummy = new Node(-1);
        Node* temp = dummy;

        curr = head;
        while (curr != nullptr) {
            if (freq[curr->data] == 1) {
                temp->next = curr;
                temp = temp->next;
            }
            curr = curr->next;
        }

        temp->next = nullptr;
        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// ============================================================================
// Approach 2: Single Pass Dummy Pointer Traversal (Optimal O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* removeAllDuplicates(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* dummy = new Node(-1);
        dummy->next = head;

        Node* prev = dummy;
        Node* curr = head;

        while (curr != nullptr) {
            // Check if curr has duplicate values following it
            if (curr->next != nullptr && curr->data == curr->next->data) {
                // Advance curr to the last node of the duplicates chain
                while (curr->next != nullptr && curr->data == curr->next->data) {
                    curr = curr->next;
                }
                // Skip all duplicates by linking prev past curr
                prev->next = curr->next;
            } else {
                // Node is unique, advance prev pointer
                prev = prev->next;
            }
            curr = curr->next;
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* removeAllDuplicates(Node* head) {
        SolutionOptimal solver;
        return solver.removeAllDuplicates(head);
    }
};
