/**
 * ============================================================================
 * Problem: Check If a Singly Linked List is a Palindrome (LeetCode 234)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given the head of a singly linked list, determine whether the list is a palindrome
 * (i.e., reads the same forwards and backwards).
 * 
 * Example 1:
 * Input:  1 -> 2 -> 2 -> 1 -> NULL
 * Output: true
 * 
 * Example 2:
 * Input:  1 -> 2 -> 3 -> 2 -> 1 -> NULL
 * Output: true
 * 
 * Example 3:
 * Input:  1 -> 2 -> NULL
 * Output: false
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Must run in O(N) time and O(1) auxiliary space (no recursion stack, no extra array).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Strings/Arrays vs Singly Linked List:
 *    - In arrays or strings (Category 3, Problem 2), checking palindrome is trivial
 *      using two converging pointers: `left++`, `right--` in O(1) space.
 *    - In a singly linked list, there are NO backward pointers, so we cannot walk
 *      backwards from the tail!
 * 2. In-Place Structural Inversion with List Restoration:
 *    - Copying values to a vector takes O(N) extra memory.
 *    - To achieve strict O(1) space, we reverse the SECOND HALF of the list in-place,
 *      compare values, and then reverse the second half back to restore original state.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 4-Step Optimal O(N) Time, O(1) Space:
 *   - Step 1 (Find Middle):
 *       Use Tortoise & Hare: `slow = head, fast = head`.
 *       Advance slow by 1, fast by 2. Slow stops at the middle node.
 *   - Step 2 (Reverse Second Half):
 *       Reverse the list starting from `slow->next` (using Problem 1 logic).
 *       Let `secondHalfHead` point to the reversed second half.
 *   - Step 3 (Compare Halves):
 *       Compare nodes from `head` and `secondHalfHead`. If any values differ,
 *       record `isPal = false`.
 *   - Step 4 (Restore Original List):
 *       Reverse `secondHalfHead` again and reattach to `slow->next`.
 *   - Return `isPal`.
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
     * Checks if the linked list is a palindrome in O(N) time and O(1) space.
     * Restores original list structure before returning.
     */
    bool isPalindrome(Node* head) {
        if (head == nullptr || head->next == nullptr) return true;

        // Step 1: Find first middle node
        Node* slow = head;
        Node* fast = head->next;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Reversing only the second half of the list enables symmetric dual-pointer
        // comparison without allocating an O(N) buffer or recursion stack.
        Node* secondHalfHead = reverseList(slow->next);

        // Step 3: Compare first half and reversed second half
        Node* p1 = head;
        Node* p2 = secondHalfHead;
        bool isPal = true;

        while (p2 != nullptr) {
            if (p1->data != p2->data) {
                isPal = false;
                break;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // Step 4: Restore original list structure by reversing second half back
        slow->next = reverseList(secondHalfHead);

        return isPal;
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

    // Test Case 1: Palindrome 1 -> 2 -> 3 -> 2 -> 1 -> NULL
    Node* head1 = new Node(1);
    head1->next = new Node(2);
    head1->next->next = new Node(3);
    head1->next->next->next = new Node(2);
    head1->next->next->next->next = new Node(1);

    cout << "List 1: ";
    printList(head1);
    cout << "Is Palindrome? " << (solver.isPalindrome(head1) ? "YES" : "NO") 
         << " (Expected: YES)\n";
    cout << "List 1 (After verification/restoration): ";
    printList(head1);

    // Test Case 2: Non-palindrome 1 -> 2 -> 3 -> 4 -> NULL
    Node* head2 = new Node(1);
    head2->next = new Node(2);
    head2->next->next = new Node(3);
    head2->next->next->next = new Node(4);

    cout << "\nList 2: ";
    printList(head2);
    cout << "Is Palindrome? " << (solver.isPalindrome(head2) ? "YES" : "NO") 
         << " (Expected: NO)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Finding middle: N/2 steps.
 *   - Reversing second half: N/2 steps.
 *   - Comparison: N/2 steps.
 *   - Restoring second half: N/2 steps.
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly. Zero heap memory or recursion frames.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Restoring the list to its original state before returning is standard
 *    best engineering practice in production and coding interviews.
 */
