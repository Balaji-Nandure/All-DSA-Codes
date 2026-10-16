/**
 * ============================================================================
 * Problem: Add 1 to a Number Represented as a Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * A number N is represented in a singly linked list such that each digit 
 * corresponds to a node in the list. The most significant digit is at the head,
 * and the least significant digit is at the tail.
 * 
 * Add 1 to this number and return the head of the modified linked list.
 * 
 * Example 1:
 * Input:  4 -> 5 -> 6 -> NULL  (456)
 * Output: 4 -> 5 -> 7 -> NULL  (457)
 * 
 * Example 2:
 * Input:  9 -> 9 -> 9 -> NULL  (999)
 * Output: 1 -> 0 -> 0 -> 0 -> NULL  (1000)
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * 0 <= Node.data <= 9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Arithmetic Carry Propagation in Reverse:
 *    - In elementary arithmetic, addition begins at the least significant digit (LSD)
 *      and ripples carry towards the most significant digit (MSD).
 *    - But in a singly linked list, we can only traverse forward from MSD to LSD!
 * 2. List Growth at the Head:
 *    - If all digits are 9 (e.g. 999), adding 1 produces a new leading carry,
 *      requiring an extra node prepended at the head (e.g. 1 -> 0 -> 0 -> 0).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: Reverse -> Add 1 -> Reverse Back (O(1) Auxiliary Space)
 *   - Step 1: Reverse list so LSD is at the head.
 *   - Step 2: Add 1 to the first node. Propagate carry = sum / 10 and node->data = sum % 10.
 *     Advance until carry becomes 0 or list ends.
 *   - Step 3: If carry == 1 at the end of the list, append a new Node(1).
 *   - Step 4: Reverse the list back to restore MSD-to-LSD order.
 *   - Why this approach: Operates strictly in O(1) auxiliary space without stack overflow.
 * 
 * Approach 2: Recursive Backtracking (Without Reversing)
 *   - Recurse to the last node.
 *   - Add 1 at base case, return carry backwards through the call stack.
 *   - If carry persists after unwinding to head, create a new node and link to head.
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

    /**
     * Recursive helper: adds carry backwards from LSD to MSD.
     * Returns the carry out of the current subtree.
     */
    int addOneRecursiveHelper(Node* node) {
        if (node == nullptr) return 1; // Base case: the 1 we want to add

        int carry = addOneRecursiveHelper(node->next);
        int sum = node->data + carry;
        node->data = sum % 10;
        return sum / 10;
    }

public:
    /**
     * Method 1: Reverse -> Add -> Reverse (Recommended O(1) Auxiliary Space)
     */
    Node* addOne(Node* head) {
        if (head == nullptr) return new Node(1);

        // Step 1: Reverse list to bring LSD to front
        head = reverseList(head);

        // Step 2: Add 1 and ripple carry forward
        Node* curr = head;
        Node* prev = nullptr;
        int carry = 1;

        while (curr != nullptr && carry > 0) {
            int sum = curr->data + carry;
            curr->data = sum % 10;
            carry = sum / 10;
            prev = curr;
            curr = curr->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // If carry is still 1 after exhausting all nodes (e.g. 999 + 1),
        // we must allocate a new node for the highest-order digit '1'.
        if (carry > 0) {
            prev->next = new Node(carry);
        }

        // Step 3: Reverse back to restore original orientation
        return reverseList(head);
    }

    /**
     * Method 2: Recursive without reversing the list (O(N) Call Stack)
     */
    Node* addOneRecursive(Node* head) {
        int carry = addOneRecursiveHelper(head);
        if (carry > 0) {
            Node* newHead = new Node(carry);
            newHead->next = head;
            return newHead;
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

    // Test Case 1: 4 -> 5 -> 6 + 1 = 4 -> 5 -> 7
    Node* head1 = new Node(4);
    head1->next = new Node(5);
    head1->next->next = new Node(6);

    cout << "Test 1 Original: ";
    printList(head1);
    head1 = solver.addOne(head1);
    cout << "Test 1 + 1:      ";
    printList(head1);

    // Test Case 2: 9 -> 9 -> 9 + 1 = 1 -> 0 -> 0 -> 0
    Node* head2 = new Node(9);
    head2->next = new Node(9);
    head2->next->next = new Node(9);

    cout << "\nTest 2 Original: ";
    printList(head2);
    head2 = solver.addOne(head2);
    cout << "Test 2 + 1:      ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Method 1 (Reversal):
 *   - Time Complexity: O(N) - 3 linear passes (reverse, addition, reverse).
 *   - Space Complexity: O(1) auxiliary space strictly.
 * 
 * Method 2 (Recursive):
 *   - Time Complexity: O(N) - Single pass through call stack.
 *   - Space Complexity: O(N) call stack memory.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Linked list arithmetic from right-to-left is naturally solved via reversal
 *    or recursion. Reversal preserves O(1) space guarantees.
 * 2. Don't forget that 999...9 produces an additional leading node!
 */
