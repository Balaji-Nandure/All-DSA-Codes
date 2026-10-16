/**
 * ============================================================================
 * Problem: Sort a Linked List of 0s, 1s and 2s
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list consisting of N nodes where each node's value is 
 * either 0, 1, or 2. Sort the linked list in-place.
 * 
 * Note: Interviewers frequently forbid overwriting node data values (as each node
 * may contain complex payload objects); the sorting must be performed purely 
 * by re-linking node pointers!
 * 
 * Example 1:
 * Input:  1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2 -> NULL
 * Output: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2 -> NULL
 * 
 * Example 2:
 * Input:  2 -> 2 -> 0 -> 1 -> NULL
 * Output: 0 -> 1 -> 2 -> 2 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * Node.data in {0, 1, 2}
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Dutch National Flag on Arrays vs Linked Lists:
 *    - In arrays (Category 1, Problem 4), DNF uses 3 index pointers and swaps
 *      elements in-place.
 *    - In linked lists, value swapping is frowned upon because nodes may hold large
 *      payloads, or node identity (reference) must remain intact.
 * 2. 3-Way Partitioning via Dummy Buckets:
 *    - We partition nodes into three independent linked chains: `zeros`, `ones`, and `twos`.
 *    - Splicing the three chains must gracefully handle cases where one or two of
 *      the buckets are completely empty (e.g., no 1s in the list).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Three Dummy-Head Buckets (Pointer Re-linking O(N) Time, O(1) Space):
 *   - Create three dummy sentinel nodes: `zeroDummy`, `oneDummy`, `twoDummy`.
 *   - Maintain tails for each: `zeroTail`, `oneTail`, `twoTail`.
 *   - Step 1: Iterate through the original list:
 *       - If `curr->data == 0`: link to `zeroTail`, advance `zeroTail`.
 *       - If `curr->data == 1`: link to `oneTail`, advance `oneTail`.
 *       - If `curr->data == 2`: link to `twoTail`, advance `twoTail`.
 *   - Step 2: Splice the three chains:
 *       - `zeroTail->next = (oneDummy->next != nullptr) ? oneDummy->next : twoDummy->next;`
 *       - `oneTail->next = twoDummy->next;`
 *       - `twoTail->next = nullptr;`
 *   - Step 3: Establish new head:
 *       `head = zeroDummy->next;`
 *   - Return `head`.
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
     * Sorts the linked list of 0s, 1s, and 2s purely by re-linking pointers.
     * @param head Pointer to the head of the linked list.
     * @return New head of the sorted linked list.
     */
    Node* segregate(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Dummy heads for each of the three value buckets
        Node* zeroDummy = new Node(0);
        Node* oneDummy = new Node(0);
        Node* twoDummy = new Node(0);

        Node* zeroTail = zeroDummy;
        Node* oneTail = oneDummy;
        Node* twoTail = twoDummy;

        Node* curr = head;

        // Step 1: Distribute nodes into their corresponding buckets
        while (curr != nullptr) {
            if (curr->data == 0) {
                zeroTail->next = curr;
                zeroTail = zeroTail->next;
            } else if (curr->data == 1) {
                oneTail->next = curr;
                oneTail = oneTail->next;
            } else {
                twoTail->next = curr;
                twoTail = twoTail->next;
            }
            curr = curr->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Seamlessly splice the three chains together handling missing buckets:
        // If the '1' bucket is empty, zeroTail jumps directly to twoDummy->next!
        zeroTail->next = (oneDummy->next != nullptr) ? oneDummy->next : twoDummy->next;
        oneTail->next = twoDummy->next;
        twoTail->next = nullptr; // Terminate list

        Node* sortedHead = zeroDummy->next;

        // Clean up dummy nodes
        delete zeroDummy;
        delete oneDummy;
        delete twoDummy;

        return sortedHead;
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

    // Test Case 1: 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2 -> NULL
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(2);
    head1->next->next->next = new Node(1);
    head1->next->next->next->next = new Node(2);
    head1->next->next->next->next->next = new Node(0);
    head1->next->next->next->next->next->next = new Node(2);
    head1->next->next->next->next->next->next->next = new Node(2);

    cout << "Original List 1: ";
    printList(head1);

    head1 = solver.segregate(head1);
    cout << "Sorted List 1:   ";
    printList(head1); // Expected: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2 -> NULL

    // Test Case 2: No 1s (only 0s and 2s: 2 -> 0 -> 2 -> 0 -> NULL)
    Node* head2 = new Node(2);
    head2->next = new Node(0);
    head2->next->next = new Node(2);
    head2->next->next->next = new Node(0);

    cout << "\nOriginal List 2 (No 1s): ";
    printList(head2);

    head2 = solver.segregate(head2);
    cout << "Sorted List 2:           ";
    printList(head2); // Expected: 0 -> 0 -> 2 -> 2 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Single pass visiting all N nodes: O(N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly (only 3 stack dummy nodes and pointers).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Pointer splicing avoids touching node data, preserving node stability and
 *    supporting complex object payloads.
 * 2. Always handle empty buckets when linking `zeroTail->next`.
 */
