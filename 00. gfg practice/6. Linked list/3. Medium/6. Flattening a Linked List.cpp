/*
    Problem Name: Flattening a Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    In a 2D linked list, every node has two pointers: `next` and `bottom`. The heads of n linked lists
    are connected using the `next` pointer, while the `bottom` pointer points to the next node in the
    current vertical linked list.
    Each vertical linked list is sorted in non-decreasing order of data, and the head nodes are also sorted.
    Flatten the 2D linked lists into a single sorted linked list connected ONLY using `bottom` pointers.

    Examples:
    Input:
    5 -> 10 -> 19 -> 28
    |    |     |     |
    7    20    22    35
    |          |
    8          50
    |
    30

    Output:
    5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 50 (connected via bottom pointers)

    Constraints:
    0 <= n <= 10^4
    1 <= number of nodes in each list <= 50
    1 <= node->data <= 5 * 10^5

    Expected Complexities:
    Time Complexity: O(N * M), where N is number of main head nodes and M is average nodes per vertical list.
    Space Complexity: O(N) recursion stack space.

    Approach 1: Brute Force — Copy All Values to Array & Sort (O(N * M log(N * M)) Time, O(N * M) Space - Striver & Love Babbar)
    Approach 2: Optimal — Recursively Flatten Right & Merge 2 Bottom Lists (O(N * M) Time, O(N) Stack Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Brute Force (Approach 1):
       - Traverse every main list using `next` and its vertical chain using `bottom`.
       - Collect all values into `vector<int> arr`, sort `arr`, and reconstruct a single bottom-linked list.
       - Time: O(N * M log(N * M)), Space: O(N * M).

    2. Optimal Recursive Merge (Approach 2):
       - Helper `merge(list1, list2)`: Merges two sorted `bottom` linked lists using dummy node,
         similar to 2-way Merge Sort.
       - `flatten(head)` function:
         * Base Case: If `head == nullptr || head->next == nullptr`, return `head`.
         * Recurse to flatten the right side: `head->next = flatten(head->next);`.
         * Merge current vertical list (`head`) with the flattened right list (`head->next`).
         * Return `merge(head, head->next)`.
       - Time: O(N * M), Space: O(N) recursion call stack.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for 2D Linked List Node
struct Node {
    int data;
    Node* next;
    Node* bottom;
    Node(int val) : data(val), next(nullptr), bottom(nullptr) {}
};

// ============================================================================
// Approach 1: Brute Force — Copy All Values to Vector & Sort (O(N*M log(N*M)) Space)
// ============================================================================
class SolutionVectorSort {
public:
    Node* flatten(Node* head) {
        if (!head) return nullptr;

        vector<int> arr;
        Node* mainPtr = head;

        // Collect all node data
        while (mainPtr != nullptr) {
            Node* bottomPtr = mainPtr;
            while (bottomPtr != nullptr) {
                arr.push_back(bottomPtr->data);
                bottomPtr = bottomPtr->bottom;
            }
            mainPtr = mainPtr->next;
        }

        // Sort all values
        sort(arr.begin(), arr.end());

        // Reconstruct a single bottom-linked list
        Node* dummy = new Node(-1);
        Node* curr = dummy;

        for (int val : arr) {
            curr->bottom = new Node(val);
            curr = curr->bottom;
        }

        Node* result = dummy->bottom;
        delete dummy;
        return result;
    }
};

// ============================================================================
// Approach 2: Optimal — Recursively Flatten Right & Merge 2 Bottom Lists (O(N*M) Time)
// ============================================================================
class SolutionMergeOptimal {
private:
    // Helper function to merge two sorted bottom-linked lists
    Node* merge(Node* list1, Node* list2) {
        Node dummy(-1);
        Node* temp = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->data <= list2->data) {
                temp->bottom = list1;
                temp = list1;
                list1 = list1->bottom;
            } else {
                temp->bottom = list2;
                temp = list2;
                list2 = list2->bottom;
            }
            temp->next = nullptr; // Ensure next pointers are cleared
        }

        if (list1 != nullptr) {
            temp->bottom = list1;
        } else {
            temp->bottom = list2;
        }

        return dummy.bottom;
    }

public:
    Node* flatten(Node* head) {
        // Base Case: If empty or only one list remains, it's already flattened
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Recursively flatten everything to the right
        head->next = flatten(head->next);

        // Step 2: Merge current vertical list with flattened right side
        head = merge(head, head->next);

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* flatten(Node* head) {
        SolutionMergeOptimal solver;
        return solver.flatten(head);
    }
};

// ============================================================================
// Helper Functions for Testing
// ============================================================================

// Helper to create a bottom list from a vector
Node* createBottomList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for (size_t i = 1; i < values.size(); i++) {
        curr->bottom = new Node(values[i]);
        curr = curr->bottom;
    }
    return head;
}

// Helper to print flattened bottom list
void printBottomList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->bottom) cout << " -> ";
        curr = curr->bottom;
    }
    cout << "\n";
}

int main() {
    // Example 1:
    // 5 -> 10 -> 19 -> 28
    // |    |     |     |
    // 7    20    22    35
    // |          |
    // 8          50
    // |
    // 30
    Node* l1 = createBottomList({5, 7, 8, 30});
    Node* l2 = createBottomList({10, 20});
    Node* l3 = createBottomList({19, 22, 50});
    Node* l4 = createBottomList({28, 35});

    l1->next = l2;
    l2->next = l3;
    l3->next = l4;

    SolutionMergeOptimal solver;
    Node* flattenedHead = solver.flatten(l1);

    cout << "Example 1 Flattened List:\n";
    printBottomList(flattenedHead);

    return 0;
}
