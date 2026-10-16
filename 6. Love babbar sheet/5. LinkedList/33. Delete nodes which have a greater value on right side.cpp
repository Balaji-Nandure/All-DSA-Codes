/**
 * ============================================================================
 * Problem: Delete Nodes Having Greater Value on Right (LeetCode 2487)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, delete every node that has a node with a greater 
 * value anywhere to the right of it.
 * 
 * Example 1:
 * Input:  12 -> 15 -> 10 -> 11 -> 5 -> 6 -> 2 -> 3 -> NULL
 * Output: 15 -> 11 -> 6 -> 3 -> NULL
 * Explanation:
 *   12 < 15 (delete 12)
 *   10 < 11 (delete 10)
 *   5 < 6 (delete 5)
 *   2 < 3 (delete 2)
 * 
 * Example 2:
 * Input:  10 -> 20 -> 30 -> 40 -> 50 -> NULL
 * Output: 50 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Global Suffix Maximum Invariant:
 *    - In Problem 6 & 7, duplicate deletion depended only on previous nodes or
 *      immediate neighbors.
 *    - Here, a node's survival depends on the MAXIMUM of all nodes strictly to
 *      its RIGHT (the suffix maximum).
 * 2. Unidirectional Inversion:
 *    - Scanning from left to right would require looking forward repeatedly,
 *      costing O(N^2) time.
 *    - By REVERSING the list, looking "to the right" becomes looking "to the past"!
 *    - A simple running `maxSoFar` eliminates nodes in a single O(N) linear pass.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Reverse -> Filter -> Reverse Pattern O(N) Time, O(1) Space:
 *   - Step 1: Reverse the linked list in-place so the tail becomes the head.
 *   - Step 2: Initialize `maxSoFar = head->data` and `curr = head`.
 *   - Step 3: Traverse the reversed list:
 *       - If `curr->next->data < maxSoFar`:
 *           `curr->next` has a greater value to its right (in original order)!
 *           Bypass and deallocate `curr->next`.
 *       - Else:
 *           `curr = curr->next;`
 *           `maxSoFar = curr->data;`
 *   - Step 4: Reverse the filtered list again to restore original left-to-right order.
 *   - Total Time: O(N), Space: strictly O(1) without stack or recursion.
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
private:
    /**
     * Helper to reverse a linked list in-place.
     */
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
        }
        return prev;
    }

public:
    /**
     * Deletes all nodes that have a greater value anywhere to their right.
     * @param head Pointer to the head of the linked list.
     * @return New head of the filtered list.
     */
    Node* compute(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Reverse the list so right-side max becomes a prefix max
        head = reverseList(head);

        // Step 2: Traverse and prune smaller elements
        Node* curr = head;
        int maxSoFar = head->data;

        while (curr != nullptr && curr->next != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // In the reversed list, if the next node's value is less than maxSoFar,
            // it had a strictly greater element to its right in the original sequence!
            if (curr->next->data < maxSoFar) {
                Node* toDelete = curr->next;
                curr->next = curr->next->next;
                delete toDelete;
            } else {
                curr = curr->next;
                maxSoFar = curr->data;
            }
        }

        // Step 3: Reverse back to restore original relative order
        return reverseList(head);
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

    // Test Case 1: 12 -> 15 -> 10 -> 11 -> 5 -> 6 -> 2 -> 3 -> NULL
    // Expected: 15 -> 11 -> 6 -> 3 -> NULL
    Node* head1 = new Node(12);
    head1->next = new Node(15);
    head1->next->next = new Node(10);
    head1->next->next->next = new Node(11);
    head1->next->next->next->next = new Node(5);
    head1->next->next->next->next->next = new Node(6);
    head1->next->next->next->next->next->next = new Node(2);
    head1->next->next->next->next->next->next->next = new Node(3);

    cout << "Original List 1: ";
    printList(head1);

    head1 = solver.compute(head1);
    cout << "Filtered List 1: ";
    printList(head1);

    // Test Case 2: Strictly ascending: 10 -> 20 -> 30 -> 40 -> 50
    // Expected: 50 -> NULL
    Node* head2 = new Node(10);
    head2->next = new Node(20);
    head2->next->next = new Node(30);
    head2->next->next->next = new Node(40);
    head2->next->next->next->next = new Node(50);

    cout << "\nOriginal List 2: ";
    printList(head2);

    head2 = solver.compute(head2);
    cout << "Filtered List 2: ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Reversing list takes O(N).
 *   - Linear filtering takes O(N).
 *   - Reversing back takes O(N).
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Reversing transforms difficult "look-ahead suffix maximum" queries into
 *    trivial "running prefix maximum" updates.
 */
