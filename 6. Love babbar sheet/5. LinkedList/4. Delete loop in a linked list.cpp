/**
 * ============================================================================
 * Problem: Detect and Remove Loop in a Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, determine if it has a cycle. If a cycle exists,
 * break the cycle by setting the `next` pointer of the last node in the loop to NULL.
 * Return the modified list without any memory leaks or loops.
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.val <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Detection vs Structural Surgical Remediation:
 *    - Problem 3 only required returning a boolean (`true`/`false`).
 *    - Here, we must locate the EXACT last node in the cycle (the node pointing
 *      back to the loop start) and sever its `next` pointer to restore linearity.
 * 2. Mathematical Synchrony (Floyd's Phase 2):
 *    - Distance from head to cycle entrance: L
 *    - Distance from entrance to collision point: d
 *    - Perimeter of cycle: C
 *    - Proof:
 *        Dist(slow) = L + d
 *        Dist(fast) = L + d + k * C
 *        2 * (L + d) = L + d + k * C  ===>  L = (k * C) - d = (k - 1)*C + (C - d)
 *      (C - d) is the exact remaining distance from collision point back to the cycle start!
 *    - Therefore, a pointer starting from `head` and a pointer starting from collision point
 *      moving at identical 1x speeds will meet EXACTLY at the loop entrance!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Step 1: Detect Collision Point using Slow and Fast pointers.
 *   - If fast reaches NULL, no loop exists, return head.
 * Step 2: Handle Edge Case where Loop Starts at Head (L = 0):
 *   - If slow == head: The loop is circular. Traverse `fast` until `fast->next == head`,
 *     then set `fast->next = NULL`.
 * Step 3: General Case (L > 0):
 *   - Reset `slow = head`.
 *   - Advance both `slow` and `fast` simultaneously 1 step at a time until
 *     `slow->next == fast->next`.
 *   - When they match, `fast` is sitting on the LAST node of the cycle!
 *   - Set `fast->next = NULL` to break the loop cleanly.
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
     * Detects and removes the loop from the linked list.
     * @param head Pointer to the head of the list.
     */
    void removeLoop(Node* head) {
        if (head == nullptr || head->next == nullptr) return;

        Node* slow = head;
        Node* fast = head;
        bool hasCycle = false;

        // Step 1: Find collision point
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }

        // If no cycle exists, nothing to remove
        if (!hasCycle) return;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Special Case: The loop connects directly back to the head node (L = 0).
        // If slow == head, both pointers are already at the entrance.
        // We must advance 'fast' around the loop until fast->next == head, then break.
        if (slow == head) {
            while (fast->next != head) {
                fast = fast->next;
            }
            fast->next = nullptr; // Sever circular link
            return;
        }

        // Step 2 & 3: General Case (L > 0)
        // Reset slow to head; move both slow and fast at 1x speed.
        slow = head;
        while (slow->next != fast->next) {
            slow = slow->next;
            fast = fast->next;
        }

        // 'fast' is now precisely the tail node of the cycle pointing to slow->next (the loop start).
        fast->next = nullptr; // Sever loop link!
    }
};

void printList(Node* head) {
    Node* temp = head;
    int limit = 20; // Guard against infinite prints in case of loop
    while (temp != nullptr && limit--) {
        cout << temp->data;
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    if (limit <= 0) cout << " ... (potential loop!)";
    else cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: General loop
    // 1 -> 2 -> 3 -> 4 -> 5 -> loop back to 3
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = head1->next->next; // 5 -> 3

    cout << "Test 1: Removing loop from 5 -> 3...\n";
    solver.removeLoop(head1);
    cout << "Result List 1: ";
    printList(head1);

    // Test Case 2: Loop back to head (circular list)
    // 10 -> 20 -> 30 -> loop back to 10
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);
    head2->next->next->next = head2; // 30 -> 10

    cout << "\nTest 2: Removing circular loop back to head...\n";
    solver.removeLoop(head2);
    cout << "Result List 2: ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Phase 1 (Loop Detection): O(N).
 *   - Phase 2 (Loop Removal): At most O(N) to advance slow and fast to meeting point.
 *   - Total Time Complexity: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Never miss the `slow == head` edge case where the loop root is the head itself.
 * 2. Advance until `slow->next == fast->next` rather than `slow == fast` so that
 *    `fast` remains positioned on the last node of the cycle whose link needs to be cleared.
 */
