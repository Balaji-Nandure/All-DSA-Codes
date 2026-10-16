/**
 * ============================================================================
 * Problem: Intersection of Two Sorted Linked Lists
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given two linked lists sorted in increasing order, create a new linked list
 * representing the intersection of the two lists. The intersection list should
 * also be sorted in increasing order and contain all elements that appear in 
 * BOTH lists.
 * 
 * Example:
 * Input:
 *   List 1: 1 -> 2 -> 3 -> 4 -> 6 -> NULL
 *   List 2: 2 -> 4 -> 6 -> 8 -> NULL
 * Output: 2 -> 4 -> 6 -> NULL
 * 
 * Constraints:
 * 1 <= Size of List 1, List 2 <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N + M) time and O(1) auxiliary space (excluding result list).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Intersection by Value vs Intersection by Node Address (Y-Shaped):
 *    - Notice: This problem finds the intersection of VALUES between two sorted lists.
 *    - Problem 12 will find the structural intersection NODE (memory reference) of
 *      a Y-shaped junction.
 * 2. Two-Pointer Linear Traversal on Sorted Graphs:
 *    - Because both lists are pre-sorted, we can find common elements in O(N + M)
 *      time without requiring an O(N) hash set.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Two-Pointer Parallel Pursuit:
 *   - Initialize a `dummyHead` to easily build the new intersection list.
 *   - Maintain `ptr1` at head1, `ptr2` at head2, and `tail` at dummyHead.
 *   - While `ptr1 != nullptr` && `ptr2 != nullptr`:
 *       - If `ptr1->data < ptr2->data`:
 *           `ptr1 = ptr1->next;` (the smaller element can never match any later element in ptr2)
 *       - Else if `ptr2->data < ptr1->data`:
 *           `ptr2 = ptr2->next;`
 *       - Else (`ptr1->data == ptr2->data`):
 *           Append new node with value `ptr1->data` to result list:
 *             `tail->next = new Node(ptr1->data);`
 *             `tail = tail->next;`
 *           Advance both: `ptr1 = ptr1->next; ptr2 = ptr2->next;`
 *   - Return `dummyHead->next`.
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
     * Constructs the intersection list of two sorted linked lists.
     * @param head1 Head of the first sorted linked list.
     * @param head2 Head of the second sorted linked list.
     * @return Head of the new sorted intersection linked list.
     */
    Node* findIntersection(Node* head1, Node* head2) {
        Node* dummyHead = new Node(0);
        Node* tail = dummyHead;

        Node* ptr1 = head1;
        Node* ptr2 = head2;

        while (ptr1 != nullptr && ptr2 != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Monotonic property of sorted lists: If values match, append to result
            // and advance both pointers. Otherwise advance whichever pointer is smaller.
            if (ptr1->data == ptr2->data) {
                tail->next = new Node(ptr1->data);
                tail = tail->next;
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            } else if (ptr1->data < ptr2->data) {
                ptr1 = ptr1->next;
            } else {
                ptr2 = ptr2->next;
            }
        }

        Node* result = dummyHead->next;
        delete dummyHead;
        return result;
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

    // List 1: 1 -> 2 -> 3 -> 4 -> 6 -> NULL
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(4);
    head1->next->next->next->next = new Node(6);

    // List 2: 2 -> 4 -> 6 -> 8 -> NULL
    Node* head2 = new Node(2);
    head2->next = new Node(4);
    head2->next->next = new Node(6);
    head2->next->next->next = new Node(8);

    cout << "List 1:       ";
    printList(head1);
    cout << "List 2:       ";
    printList(head2);

    Node* intersection = solver.findIntersection(head1, head2);
    cout << "Intersection: ";
    printList(intersection); // Expected: 2 -> 4 -> 6 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each step advances at least one pointer (ptr1 or ptr2).
 *   - Total operations: at most N + M steps.
 *   - Total Time: O(N + M) optimal linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond the nodes of the output list.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Leverage sortedness: comparing elements in sorted lists allows two pointers
 *    to find matches in linear time without hashing.
 */
