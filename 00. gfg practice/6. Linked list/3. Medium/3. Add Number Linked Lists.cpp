/*
    Problem Name: Add Number Linked Lists
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    You are given the head of two singly linked lists head1 and head2 representing two non-negative integers,
    where the Most Significant Digit (MSD) is at the head.
    Return the head of the linked list representing the sum of these two numbers.

    Note: Input lists may contain leading zeros, but the output list MUST NOT contain any leading zeros
          (unless the result itself is 0).

    Examples:
    Input: head1 = 1 -> 2 -> 3, head2 = 9 -> 9 -> 9
    Output: 1 -> 1 -> 2 -> 2
    Explanation: 123 + 999 = 1122.

    Input: head1 = 6 -> 3, head2 = 7
    Output: 7 -> 0
    Explanation: 63 + 7 = 70.

    Constraints:
    1 <= Number of nodes in head1, head2 <= 10^5
    0 <= node->data <= 9

    Expected Complexities:
    Time Complexity: O(N + M)
    Space Complexity: O(1) auxiliary space (excluding result list nodes).

    Approach 1: Reverse Both Lists + Digit-by-Digit Addition + Reverse Result (Optimal - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Trim Leading Zeros:
       - Strip any extraneous leading zeros from input lists `head1` and `head2`.
    2. Reverse Input Lists:
       - Since addition starts from the Least Significant Digit (LSD), reverse both lists.
    3. Addition with Carry:
       - Traverse reversed lists simultaneously using two pointers.
       - Sum corresponding digits along with `carry`. Append `sum % 10` to the result list and update `carry = sum / 10`.
    4. Reverse Result & Trim Leading Zeros:
       - Reverse the result list to bring MSD back to the front.
       - Remove any leftover leading zeros from the final result list.
*/

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Reverse Lists + Addition + Reverse Result (Optimal - Striver & Love Babbar)
// ============================================================================
class SolutionReversal {
private:
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;

        while (curr != nullptr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }

        return prev;
    }

    Node* trimLeadingZeros(Node* head) {
        while (head != nullptr && head->data == 0 && head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

public:
    Node* addTwoLists(Node* head1, Node* head2) {
        // Step 1: Trim leading zeros from input lists
        head1 = trimLeadingZeros(head1);
        head2 = trimLeadingZeros(head2);

        // Step 2: Reverse both linked lists
        head1 = reverseList(head1);
        head2 = reverseList(head2);

        // Step 3: Digit-by-digit addition
        Node dummy(0);
        Node* curr = &dummy;
        int carry = 0;

        Node* p1 = head1;
        Node* p2 = head2;

        while (p1 != nullptr || p2 != nullptr || carry != 0) {
            int sum = carry;

            if (p1 != nullptr) {
                sum += p1->data;
                p1 = p1->next;
            }

            if (p2 != nullptr) {
                sum += p2->data;
                p2 = p2->next;
            }

            carry = sum / 10;
            curr->next = new Node(sum % 10);
            curr = curr->next;
        }

        // Step 4: Reverse the result list back to MSD first order
        Node* resHead = reverseList(dummy.next);

        // Step 5: Trim any leading zeros in result
        return trimLeadingZeros(resHead);
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* addTwoLists(Node* head1, Node* head2) {
        SolutionReversal solver;
        return solver.addTwoLists(head1, head2);
    }
};

// ============================================================================
// Helper Functions for Testing
// ============================================================================

// Helper to create a linked list from a vector
Node* createList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    Node* head = new Node(values[0]);
    Node* curr = head;
    for (size_t i = 1; i < values.size(); i++) {
        curr->next = new Node(values[i]);
        curr = curr->next;
    }
    return head;
}

// Helper to print linked list
void printList(Node* head) {
    Node* curr = head;
    while (curr) {
        cout << curr->data;
        if (curr->next) cout << " -> ";
        curr = curr->next;
    }
    cout << "\n";
}

int main() {
    // Example 1: 123 + 999 = 1122
    // Expected Output: 1 -> 1 -> 2 -> 2
    Node* head1 = createList({1, 2, 3});
    Node* head2 = createList({9, 9, 9});

    cout << "Example 1 Input:\nList 1: ";
    printList(head1);
    cout << "List 2: ";
    printList(head2);

    SolutionReversal solver;
    Node* res1 = solver.addTwoLists(head1, head2);
    cout << "Example 1 Sum: ";
    printList(res1);
    cout << "\n";

    // Example 2: 63 + 7 = 70
    // Expected Output: 7 -> 0
    Node* head3 = createList({6, 3});
    Node* head4 = createList({7});

    cout << "Example 2 Input:\nList 1: ";
    printList(head3);
    cout << "List 2: ";
    printList(head4);

    Node* res2 = solver.addTwoLists(head3, head4);
    cout << "Example 2 Sum: ";
    printList(res2);

    return 0;
}
