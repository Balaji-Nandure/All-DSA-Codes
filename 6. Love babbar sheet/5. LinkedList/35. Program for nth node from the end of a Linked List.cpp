/**
 * ============================================================================
 * Problem: N-th Node from the End of a Linked List (LeetCode 19 / GFG)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list consisting of L nodes and an integer N.
 * Find the N-th node from the end of the linked list (1-indexed).
 * If N is greater than the total number of nodes in the list, return -1.
 * 
 * Example 1:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL, N = 2
 * Output: 8
 * 
 * Example 2:
 * Input:  10 -> 5 -> 100 -> 5 -> NULL, N = 5
 * Output: -1 (N > total nodes)
 * 
 * Constraints:
 * 1 <= L <= 10^5
 * 1 <= N <= 10^5
 * Must run in a SINGLE PASS with O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single Pass vs Dual Pass (L - N + 1):
 *    - In arrays, accessing the N-th element from the end is O(1) random access:
 *      `arr[L - N]`.
 *    - In linked lists, a naive solution takes 2 passes: Pass 1 finds length L,
 *      Pass 2 advances (L - N) steps.
 *    - The Sliding Window Two-Pointer technique finds the target in a SINGLE PASS.
 * 2. Constant Offset Window:
 *    - Maintaining a lead of exactly N nodes between `fast` and `slow` guarantees
 *      that when `fast` hits the end of the list, `slow` lands directly on the target.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Fixed-Gap Two Pointer Technique O(L) Single Pass, O(1) Space:
 *   - Step 1: Initialize `fast = head` and `slow = head`.
 *   - Step 2: Advance `fast` forward by N steps:
 *       - If `fast` becomes `nullptr` before completing N steps, the list has
 *         fewer than N nodes -> return -1.
 *   - Step 3: Advance both `fast` and `slow` simultaneously 1 step at a time
 *     until `fast == nullptr`:
 *       `fast = fast->next;`
 *       `slow = slow->next;`
 *   - Step 4: When `fast` reaches `nullptr`, `slow` points to the N-th node from the end.
 *     Return `slow->data`.
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
     * Finds the data value of the N-th node from the end of the linked list.
     * @param head Head of the linked list.
     * @param n Position from the end (1-indexed).
     * @return Value of the N-th node from the end, or -1 if n > length.
     */
    int getNthFromLast(Node* head, int n) {
        if (head == nullptr || n <= 0) return -1;

        Node* fast = head;
        Node* slow = head;

        // Step 1: Advance 'fast' pointer by n nodes
        for (int i = 0; i < n; ++i) {
            if (fast == nullptr) {
                return -1; // List length is strictly less than n
            }
            fast = fast->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // By advancing 'fast' and 'slow' simultaneously with a fixed gap of 'n' nodes,
        // when 'fast' reaches NULL, 'slow' is mathematically positioned on the Nth node from the end.
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }

        return slow->data;
    }
};

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

    // List: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> NULL
    Node* head = new Node(1);
    Node* curr = head;
    for (int i = 2; i <= 9; ++i) {
        curr->next = new Node(i);
        curr = curr->next;
    }

    cout << "Linked List: ";
    printList(head);

    // Test Case 1: 2nd node from end
    cout << "2nd from end: " << solver.getNthFromLast(head, 2) << " (Expected: 8)\n";

    // Test Case 2: 9th node from end (first node)
    cout << "9th from end: " << solver.getNthFromLast(head, 9) << " (Expected: 1)\n";

    // Test Case 3: Out of bounds (15th from end)
    cout << "15th from end: " << solver.getNthFromLast(head, 15) << " (Expected: -1)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Fast pointer makes exactly L steps.
 *   - Total Time: O(L) in a strict single pass.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly (two pointer variables).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Maintaining a fixed-distance window between two pointers eliminates the need
 *    for a preliminary length-counting pass.
 */
