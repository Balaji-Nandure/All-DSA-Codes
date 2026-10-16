/**
 * ============================================================================
 * Problem: Segregate Even and Odd Nodes in a Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a singly linked list, modify the list such that all even-valued nodes
 * appear before all odd-valued nodes. The relative order of even elements among
 * themselves and odd elements among themselves MUST be preserved.
 * 
 * Example:
 * Input:  17 -> 15 -> 8 -> 9 -> 2 -> 4 -> 6 -> NULL
 * Output: 8 -> 2 -> 4 -> 6 -> 17 -> 15 -> 9 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Stable Partitioning on Graphs:
 *    - In arrays (Category 1, Problem 5), segregation using two-pointer swapping
 *      in-place does NOT maintain relative stability.
 *    - In linked lists, we can achieve STRICT STABILITY in O(1) space by maintaining
 *      two separate chain tails (`evenTail` and `oddTail`) and appending nodes in-order.
 * 2. Missing Sublist Boundaries:
 *    - If all nodes are odd or all nodes are even, connecting `evenTail->next = oddDummy->next`
 *      must gracefully handle empty chains without crashing.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Dual Dummy Sentinel Buckets O(N) Time, O(1) Space:
 *   - Create two dummy heads: `evenDummy` and `oddDummy`.
 *   - Maintain tails: `evenTail = evenDummy`, `oddTail = oddDummy`.
 *   - Step 1: Traverse the original list:
 *       - If `curr->data % 2 == 0`:
 *           `evenTail->next = curr;`
 *           `evenTail = evenTail->next;`
 *       - Else:
 *           `oddTail->next = curr;`
 *           `oddTail = oddTail->next;`
 *       - `curr = curr->next;`
 *   - Step 2: Connect even chain to odd chain:
 *       `evenTail->next = oddDummy->next;`
 *       `oddTail->next = nullptr;` // Prevent trailing cycles
 *   - Step 3: Result is `evenDummy->next`.
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
     * Segregates even and odd nodes in the linked list preserving relative order.
     * @param head Head of the linked list.
     * @return Head of the modified list.
     */
    Node* segregateEvenOdd(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        Node* evenDummy = new Node(0);
        Node* oddDummy = new Node(0);

        Node* evenTail = evenDummy;
        Node* oddTail = oddDummy;

        Node* curr = head;

        // Step 1: Distribute nodes into even and odd chains
        while (curr != nullptr) {
            if (curr->data % 2 == 0) {
                evenTail->next = curr;
                evenTail = evenTail->next;
            } else {
                oddTail->next = curr;
                oddTail = oddTail->next;
            }
            curr = curr->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Splice even chain directly into the start of the odd chain,
        // and ensure the tail of the odd chain is explicitly set to nullptr.
        evenTail->next = oddDummy->next;
        oddTail->next = nullptr;

        Node* newHead = evenDummy->next;

        delete evenDummy;
        delete oddDummy;

        return newHead;
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

    // Test Case: 17 -> 15 -> 8 -> 9 -> 2 -> 4 -> 6 -> NULL
    // Expected: 8 -> 2 -> 4 -> 6 -> 17 -> 15 -> 9 -> NULL
    Node* head = new Node(17);
    head->next = new Node(15);
    head->next->next = new Node(8);
    head->next->next->next = new Node(9);
    head->next->next->next->next = new Node(2);
    head->next->next->next->next->next = new Node(4);
    head->next->next->next->next->next->next = new Node(6);

    cout << "Original List: ";
    printList(head);

    head = solver.segregateEvenOdd(head);
    cout << "Segregated:    ";
    printList(head);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Single pass visiting all N nodes: O(N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Stable partitioning is trivial in linked lists using two dummy sentinels.
 * 2. Always set `oddTail->next = nullptr` to terminate the list properly.
 */
