/**
 * ============================================================================
 * Problem: Find First Node of Loop in a Linked List (Linked List Cycle II)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, find the first node (entrance node) of the cycle, 
 * if one exists. If there is no cycle, return NULL.
 * 
 * Example:
 * Input:  head = [3, 2, 0, -4], pos = 1 (node with val 2)
 * Output: Node with val 2
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.val <= 10^9
 * Must run in O(N) time and O(1) auxiliary space without modifying the list.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Cycle Detection vs Precise Origin Identification:
 *    - Problem 3 told us IF a cycle exists.
 *    - Problem 4 severed the loop.
 *    - This problem specifically requires isolating the exact `Node*` pointer
 *      where the tail reconnects into the linear list (the cycle entrance).
 * 2. Mathematical Synchrony (Floyd's Cycle Finding Proof):
 *    - Let L = length from head to loop origin.
 *    - Let C = perimeter of the loop.
 *    - Let d = length from loop origin to the collision point of slow & fast.
 *    - When slow and fast collide:
 *        Distance(slow) = L + d
 *        Distance(fast) = L + d + k * C
 *        2 * Distance(slow) = Distance(fast)  ===>  2(L + d) = L + d + k * C
 *        ===>  L + d = k * C
 *        ===>  L = k * C - d = (k - 1) * C + (C - d)
 *    - Interpretation: The distance from head to loop start (L) is IDENTICAL to
 *      the distance from collision point to loop start modulo C!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Phase 1: Detect Collision Point
 *    - Move `slow` by 1 step, `fast` by 2 steps.
 *    - If `fast` or `fast->next` becomes NULL: return NULL (no loop).
 * 2. Phase 2: Locate Entrance
 *    - Reset `slow = head` while leaving `fast` at the collision point.
 *    - Advance BOTH `slow` and `fast` by 1 step per iteration.
 *    - The node where `slow == fast` is mathematically guaranteed to be the
 *      loop origin. Return this node.
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
     * Finds the first node of the loop in a linked list.
     * @param head Head pointer of the linked list.
     * @return Pointer to the cycle entry node, or nullptr if no cycle exists.
     */
    Node* findLoopStart(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return nullptr;
        }

        Node* slow = head;
        Node* fast = head;
        bool hasCycle = false;

        // Phase 1: Detect cycle and identify collision point
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }

        // No cycle exists
        if (!hasCycle) {
            return nullptr;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Phase 2: Reset 'slow' to head while keeping 'fast' at collision point.
        // Advance both at the exact same 1x speed. The point of convergence is the cycle entry!
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow; // Both pointers now point to the cycle entrance
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: List with loop starting at node with value 2
    // 3 -> 2 -> 0 -> -4 -> loop back to 2
    Node* head1 = new Node(3);
    Node* cycleStart = new Node(2);
    head1->next = cycleStart;
    head1->next->next = new Node(0);
    head1->next->next->next = new Node(-4);
    head1->next->next->next->next = cycleStart; // Reconnect to node 2

    Node* result1 = solver.findLoopStart(head1);
    cout << "Test 1: Loop starts at node with value = " 
         << (result1 ? to_string(result1->data) : "NULL") 
         << " (Expected: 2)\n";

    // Test Case 2: List without cycle
    Node* head2 = new Node(1);
    head2->next = new Node(2);
    head2->next->next = new Node(3);

    Node* result2 = solver.findLoopStart(head2);
    cout << "Test 2: Loop starts at node = " 
         << (result2 ? to_string(result2->data) : "NULL") 
         << " (Expected: NULL)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Phase 1: Slow pointer travels at most N steps; Fast travels at most 2N steps.
 *   - Phase 2: Both pointers travel L <= N steps.
 *   - Total Time Complexity: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) - two pointer variables.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The mathematical equation L = (k-1)C + (C - d) directly explains why
 *    moving one pointer from head and one from collision point at 1x speed
 *    guarantees convergence at the cycle origin.
 */
