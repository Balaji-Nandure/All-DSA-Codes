/**
 * ============================================================================
 * Problem: Split a Circular Linked List into Two Halves
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a Circular Linked List of size N. Split it into two circular linked lists.
 * - If there are an odd number of nodes in the given circular list, the first 
 *   result list should have (N + 1) / 2 nodes, and the second should have N / 2 nodes.
 * - If there are an even number of nodes, each result list should have N / 2 nodes.
 * 
 * Both resulting sublists MUST remain properly circular (their tails pointing 
 * back to their respective heads).
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Splitting Linear vs Circular Structures:
 *    - In linear lists (Problem 13, Merge Sort), splitting was done by setting
 *      `mid->next = nullptr`, which produced two NULL-terminated linear lists.
 *    - In circular lists, setting `next = nullptr` destroys circularity.
 *    - Here, we must create TWO separate closed rings:
 *        Ring 1: Tail of first half (`slow`) must point back to `head1`.
 *        Ring 2: Tail of second half (`fast`) must point back to `head2` (`slow->next`).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Tortoise & Hare Adapted for Circular Boundaries:
 *   - Start `slow = head`, `fast = head`.
 *   - Advance `slow` by 1 step and `fast` by 2 steps while:
 *       `fast->next != head && fast->next->next != head`
 *   - If the list has an even number of nodes, `fast->next->next == head`.
 *     Advance `fast = fast->next` so `fast` lands on the absolute last node.
 *   - Identify heads and close circles:
 *       `*head1_ref = head;`
 *       `*head2_ref = slow->next;`
 *       `fast->next = slow->next;`   (Close circle 2: tail2 -> head2)
 *       `slow->next = head;`         (Close circle 1: tail1 -> head1)
 *   - Runs in a single pass of N/2 iterations with O(1) space!
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
     * Splits a circular linked list into two distinct circular linked lists.
     * @param head Head of the original circular linked list.
     * @param head1_ref Output pointer to the head of the first circular half.
     * @param head2_ref Output pointer to the head of the second circular half.
     */
    void splitList(Node* head, Node** head1_ref, Node** head2_ref) {
        if (head == nullptr) {
            *head1_ref = nullptr;
            *head2_ref = nullptr;
            return;
        }

        Node* slow = head;
        Node* fast = head;

        // Advance slow by 1 and fast by 2 until fast reaches the circular boundary
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // For even number of nodes, advance fast one extra step to reach the last node
        if (fast->next->next == head) {
            fast = fast->next;
        }

        // Set the head pointers of the two halves
        *head1_ref = head;
        *head2_ref = slow->next;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Re-routing pointers to seal both halves into independent closed circular loops:
        // fast->next points to head of second half; slow->next points back to head of first half.
        fast->next = slow->next;
        slow->next = head;
    }
};

void printCircularList(Node* head) {
    if (head == nullptr) {
        cout << "Empty\n";
        return;
    }
    Node* temp = head;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to " << head->data << ")\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: Odd length (5 nodes: 1 -> 2 -> 3 -> 4 -> 5 -> back to 1)
    // Expected Halves: {1, 2, 3} and {4, 5}
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = head1;

    cout << "Original Odd Circular List:  ";
    printCircularList(head1);

    Node* half1_odd = nullptr;
    Node* half2_odd = nullptr;
    solver.splitList(head1, &half1_odd, &half2_odd);

    cout << "First Half (Odd):            ";
    printCircularList(half1_odd);
    cout << "Second Half (Odd):           ";
    printCircularList(half2_odd);

    // Test Case 2: Even length (4 nodes: 10 -> 20 -> 30 -> 40 -> back to 10)
    // Expected Halves: {10, 20} and {30, 40}
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);
    head2->next->next->next = new Node(40);
    head2->next->next->next->next = head2;

    cout << "\nOriginal Even Circular List: ";
    printCircularList(head2);

    Node* half1_even = nullptr;
    Node* half2_even = nullptr;
    solver.splitList(head2, &half1_even, &half2_even);

    cout << "First Half (Even):           ";
    printCircularList(half1_even);
    cout << "Second Half (Even):          ";
    printCircularList(half2_even);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Fast pointer makes at most N/2 steps.
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Always seal the second circle first (`fast->next = slow->next`) before
 *    overwriting `slow->next = head` to avoid losing the address of `head2`.
 */
