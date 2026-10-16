/**
 * ============================================================================
 * Problem: Reverse a Doubly Linked List in Groups of Given Size K
 * Category: LinkedList / Doubly Linked List
 * 
 * Problem Statement:
 * Given a Doubly Linked List, reverse every contiguous group of K nodes in the list.
 * If the number of nodes in the last group is less than K, reverse those remaining
 * nodes as well. Ensure all bidirectional `next` and `prev` pointers remain
 * structurally sound across block boundaries.
 * 
 * Example:
 * Input:  10 <-> 8 <-> 4 <-> 2 <-> 5 <-> 7 -> NULL, K = 2
 * Output: 8 <-> 10 <-> 2 <-> 4 <-> 7 <-> 5 -> NULL
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * 1 <= K <= Number of nodes
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Bidirectional Link Maintenance across Group Boundaries:
 *    - In Singly Linked Lists (Problem 2), we only had to stitch the forward link:
 *      `head->next = reverseKGroup(forward, k)`.
 *    - In a Doubly Linked List, the connection between group `G_i` and `G_{i+1}`
 *      requires TWO mutual pointer updates:
 *        1. `tail_of_G_i->next = head_of_G_{i+1}`
 *        2. `head_of_G_{i+1}->prev = tail_of_G_i`
 * 2. In-Place Swapping of next and prev within each Chunk:
 *    - Each node inside the K-block has its `next` and `prev` swapped.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Recursive Chunk Reversal:
 *   - Base Case: If `head == nullptr` or `k <= 1`, return `head`.
 *   - Step 1: Reverse up to K nodes using pointer swapping:
 *       Count up to K:
 *         `forward = curr->next;`
 *         `curr->next = curr->prev;`
 *         `curr->prev = forward;`
 *         `newHead = curr;`
 *         `curr = forward;`
 *   - Step 2: Recurse for the remaining list:
 *       `head` was the original first node, now it is the TAIL of this group.
 *       `head->next = reverseKGroupDLL(forward, k);`
 *       `if (head->next != nullptr) head->next->prev = head;`
 *   - Step 3: Set `newHead->prev = nullptr;` and return `newHead`.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution {
public:
    /**
     * Reverses a Doubly Linked List in groups of size K.
     * @param head Pointer to the head of the DLL.
     * @param k Size of each chunk to reverse.
     * @return New head of the modified DLL.
     */
    Node* reverseKGroupDLL(Node* head, int k) {
        if (head == nullptr || head->next == nullptr || k <= 1) {
            return head;
        }

        Node* curr = head;
        Node* forward = nullptr;
        Node* newHead = nullptr;
        int count = 0;

        // Step 1: Reverse first K nodes of current block
        while (curr != nullptr && count < k) {
            forward = curr->next;

            // Invert bidirectional pointers
            curr->next = curr->prev;
            curr->prev = forward;

            newHead = curr;
            curr = forward;
            count++;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 'head' is now the tail of this reversed group.
        // We link its 'next' pointer to the head of the next reversed chunk,
        // AND link that next chunk's 'prev' pointer back to 'head'!
        if (forward != nullptr) {
            head->next = reverseKGroupDLL(forward, k);
            if (head->next != nullptr) {
                head->next->prev = head;
            }
        }

        newHead->prev = nullptr;
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

    // Create DLL: 10 <-> 8 <-> 4 <-> 2 <-> 5 <-> 7 -> NULL, K = 2
    vector<int> values = {10, 8, 4, 2, 5, 7};
    Node* head = new Node(values[0]);
    Node* curr = head;

    for (size_t i = 1; i < values.size(); ++i) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }

    int K = 2;
    cout << "Original DLL:              ";
    printDLL(head);

    head = solver.reverseKGroupDLL(head, K);
    cout << "Reversed in groups of 2:   ";
    printDLL(head); // Expected: 8 <-> 10 <-> 2 <-> 4 <-> 7 <-> 5 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each node is visited and its links swapped exactly once: O(N).
 * 
 * Space Complexity:
 *   - Recursion stack: O(N/K) frames.
 *   - Auxiliary Space: O(1) beyond the call stack.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. In DLL chunk reversal, always establish both forward and backward connections:
 *    `head->next = nextHead;` AND `nextHead->prev = head;`.
 */
