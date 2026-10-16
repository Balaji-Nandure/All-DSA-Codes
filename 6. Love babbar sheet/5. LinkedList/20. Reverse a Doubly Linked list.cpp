/**
 * ============================================================================
 * Problem: Reverse a Doubly Linked List
 * Category: LinkedList / Doubly Linked List
 * 
 * Problem Statement:
 * Given a Doubly Linked List, reverse the list in-place such that all `next` and
 * `prev` pointers are properly inverted. Return the pointer to the head of the 
 * reversed doubly linked list.
 * 
 * Example:
 * Input:  NULL <- 3 <-> 4 <-> 5 -> NULL
 * Output: NULL <- 5 <-> 4 <-> 3 -> NULL
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Singly vs Doubly Linked Reversal:
 *    - In Singly Linked Lists (Problem 1), only the unidirectional `next` pointer
 *      was redirected backwards to `prev`.
 *    - In Doubly Linked Lists, every node possesses bidirectional links (`next` and `prev`).
 *    - To completely reverse a DLL, BOTH pointers of EVERY node must be swapped:
 *      `next` becomes `prev`, and `prev` becomes `next`.
 * 2. Navigating after Pointer Swapping:
 *    - After executing `swap(curr->next, curr->prev)`, `curr->next` now points to
 *      the PRECEDING node!
 *    - To advance forward through the original list, one must follow `curr->prev`!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * In-Place Pointer Swapping:
 *   - Base Case: If list is empty (`head == nullptr`) or has 1 node, return `head`.
 *   - Initialize: `curr = head`, `last = nullptr`.
 *   - While `curr != nullptr`:
 *       - Save `last = curr;` (to track the final non-null node as the new head).
 *       - Swap pointers: `swap(curr->next, curr->prev);`
 *       - Advance to next original node: `curr = curr->prev;` (since pointers swapped).
 *   - Return `last` (the original tail, which is now the new head).
 * ============================================================================
 */

#include <iostream>
#include <algorithm>

using namespace std;

// Definition for Doubly-Linked List node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution {
public:
    /**
     * Reverses a doubly linked list in-place in O(N) time and O(1) auxiliary space.
     * @param head Pointer to the head of the doubly linked list.
     * @return New head of the reversed doubly linked list.
     */
    Node* reverseDLL(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* curr = head;
        Node* last = nullptr;

        while (curr != nullptr) {
            last = curr;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Swapping 'next' and 'prev' inverts the bidirectional graph locally.
            // Following 'curr->prev' advances to the node that was originally NEXT.
            swap(curr->next, curr->prev);

            curr = curr->prev; // Advance using the newly swapped pointer
        }

        return last; // 'last' is now the new head of the reversed DLL
    }
};

void printDLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next) cout << " <-> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create Doubly Linked List: 3 <-> 4 <-> 5 -> NULL
    Node* head = new Node(3);
    Node* n2 = new Node(4);
    Node* n3 = new Node(5);

    head->next = n2;
    n2->prev = head;
    n2->next = n3;
    n3->prev = n2;

    cout << "Original DLL: ";
    printDLL(head);

    head = solver.reverseDLL(head);
    cout << "Reversed DLL: ";
    printDLL(head); // Expected: 5 <-> 4 <-> 3 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Single pass visiting all N nodes: O(N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. After swapping `curr->next` and `curr->prev`, always use `curr = curr->prev`
 *    to advance to the subsequent node in the original sequence.
 */
