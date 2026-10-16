/**
 * ============================================================================
 * Problem: Add Two Numbers Represented by Linked Lists
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given two numbers represented by two singly linked lists. Each node contains
 * a single digit. The digits are stored such that the most significant digit (MSD)
 * is at the head, and the least significant digit (LSD) is at the tail.
 * 
 * Add the two numbers and return the sum as a linked list in the same format.
 * (Note: The input lists may contain leading zeros, which should be stripped,
 * and the two lists can have different lengths).
 * 
 * Example 1:
 * Input:
 *   List 1: 4 -> 5 -> NULL (45)
 *   List 2: 3 -> 4 -> 5 -> NULL (345)
 * Output: 3 -> 9 -> 0 -> NULL (45 + 345 = 390)
 * 
 * Example 2:
 * Input:
 *   List 1: 0 -> 0 -> 6 -> 3 -> NULL (63)
 *   List 2: 7 -> NULL (7)
 * Output: 7 -> 0 -> NULL (70)
 * 
 * Constraints:
 * 1 <= Size of List 1, List 2 <= 10^5
 * 0 <= Node.data <= 9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Multi-digit Bivariate Ripple Addition:
 *    - In Problem 9, we added a scalar constant (+1) to a single list.
 *    - Here, two independent lists of differing lengths must be aligned at their
 *      least significant digits.
 * 2. Asymmetric Lengths & Trailing Carry:
 *    - One list may run out of digits while the other continues.
 *    - Carry generated at the most significant digit produces a brand-new node.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 1. Clean Leading Zeros:
 *    - Strip non-significant leading zero nodes from both lists.
 * 2. Invert Orientation via Reversal:
 *    - Reverse List 1 and List 2 in O(1) space so least significant digits
 *      are positioned at the heads.
 * 3. Simultaneous Traversal & Digit Addition:
 *    - Maintain `carry = 0`.
 *    - While `l1 != nullptr` || `l2 != nullptr` || `carry != 0`:
 *        val1 = (l1 ? l1->data : 0)
 *        val2 = (l2 ? l2->data : 0)
 *        sum = val1 + val2 + carry
 *        carry = sum / 10
 *        Append node with value (sum % 10) to result list.
 * 4. Restore Result:
 *    - Reverse the resulting sum list to restore MSD-at-head convention.
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
     * In-place list reversal helper.
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
     * Strips non-significant leading zeros (e.g. 0 -> 0 -> 5 becomes 5).
     */
    Node* trimLeadingZeros(Node* head) {
        while (head != nullptr && head->data == 0 && head->next != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        return head;
    }

public:
    /**
     * Adds two numbers represented by linked lists.
     * @param num1 Head of first linked list.
     * @param num2 Head of second linked list.
     * @return Head of the result linked list representing the sum.
     */
    Node* addTwoLists(Node* num1, Node* num2) {
        // Step 1: Strip leading zeros
        num1 = trimLeadingZeros(num1);
        num2 = trimLeadingZeros(num2);

        // Step 2: Reverse both lists to align least significant digits
        num1 = reverseList(num1);
        num2 = reverseList(num2);

        Node* dummyHead = new Node(0);
        Node* tail = dummyHead;
        int carry = 0;

        // Step 3: Add corresponding digits
        while (num1 != nullptr || num2 != nullptr || carry != 0) {
            int val1 = (num1 != nullptr) ? num1->data : 0;
            int val2 = (num2 != nullptr) ? num2->data : 0;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Full adder logic: sum consists of both operand digits plus incoming carry.
            // Outgoing carry cascades into the next higher decimal place.
            int sum = val1 + val2 + carry;
            carry = sum / 10;

            tail->next = new Node(sum % 10);
            tail = tail->next;

            if (num1 != nullptr) num1 = num1->next;
            if (num2 != nullptr) num2 = num2->next;
        }

        Node* result = dummyHead->next;
        delete dummyHead;

        // Step 4: Reverse the result list to restore original MSD-to-LSD order
        return reverseList(result);
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

    // List 1: 4 -> 5 (45)
    Node* num1 = new Node(4);
    num1->next = new Node(5);

    // List 2: 3 -> 4 -> 5 (345)
    Node* num2 = new Node(3);
    num2->next = new Node(4);
    num2->next->next = new Node(5);

    cout << "Number 1: ";
    printList(num1);
    cout << "Number 2: ";
    printList(num2);

    Node* sumResult = solver.addTwoLists(num1, num2);
    cout << "Sum:      ";
    printList(sumResult); // Expected: 3 -> 9 -> 0 -> NULL (390)

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Reversing both input lists: O(N + M).
 *   - Addition loop: O(max(N, M)).
 *   - Reversing the output list: O(max(N, M)).
 *   - Total Time: O(N + M) optimal linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond the nodes allocated for the output list.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Dummy heads dramatically reduce code duplication when building new linked lists.
 * 2. Combining `while (num1 != nullptr || num2 != nullptr || carry != 0)` cleanly
 *    handles unequal list lengths and the terminal carry node in a single loop.
 */
