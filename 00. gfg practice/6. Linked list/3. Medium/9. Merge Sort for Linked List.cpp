/*
    Problem Name: Merge Sort for Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 148

    Problem Statement:
    Given the head of a singly linked list, sort the linked list in non-decreasing order using the
    Merge Sort algorithm and return the head of the sorted list.

    Examples:
    Input: 3 -> 5 -> 2 -> 4 -> nullptr
    Output: 2 -> 3 -> 4 -> 5 -> nullptr

    Input: 50 -> 40 -> 30 -> 20 -> 10 -> 60 -> nullptr
    Output: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> nullptr

    Constraints:
    1 <= number of nodes <= 10^5
    0 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N log N)
    Space Complexity: O(log N) recursive call stack space.

    Approach 1: Naive — Copy to Vector & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Optimal — Divide & Conquer Linked List Merge Sort (O(N log N) Time, O(log N) Stack Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Naive Vector Copy (Approach 1):
       - Traverse list, copy all values to `vector<int> arr`, sort `arr`, overwrite node values.
       - Time: O(N log N), Space: O(N).

    2. Optimal Linked List Merge Sort (Approach 2):
       - Step 1 (Find Middle & Split): Use fast (2 steps) and slow (1 step starting at head) pointers
         to find the middle node `mid`. Disconnect `mid->next` to split list into two independent halves: `left` and `right`.
       - Step 2 (Recursive Sort): Recursively call `mergeSort(head)` and `mergeSort(rightHead)` to sort both halves.
       - Step 3 (Merge 2 Sorted Lists): Merge the two sorted linked lists using a 2-pointer merge strategy
         with a dummy node.
       - Time: O(N log N), Space: O(log N) recursion call stack space.

    DRY RUN:
    Example: 4 -> 2 -> 1 -> 3
    - Step 1 (Split):
      getMiddle(4 -> 2 -> 1 -> 3) returns node(2).
      Left half: 4 -> 2 -> nullptr
      Right half: 1 -> 3 -> nullptr
    - Step 2 (Recursive Sort):
      Left sorted: 2 -> 4
      Right sorted: 1 -> 3
    - Step 3 (Merge):
      merge(2 -> 4, 1 -> 3)
      - Compare 2 vs 1 -> pick 1
      - Compare 2 vs 3 -> pick 2
      - Compare 4 vs 3 -> pick 3
      - Remaining -> pick 4
      Result: 1 -> 2 -> 3 -> 4
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
// Approach 1: Naive — Copy to Vector & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionVectorSort {
public:
    Node* mergeSort(Node* head) {
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
// Approach 2: Optimal — Linked List Divide & Conquer Merge Sort (O(N log N) Time, O(log N) Space)
// ============================================================================
class SolutionMergeSort {
private:
    // ========================================================================
    // IMPORTANT DSA NOTE ON SLOW & FAST POINTER INITIALIZATION:
    // ========================================================================
    // 1. `slow = head`, `fast = head->next` (First Middle Node in even lengths):
    //    - CRITICAL for Merge Sort!
    //    - For 2 nodes (e.g. 1 -> 2): `slow` lands on node 1 (first middle).
    //      Splits list cleanly into: Left (1 -> null) and Right (2 -> null).
    //    - Avoids Infinite Recursion Stack Overflow!
    //
    // 2. `slow = head`, `fast = head` (Second Middle Node in even lengths):
    //    - Used in Palindrome check or standard Middle element finding.
    //    - For 2 nodes (e.g. 1 -> 2): `slow` lands on node 2 (second middle).
    //      If used in Merge Sort, `mid->next` splitting fails for 2 nodes,
    //      causing infinite recursion loop.
    // ========================================================================
    Node* getMiddle(Node* head) {
        if (head == nullptr) return head;

        Node* slow = head;
        Node* fast = head->next; // First middle node for even lengths

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    // Helper function to merge two sorted linked lists using new Node(-1)
    Node* merge(Node* left, Node* right) {
        Node* dummy = new Node(-1); // Heap allocation (User Preferred Style)
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

        if (left != nullptr) {
            temp->next = left;
        } else {
            temp->next = right;
        }

        Node* result = dummy->next;
        delete dummy; // Clean up heap dummy node
        return result;
    }

public:
    Node* mergeSort(Node* head) {
        // Base Case: 0 or 1 element is already sorted
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Split the linked list into two halves
        Node* mid = getMiddle(head);
        Node* rightHead = mid->next;
        mid->next = nullptr; // Disconnect left and right halves

        // Step 2: Recursively sort left and right halves
        Node* left = mergeSort(head);
        Node* right = mergeSort(rightHead);

        // Step 3: Merge the two sorted halves
        return merge(left, right);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* mergeSort(Node* head) {
        SolutionMergeSort solver;
        return solver.mergeSort(head);
    }
};
