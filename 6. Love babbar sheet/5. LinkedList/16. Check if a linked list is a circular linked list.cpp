/**
 * ============================================================================
 * Problem: Check if a Linked List is Circular
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given head of a singly linked list, determine whether the list is circular.
 * A linked list is circular if it is not NULL-terminated and the last node 
 * points back directly to the FIRST node (the head) of the list.
 * 
 * Note: An empty list is considered circular.
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Circular Linked List vs Generic Loop (Problem 3):
 *    - In Problem 3 (Detect Loop), any cycle anywhere in the list qualified as a loop
 *      (e.g., 1 -> 2 -> 3 -> 4 -> 2, where loop starts at 2, not 1).
 *    - In a true Circular Linked List, the cycle MUST close specifically at the HEAD node
 *      (e.g., 1 -> 2 -> 3 -> 4 -> 1).
 *    - A list with a loop that does not include the head is NOT a circular linked list!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach: Single Pointer Traversal with Cycle Invariant
 *   - Case 1: Empty list (`head == nullptr`) -> return true by definition.
 *   - Start `curr = head->next`.
 *   - Traverse while `curr != nullptr` and `curr != head`:
 *       `curr = curr->next;`
 *   - If `curr == head`: The list closed back on the root -> return true.
 *   - If `curr == nullptr`: The list terminated linearly -> return false.
 *   - Note: If there is a possibility of a generic middle loop (where curr gets trapped
 *     without reaching head), we use Floyd's Tortoise and Hare with the check
 *     that the collision entrance must equal `head`.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Determines whether the given linked list is circular.
     * @param head Pointer to the head of the linked list.
     * @return true if circular, false otherwise.
     */
    bool isCircular(Node* head) {
        // An empty list is circular by standard definition
        if (head == nullptr) return true;

        Node* curr = head->next;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // A circular linked list requires the cycle to terminate precisely at 'head',
        // whereas a general looped list may cycle internally without ever touching 'head'.
        while (curr != nullptr && curr != head) {
            curr = curr->next;
        }

        // If curr wrapped all the way back to head, it is circular!
        return (curr == head);
    }

    /**
     * Robust check handling arbitrary middle loops using Floyd's Tortoise and Hare.
     */
    bool isCircularRobust(Node* head) {
        if (head == nullptr) return true;

        Node* slow = head;
        Node* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }

        // If fast reached NULL, it's linear (not circular)
        if (fast == nullptr || fast->next == nullptr) return false;

        // Check if the loop starts at head
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return (slow == head);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Truly circular list: 1 -> 2 -> 3 -> 4 -> 1
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = head1; // Connect back to head

    cout << "Test 1 (Circular to Head): " 
         << (solver.isCircular(head1) ? "YES" : "NO") << " (Expected: YES)\n";

    // Test Case 2: Linear list: 10 -> 20 -> 30 -> NULL
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);

    cout << "Test 2 (Linear NULL):     " 
         << (solver.isCircular(head2) ? "YES" : "NO") << " (Expected: NO)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - At most N nodes are traversed before hitting either head or NULL.
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Distinction between a "looped list" (arbitrary cycle) and a "circular list"
 *    (cycle strictly anchored at the head).
 */
