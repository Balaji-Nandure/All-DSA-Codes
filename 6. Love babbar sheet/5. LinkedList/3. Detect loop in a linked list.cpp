/**
 * ============================================================================
 * Problem: Detect Loop in a Linked List (Floyd's Cycle-Finding Algorithm)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, determine whether the list contains a cycle (loop).
 * A loop exists if a node's next pointer points to a previously visited node,
 * causing an infinite traversal.
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.val <= 10^9
 * Must run in O(N) time and O(1) auxiliary space without modifying the list.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Infinite Topology vs Linear Termination:
 *    - In all previous linked list problems, lists were strictly linear, ending
 *      with a terminating `NULL` sentinel.
 *    - With a cycle, a naive traversal `while (curr != NULL) curr = curr->next;`
 *      will run indefinitely into an infinite loop and crash the program.
 * 2. Hash Set vs Floyd's Tortoise and Hare:
 *    - Hash Set: Storing visited node addresses takes O(N) memory and heap overhead.
 *    - Floyd's Two-Speed Pointers: Uses two pointers traversing at different velocities
 *      (1 step vs 2 steps) in O(1) auxiliary space.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Floyd's Cycle Detection (Tortoise and Hare):
 *   - Initialize two pointers: `slow = head` and `fast = head`.
 *   - In each step:
 *       `slow = slow->next`         (moves at 1x speed)
 *       `fast = fast->next->next`   (moves at 2x speed)
 *   - Case 1: No Loop exists.
 *       `fast` or `fast->next` will reach `nullptr`. We terminate and return `false`.
 *   - Case 2: Loop exists.
 *       Both pointers will eventually enter the loop.
 *       Suppose the loop has perimeter C. In each iteration inside the loop,
 *       the distance between `fast` and `slow` decreases by 1 step modulo C:
 *         (dist + 2 - 1) % C = (dist + 1) % C.
 *       Hence, `fast` is mathematically guaranteed to catch up to and collide
 *       with `slow` in at most C iterations!
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
     * Detects if a cycle exists in the linked list using Floyd's Tortoise and Hare.
     * @param head Pointer to the head of the linked list.
     * @return true if a loop is detected, false otherwise.
     */
    bool hasLoop(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }

        Node* slow = head;
        Node* fast = head;

        // Traverse while fast and fast->next are valid
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // Move 1 step
            fast = fast->next->next;    // Move 2 steps

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // In a closed loop, the relative velocity is (2 - 1) = 1 node/iteration.
            // Fast is guaranteed to lap and collide with slow if and only if a loop exists.
            if (slow == fast) {
                return true; // Cycle detected!
            }
        }

        return false; // Fast reached NULL -> purely linear list
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: List with a loop
    // 1 -> 2 -> 3 -> 4 -> 5 -> connects back to node 3
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    // Create loop: 5 -> 3
    head1->next->next->next->next->next = head1->next->next;

    cout << "Test 1 (Has Loop): " << (solver.hasLoop(head1) ? "YES" : "NO") 
         << " (Expected: YES)\n";

    // Test Case 2: Linear list without loop
    // 10 -> 20 -> 30 -> NULL
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);

    cout << "Test 2 (No Loop):  " << (solver.hasLoop(head2) ? "YES" : "NO") 
         << " (Expected: NO)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Let non-loop length be L, and loop length be C.
 *   - Slow takes L steps to reach the loop start.
 *   - Fast and slow collide within at most C steps inside the loop.
 *   - Total steps: L + C = N.
 *   - Total Time: O(N) strictly.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) - exactly two pointers used (`slow` and `fast`).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always check both `fast != nullptr` and `fast->next != nullptr` before advancing.
 * 2. Floyd's cycle detection is the cornerstone for cycle detection, loop length
 *    finding, and loop entrance location.
 */
