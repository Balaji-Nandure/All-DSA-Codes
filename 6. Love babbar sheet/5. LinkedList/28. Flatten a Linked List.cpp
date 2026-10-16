/**
 * ============================================================================
 * Problem: Flattening a Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a Linked List of size N, where every node represents a sub-linked-list 
 * and contains two pointers:
 *   1. `next` pointer to the next node in the horizontal main list.
 *   2. `bottom` (or `child`) pointer to a vertical sub-linked-list where this node is head.
 * 
 * Each of the vertical sub-linked-lists is ALREADY SORTED in ascending order.
 * Flatten the entire 2D structure into a single 1D linked list sorted in ascending
 * order, connected via the `bottom` pointers (with `next` pointers set to NULL).
 * 
 * Example:
 *   5 -> 10 -> 19 -> 28
 *   |    |     |     |
 *   7    20    22    35
 *   |          |     |
 *   8          50    40
 *   |                |
 *   30               45
 * 
 * Output: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50
 * 
 * Constraints:
 * 1 <= Total Nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. 2D Orthogonal Pointers (`next` horizontal, `bottom` vertical):
 *    - In standard 1D linked lists, nodes only have 1 forward link.
 *    - Here, the data structure is a 2D sparse tree/grid where each horizontal
 *      column is an independently sorted vertical list.
 * 2. Multi-Way Merge Reduced to Recursive 2-Way Merge:
 *    - Instead of merging all vertical lists simultaneously, we recursively flatten
 *      from right to left: flatten the tail column first, then merge the current
 *      column with the already-flattened result.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Recursive 2-Way Merge (The Standard & Optimal Pattern):
 *   - Base Case: If `root == nullptr` or `root->next == nullptr`, return `root`.
 *   - Step 1: Recursively flatten all horizontal lists to the right:
 *       `root->next = flatten(root->next);`
 *   - Step 2: Merge current vertical list (`root`) with the flattened right list (`root->next`):
 *       `root = mergeTwoLists(root, root->next);`
 *   - Step 3: Return `root`.
 * 
 * Merging Two Vertical Lists (`bottom` pointers):
 *   - Compare `a->data` and `b->data`.
 *   - Follow the smaller node and recursively or iteratively link via `result->bottom`.
 *   - Set `result->next = nullptr`.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* bottom;
    Node(int val) : data(val), next(nullptr), bottom(nullptr) {}
};

class Solution {
private:
    /**
     * Merges two sorted vertical lists (linked via 'bottom' pointers) into one.
     */
    Node* merge(Node* a, Node* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;

        Node* result = nullptr;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Standard merge adapted to 2D orthogonal pointers: link elements along
        // the vertical 'bottom' axis while severing the horizontal 'next' links.
        if (a->data <= b->data) {
            result = a;
            result->bottom = merge(a->bottom, b);
        } else {
            result = b;
            result->bottom = merge(a, b->bottom);
        }

        result->next = nullptr; // Ensure horizontal pointer is cleared
        return result;
    }

public:
    /**
     * Flattens a 2D multi-level sorted linked list into a single sorted vertical list.
     * @param root Pointer to the head node of the 2D linked list.
     * @return Head of the flattened sorted list (linked via 'bottom').
     */
    Node* flatten(Node* root) {
        // Base case: empty list or only one vertical chain remaining
        if (root == nullptr || root->next == nullptr) {
            return root;
        }

        // Recursively flatten the right sublist
        root->next = flatten(root->next);

        // Merge current vertical chain with the flattened right list
        root = merge(root, root->next);

        return root;
    }
};

void printFlattenedList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->bottom) cout << " -> ";
        temp = temp->bottom;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Build sample 2D linked list
    // 5 -> 10 -> 19 -> 28
    // |    |     |     |
    // 7    20    22    35
    // |          |     |
    // 8          50    40
    // |                |
    // 30               45

    Node* head = new Node(5);
    head->bottom = new Node(7);
    head->bottom->bottom = new Node(8);
    head->bottom->bottom->bottom = new Node(30);

    head->next = new Node(10);
    head->next->bottom = new Node(20);

    head->next->next = new Node(19);
    head->next->next->bottom = new Node(22);
    head->next->next->bottom->bottom = new Node(50);

    head->next->next->next = new Node(28);
    head->next->next->next->bottom = new Node(35);
    head->next->next->next->bottom->bottom = new Node(40);
    head->next->next->next->bottom->bottom->bottom = new Node(45);

    Node* flattened = solver.flatten(head);
    cout << "Flattened Sorted List:\n";
    printFlattenedList(flattened);
    // Expected: 5 -> 7 -> 8 -> 10 -> 19 -> 20 -> 22 -> 28 -> 30 -> 35 -> 40 -> 45 -> 50 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Let K be the number of vertical columns, and M be the average nodes per column.
 *   - Total nodes N = K * M.
 *   - Merging column K with column K-1 takes O(2M), then with K-2 takes O(3M)...
 *   - Total Time: O(M * (2 + 3 + ... + K)) = O(M * K^2) = O(N * K).
 *   - (Note: Using a Min-Heap of size K brings this down to O(N log K)).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(K) recursion stack frames.
 *   - In-place pointer rewiring: O(1) heap allocation.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Flattening multi-level sorted lists is fundamentally a multi-way merge problem.
 * 2. Unwinding from right to left simplifies the code into clean 2-way merges.
 */
