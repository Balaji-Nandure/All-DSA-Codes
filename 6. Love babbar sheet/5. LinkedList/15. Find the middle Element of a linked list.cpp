/**
 * ============================================================================
 * Problem: Find the Middle of a Linked List (LeetCode 876)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given the head of a singly linked list, return the middle node of the linked list.
 * If there are two middle nodes (even number of nodes), return the SECOND middle node.
 * 
 * Example 1:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL (Odd length: 5 nodes)
 * Output: Node 3 (Value = 3)
 * 
 * Example 2:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> NULL (Even length: 6 nodes)
 * Output: Node 4 (Value = 4) [Between 3 and 4, second middle is node 4]
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in a single pass O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single Pass vs Dual Pass:
 *    - Naive approach: Pass 1 counts total length L. Pass 2 advances L/2 steps.
 *      Requires traversing the list twice (2 passes).
 *    - Two-pointer Tortoise & Hare: Finds the middle in a SINGLE PASS.
 * 2. Subtle Initialization for Even Lengths:
 *    - To return the SECOND middle node (LeetCode convention):
 *      Initialize `slow = head, fast = head`.
 *    - To return the FIRST middle node (Merge Sort splitting convention):
 *      Initialize `slow = head, fast = head->next`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Fast and Slow Pointers (Tortoise and Hare):
 *   - Initialize:
 *       `slow = head`
 *       `fast = head`
 *   - In each iteration:
 *       `slow = slow->next;`        (1 step)
 *       `fast = fast->next->next;`  (2 steps)
 *   - While condition: `while (fast != nullptr && fast->next != nullptr)`
 *   - When fast reaches the end, slow has traversed exactly half the distance,
 *     placing it precisely on the middle node.
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
     * Finds the middle node (second middle for even length).
     * Single pass, O(N) Time, O(1) Auxiliary Space.
     */
    Node* findMiddleSecond(Node* head) {
        if (head == nullptr) return nullptr;

        Node* slow = head;
        Node* fast = head;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // While fast travels at double speed (2x), slow travels at 1x speed.
        // The moment fast reaches the boundary (NULL or tail), slow is at mid.
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow; // Second middle for even length, exact middle for odd length
    }

    /**
     * Finds the first middle node for even length (Used in Merge Sort splitting).
     */
    Node* findMiddleFirst(Node* head) {
        if (head == nullptr) return nullptr;

        Node* slow = head;
        Node* fast = head->next; // Staggered initialization

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow; // First middle for even length
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Odd length (5 nodes: 1 -> 2 -> 3 -> 4 -> 5)
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);

    Node* mid1 = solver.findMiddleSecond(head1);
    cout << "Test 1 (Odd: 5 nodes): Middle = " << mid1->data << " (Expected: 3)\n";

    // Test Case 2: Even length (6 nodes: 1 -> 2 -> 3 -> 4 -> 5 -> 6)
    Node* head2 = new Node(1);
    head2->next = new Node(2);
    head2->next->next = new Node(3);
    head2->next->next->next = new Node(4);
    head2->next->next->next->next = new Node(5);
    head2->next->next->next->next->next = new Node(6);

    Node* mid2Second = solver.findMiddleSecond(head2);
    Node* mid2First = solver.findMiddleFirst(head2);
    cout << "Test 2 (Even: 6 nodes): Second Middle = " << mid2Second->data << " (Expected: 4)\n";
    cout << "Test 2 (Even: 6 nodes): First Middle  = " << mid2First->data << " (Expected: 3)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Fast pointer makes at most N/2 iterations.
 *   - Total Time: O(N) in a single pass.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. `fast = head` yields the second middle node on even lengths.
 * 2. `fast = head->next` yields the first middle node on even lengths.
 */
