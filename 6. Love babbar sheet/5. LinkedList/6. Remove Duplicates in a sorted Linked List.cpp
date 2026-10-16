/**
 * ============================================================================
 * Problem: Remove Duplicate Elements from Sorted Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list consisting of N nodes, sorted in ascending order.
 * The task is to remove all duplicate elements from the list such that each 
 * distinct value appears exactly once.
 * 
 * Example 1:
 * Input:  2 -> 2 -> 4 -> 5 -> NULL
 * Output: 2 -> 4 -> 5 -> NULL
 * 
 * Example 2:
 * Input:  11 -> 11 -> 11 -> 21 -> 43 -> 43 -> 60 -> NULL
 * Output: 11 -> 21 -> 43 -> 60 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Clustered Identical Neighbors vs Scattered Duplicates:
 *    - In an unsorted array or list, duplicates can appear anywhere, requiring
 *      a hash set O(N) space or nested comparisons O(N^2).
 *    - Because the list is SORTED, all duplicate instances of any value are 
 *      strictly contiguous adjacent neighbors.
 * 2. Proper Memory Management (Destruction):
 *    - In C++, simply bypassing a node (`curr->next = curr->next->next`) creates
 *      an unreferenced memory leak.
 *    - We must explicitly deallocate discarded nodes using `delete`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Single Pointer Traversal O(N) Time, O(1) Space:
 *   - Maintain pointer `curr = head`.
 *   - While `curr != nullptr` and `curr->next != nullptr`:
 *       - If `curr->data == curr->next->data`:
 *           1. Stash pointer `Node* dup = curr->next;`
 *           2. Bypass: `curr->next = curr->next->next;`
 *           3. Free memory: `delete dup;`
 *           (Crucial: Do NOT advance `curr`, because the newly linked node
 *            might also be a duplicate of `curr->data`!).
 *       - Else:
 *           `curr = curr->next;`
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
     * Removes duplicates from a sorted linked list in-place with O(1) extra space.
     * @param head Pointer to the head of the sorted linked list.
     * @return Head of the deduplicated list.
     */
    Node* removeDuplicates(Node* head) {
        if (head == nullptr) return nullptr;

        Node* curr = head;

        while (curr != nullptr && curr->next != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // When an adjacent duplicate is detected, bypass and delete the duplicate node,
            // but keep 'curr' stationary to test the new neighbor against cascading duplicates.
            if (curr->data == curr->next->data) {
                Node* duplicateNode = curr->next;
                curr->next = curr->next->next; // Bypass
                delete duplicateNode;          // Deallocate to prevent memory leak
            } else {
                curr = curr->next;             // Advance only when next node is distinct
            }
        }

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

    // Test Case 1: 11 -> 11 -> 11 -> 21 -> 43 -> 43 -> 60 -> NULL
    Node* head1 = new Node(11);
    head1->next = new Node(11);
    head1->next->next = new Node(11);
    head1->next->next->next = new Node(21);
    head1->next->next->next->next = new Node(43);
    head1->next->next->next->next->next = new Node(43);
    head1->next->next->next->next->next->next = new Node(60);

    cout << "Original List 1: ";
    printList(head1);

    head1 = solver.removeDuplicates(head1);
    cout << "Deduplicated 1:  ";
    printList(head1);

    // Test Case 2: All identical elements: 5 -> 5 -> 5 -> 5 -> NULL
    Node* head2 = new Node(5);
    head2->next = new Node(5);
    head2->next->next = new Node(5);
    head2->next->next->next = new Node(5);

    cout << "\nOriginal List 2: ";
    printList(head2);

    head2 = solver.removeDuplicates(head2);
    cout << "Deduplicated 2:  ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each node is visited at most once.
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly. Zero heap buffers or recursion frames.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Never advance `curr = curr->next` inside the `if (curr->data == curr->next->data)` block,
 *    or you will fail on runs of 3 or more identical values (e.g. 11 -> 11 -> 11).
 * 2. In C++, always `delete` bypassed nodes to avoid memory leaks.
 */
