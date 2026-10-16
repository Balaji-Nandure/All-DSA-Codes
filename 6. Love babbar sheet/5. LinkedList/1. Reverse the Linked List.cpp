/**
 * ============================================================================
 * Problem: Reverse a Linked List (Iterative and Recursive)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given the pointer to the head node of a singly linked list, reverse the linked
 * list and return the pointer to the head of the reversed list.
 * 
 * Example:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL
 * Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.val <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Sequential Pointer Manipulation vs Contiguous Arrays:
 *    - In arrays (Category 1, Problem 1), reversing is done in O(1) space by swapping
 *      elements via index arithmetic: `swap(arr[i], arr[n - 1 - i])`.
 *    - In singly linked lists, nodes are scattered across heap memory with ONLY 
 *      unidirectional forward pointers (`next`). There is NO random access and NO 
 *      backward pointer (`prev`).
 * 2. In-Place Pointer Inversion:
 *    - We cannot simply swap values across symmetric indices efficiently without
 *      incurring O(N^2) pointer traversals.
 *    - Instead, we mutate the structural graph itself: redirect each node's `next`
 *      pointer backwards to its predecessor.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: 3-Pointer Iterative Reversal (Gold Standard)
 *   - Use three pointers: `prev` (NULL), `curr` (head), `forward` (NULL).
 *   - At each step:
 *       1. Save `forward = curr->next` (otherwise connection to the rest of the list is lost!).
 *       2. Invert link: `curr->next = prev`.
 *       3. Slide forward: `prev = curr`, `curr = forward`.
 *   - When `curr` becomes NULL, `prev` is the new head.
 *   - Why this approach: O(N) time and strictly O(1) auxiliary space. Immune to stack overflow.
 * 
 * Approach 2: Recursive Reversal
 *   - Base Case: If list is empty or has only 1 node, return `head`.
 *   - Recursively reverse the rest of the list: `newHead = reverseRecursive(head->next)`.
 *   - Invert the pointer between head and head->next: `head->next->next = head`.
 *   - Break original link to prevent a cycle: `head->next = NULL`.
 *   - Return `newHead`.
 *   - Why know this: Fundamental paradigm for tree and linked list recursive thinking.
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Method 1: Iterative Pointer Reversal (O(N) Time, O(1) Space)
     * Recommended for production and competitive programming.
     */
    Node* reverseListIterative(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        Node* forward = nullptr;

        while (curr != nullptr) {
            forward = curr->next; // 1. Preserve reference to remaining list

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Inverting the arrow: Rather than pointing to the forward neighbor,
            // current node's pointer is redirected backward to 'prev'.
            curr->next = prev;

            prev = curr;          // 2. Advance prev to current
            curr = forward;       // 3. Advance current to forward
        }

        return prev; // 'prev' now rests on the new head of the reversed list
    }

    /**
     * Method 2: Recursive Reversal (O(N) Time, O(N) Call Stack)
     */
    Node* reverseListRecursive(Node* head) {
        // Base case: 0 or 1 node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Recursively reverse all nodes after head
        Node* newHead = reverseListRecursive(head->next);

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 'head->next' is the immediate child node. We make that child point BACK to 'head'.
        head->next->next = head;
        head->next = nullptr; // Sever old forward pointer to prevent cycle

        return newHead;
    }
};

// Helper utilities for demonstration
void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create linked list: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

    cout << "Original List:         ";
    printList(head);

    // Test Iterative Reversal
    head = solver.reverseListIterative(head);
    cout << "Reversed (Iterative):  ";
    printList(head);

    // Test Recursive Reversal (reversing again restores original order)
    head = solver.reverseListRecursive(head);
    cout << "Reversed (Recursive):  ";
    printList(head);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Iterative Method:
 *   - Time Complexity: O(N) - Single pass through all N nodes.
 *   - Space Complexity: O(1) - Three pointer variables (`prev`, `curr`, `forward`).
 * 
 * Recursive Method:
 *   - Time Complexity: O(N) - Visited once during recursion unwinding.
 *   - Space Complexity: O(N) - Call stack depth equals list length N.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always stash `curr->next` into a temporary `forward` pointer BEFORE mutating `curr->next`.
 * 2. In recursive reversal, `head->next->next = head` directly connects the
 *    reversed sublist tail back to `head`, eliminating the need to traverse to the end.
 */
