/**
 * ============================================================================
 * Problem: Move the Last Element to the Front of a Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, move its last node to the front of the list.
 * 
 * Example 1:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL
 * Output: 5 -> 1 -> 2 -> 3 -> 4 -> NULL
 * 
 * Example 2:
 * Input:  10 -> 20 -> NULL
 * Output: 20 -> 10 -> NULL
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Single Cyclic Shift (Right Rotation by 1):
 *    - In arrays (Category 1, Problem 7), rotating by one required shifting all
 *      N elements right: `arr[i] = arr[i - 1]` in O(N) memory writes.
 *    - In a linked list, elements NEVER move physically in memory!
 *    - Only TWO pointer updates are performed:
 *        1. `secondLast->next = nullptr` (disconnect tail).
 *        2. `last->next = head` (connect old tail to old head).
 * 2. Importance of the Second-to-Last Node:
 *    - In a singly linked list, there are no backward pointers (`prev`).
 *    - To detach the last node, you MUST hold a pointer to the second-to-last node;
 *      otherwise, you cannot set its `next` to NULL!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Corner Cases:
 *    - If list is empty (`head == nullptr`) or has only 1 node (`head->next == nullptr`),
 *      no shift is possible or needed. Return `head`.
 * 2. Find Second-to-Last Node:
 *    - Initialize `secondLast = head`.
 *    - Advance while `secondLast->next->next != nullptr`.
 * 3. Re-link Pointers:
 *    - `last = secondLast->next`
 *    - `secondLast->next = nullptr`
 *    - `last->next = head`
 *    - `head = last`
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
     * Moves the last element of the linked list to the front.
     * @param head Pointer to the head of the linked list.
     * @return New head of the modified linked list.
     */
    Node* moveLastToFront(Node* head) {
        // Edge cases: 0 or 1 node
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* secondLast = head;

        // Traverse until secondLast points to the penultimate node
        while (secondLast->next->next != nullptr) {
            secondLast = secondLast->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Isolate the tail, sever the penultimate node's next link,
        // and reattach the old tail at the very beginning of the list.
        Node* last = secondLast->next;
        secondLast->next = nullptr;
        last->next = head;
        head = last;

        return head;
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

    // Test Case 1: 1 -> 2 -> 3 -> 4 -> 5 -> NULL
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(5);

    cout << "Original List 1: ";
    printList(head1);

    head1 = solver.moveLastToFront(head1);
    cout << "Moved to Front:  ";
    printList(head1);

    // Test Case 2: 10 -> 20 -> NULL
    Node* head2 = new Node(10);
    head2->next = new Node(20);

    head2 = solver.moveLastToFront(head2);
    cout << "\nMoved to Front 2: ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Traversal to find the second-to-last node takes (N - 2) pointer hops: O(N).
 *   - Pointer re-linking takes O(1) time.
 *   - Total Time Complexity: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly. Zero heap allocation or recursion.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Singly linked list pointer disconnection always requires access to the
 *    immediate predecessor of the node being relocated.
 */
