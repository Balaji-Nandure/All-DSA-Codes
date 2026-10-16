/**
 * ============================================================================
 * Problem: Rotate a Doubly Linked List by P Nodes (Counter-Clockwise / Left Rotate)
 * Category: LinkedList / Doubly Linked List
 * 
 * Problem Statement:
 * Given a Doubly Linked List, rotate it counter-clockwise by P nodes.
 * 
 * Example:
 * Input:  'a' <-> 'b' <-> 'c' <-> 'd' <-> 'e' -> NULL, P = 2
 * Output: 'c' <-> 'd' <-> 'e' <-> 'a' <-> 'b' -> NULL
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * 1 <= P <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Array Rotation vs DLL Pointer Splicing:
 *    - In arrays (Category 1, Problem 7), rotating by P required reversing blocks
 *      or copying elements in O(N) memory writes.
 *    - In Doubly Linked Lists, rotation requires ZERO element movements.
 *    - We temporarily seal the list into a ring (circular DLL) and cut the ring
 *      at the P-th node!
 * 2. Bidirectional Pointer Maintenance:
 *    - Both `next` and `prev` pointers at the junction must be correctly re-linked
 *      and NULL-terminated.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Circular Ring & Cut Method O(N) Time, O(1) Space:
 *   - Step 1: Traverse the list to calculate its length `len` and locate the `tail`.
 *   - Step 2: Normalize `P = P % len`. If `P == 0`, no rotation needed.
 *   - Step 3: Connect tail to head to form a circular DLL:
 *       `tail->next = head;`
 *       `head->prev = tail;`
 *   - Step 4: Advance from `head` by (P - 1) steps to find the node that will become the new tail.
 *       Let this node be `newTail`.
 *   - Step 5: `newHead = newTail->next`.
 *   - Step 6: Break circular links:
 *       `newHead->prev = nullptr;`
 *       `newTail->next = nullptr;`
 *   - Return `newHead`.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    char data;
    Node* next;
    Node* prev;
    Node(char val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution {
public:
    /**
     * Left-rotates a Doubly Linked List by P nodes in O(N) time and O(1) space.
     * @param head Pointer to the head of the DLL.
     * @param p Number of positions to rotate counter-clockwise.
     * @return New head of the rotated DLL.
     */
    Node* rotateDLL(Node* head, int p) {
        if (head == nullptr || head->next == nullptr || p == 0) {
            return head;
        }

        // Step 1: Calculate length and find tail
        Node* tail = head;
        int len = 1;
        while (tail->next != nullptr) {
            tail = tail->next;
            len++;
        }

        // Normalize p
        p = p % len;
        if (p == 0) return head;

        // Step 2: Make the DLL circular
        tail->next = head;
        head->prev = tail;

        // Step 3: Move to the p-th node (which will become the new tail)
        Node* newTail = head;
        for (int i = 1; i < p; ++i) {
            newTail = newTail->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Establish the new head immediately after newTail,
        // and sever both the forward 'next' and backward 'prev' circular links.
        Node* newHead = newTail->next;
        newHead->prev = nullptr;
        newTail->next = nullptr;

        return newHead;
    }
};

void printDLL(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next) cout << " <-> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create DLL: 'a' <-> 'b' <-> 'c' <-> 'd' <-> 'e' -> NULL
    vector<char> chars = {'a', 'b', 'c', 'd', 'e'};
    Node* head = new Node(chars[0]);
    Node* curr = head;

    for (size_t i = 1; i < chars.size(); ++i) {
        Node* newNode = new Node(chars[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }

    int P = 2;
    cout << "Original DLL:    ";
    printDLL(head);

    head = solver.rotateDLL(head, P);
    cout << "Rotated by 2:    ";
    printDLL(head); // Expected: 'c' <-> 'd' <-> 'e' <-> 'a' <-> 'b' -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Finding length and tail: O(N).
 *   - Advancing to new tail: O(P) <= O(N).
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Making the list temporarily circular transforms any rotation into a simple
 *    ring cut operation.
 * 2. Always handle `p >= len` using modulo arithmetic (`p % len`).
 */
