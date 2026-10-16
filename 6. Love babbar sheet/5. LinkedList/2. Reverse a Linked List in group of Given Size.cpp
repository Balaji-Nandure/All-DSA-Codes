/**
 * ============================================================================
 * Problem: Reverse a Linked List in Groups of Given Size (Reverse Nodes in k-Group)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given a linked list, reverse every contiguous group of K nodes.
 * If the number of nodes in the last group is less than K, reverse those remaining
 * nodes as well (standard GFG / Love Babbar specification).
 * 
 * Example 1:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> NULL, K = 3
 * Output: 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 8 -> 7 -> NULL
 * 
 * Example 2:
 * Input:  1 -> 2 -> 3 -> 4 -> 5 -> NULL, K = 2
 * Output: 2 -> 1 -> 4 -> 3 -> 5 -> NULL
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 1 <= K <= N
 * -10^9 <= Node.data <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Global vs Local Chunk Reversal:
 *    - In Problem 1, we reversed the entire list once from end-to-end.
 *    - Here, the list is broken into localized chunks of size K.
 *    - The tail of each reversed block must be seamlessly spliced into the head
 *      of the subsequent reversed block.
 * 2. Maintaining Inter-Block Linkages:
 *    - In each chunk of size K, the node that was originally the `head` becomes
 *      the `tail` of that reversed block.
 *    - That tail's `next` pointer must be linked to the result of reversing the
 *      remaining list starting at `forward`.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: Recursive Formulation (Extremely Clean & Intuitive)
 *   - Step 1: Reverse the first K nodes iteratively using standard 3-pointer reversal.
 *     Keep count of reversed nodes (`count < K`).
 *   - Step 2: The pointer `forward` now points to the (K+1)-th node (start of the next group).
 *     Original `head` is now the tail of the current reversed group.
 *   - Step 3: Recurse for the remaining list: `head->next = reverseKGroup(forward, K)`.
 *   - Step 4: Return `prev` (new head of this reversed K-node block).
 * 
 * Approach 2: Constant O(1) Space Iterative with Dummy Node
 *   - For environments with strict O(1) auxiliary space restrictions (no recursion stack).
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
     * Method 1: Elegant Recursive Chunk Reversal
     * Reverses K nodes at a time, recursively connecting each block.
     * Time: O(N), Space: O(N/K) call stack frames.
     */
    Node* reverseKGroupRecursive(Node* head, int k) {
        if (head == nullptr || k <= 1) return head;

        Node* prev = nullptr;
        Node* curr = head;
        Node* forward = nullptr;
        int count = 0;

        // Step 1: Reverse first k nodes of the linked list
        while (curr != nullptr && count < k) {
            forward = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forward;
            count++;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // 'head' was the first node of this group, but after reversal it is now the TAIL.
        // We connect its 'next' pointer directly to the head of the NEXT reversed group returned by recursion.
        if (forward != nullptr) {
            head->next = reverseKGroupRecursive(forward, k);
        }

        // 'prev' is the new head of this reversed K-group
        return prev;
    }

    /**
     * Method 2: Purely Iterative In-Place Reversal (Strict O(1) Auxiliary Space)
     */
    Node* reverseKGroupIterative(Node* head, int k) {
        if (head == nullptr || k <= 1) return head;

        Node* dummy = new Node(0);
        dummy->next = head;

        Node* prevGroupEnd = dummy;
        Node* curr = head;

        while (curr != nullptr) {
            Node* groupStart = curr;
            Node* prev = nullptr;
            Node* forward = nullptr;
            int count = 0;

            // Reverse current block of up to k nodes
            while (curr != nullptr && count < k) {
                forward = curr->next;
                curr->next = prev;
                prev = curr;
                curr = forward;
                count++;
            }

            // Splice reversed block with preceding and succeeding blocks
            prevGroupEnd->next = prev;
            groupStart->next = curr;

            // Advance prevGroupEnd to the tail of the newly reversed group
            prevGroupEnd = groupStart;
        }

        Node* newHead = dummy->next;
        delete dummy;
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

    // List: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> NULL
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);
    head->next->next->next->next->next = new Node(6);
    head->next->next->next->next->next->next = new Node(7);
    head->next->next->next->next->next->next->next = new Node(8);

    cout << "Original List:         ";
    printList(head);

    // Reverse in groups of k = 3
    // Expected: 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 8 -> 7 -> NULL
    head = solver.reverseKGroupRecursive(head, 3);
    cout << "Reversed in groups of 3: ";
    printList(head);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each node is visited and its pointer redirected exactly once: O(N).
 * 
 * Space Complexity:
 *   - Recursive: O(N/K) recursion stack frames.
 *   - Iterative: O(1) auxiliary space strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. The original `head` becomes the `tail` after group reversal.
 * 2. In recursion, let the return value give you the head of the next block,
 *    and hook `head->next = reverseKGroup(...)`.
 */
