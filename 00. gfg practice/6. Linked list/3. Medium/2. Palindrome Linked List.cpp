/*
    Problem Name: Palindrome Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 234

    Problem Statement:
    Given the head of a singly linked list of positive integers, check if the given linked list is a
    palindrome or not.

    Examples:
    Input: 1 -> 2 -> 1 -> 1 -> 2 -> 1 -> nullptr
    Output: true
    Explanation: The values read the same forward and backward.

    Input: 10 -> 20 -> 30 -> 40 -> 50 -> nullptr
    Output: false

    Constraints:
    1 <= number of nodes <= 10^5
    0 <= node->data <= 10^3

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space (Optimal In-Place Reversal)

    Approach 1: Copy Values to Array / Vector (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Find Middle, Reverse Second Half & Compare (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Copy Approach (Approach 1):
       - Traverse the linked list and copy node values into a `vector<int> arr`.
       - Use two pointers `left` and `right` to check if `arr` is a palindrome.
       - Time: O(N), Space: O(N).

    2. Optimal In-Place Reversal Approach (Approach 2):
       - Step 1 (Find Middle): Use slow (1 step) and fast (2 steps) pointers to find the middle node of the list.
       - Step 2 (Reverse Second Half): Reverse the sublist starting from `slow->next`.
       - Step 3 (Compare Both Halves): Compare node values of the first half (starting from `head`)
         and the reversed second half (starting from `newHead`).
       - Step 4 (Restore Original List): Reverse the second half again and reattach to `slow->next`.
       - Time: O(N), Space: O(1).
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
// Approach 1: Copy Values to Vector (O(N) Time, O(N) Space - Striver & Love Babbar)
// ============================================================================
class SolutionVector {
public:
    bool isPalindrome(Node* head) {
        vector<int> arr;
        Node* curr = head;

        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        int left = 0, right = arr.size() - 1;
        while (left < right) {
            if (arr[left] != arr[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};

// ============================================================================
// Approach 2: Find Middle, Reverse Second Half & Compare (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
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

public:
    bool isPalindrome(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }

        // Step 1: Find the middle of the linked list
        Node* slow = head;
        Node* fast = head;

        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Step 2: Reverse the second half of the linked list
        Node* newHead = reverseList(slow->next);

        // Step 3: Compare first half and reversed second half
        Node* first = head;
        Node* second = newHead;
        bool isPalin = true;

        while (second != nullptr) {
            if (first->data != second->data) {
                isPalin = false;
                break;
            }
            first = first->next;
            second = second->next;
        }

        // Step 4: Restore original linked list structure
        slow->next = reverseList(newHead);

        return isPalin;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    bool isPalindrome(Node* head) {
        SolutionOptimal solver;
        return solver.isPalindrome(head);
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
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "nullptr\n";
}

int main() {
    // Example 1: 1 -> 2 -> 1 -> 1 -> 2 -> 1
    // Expected Output: true
    Node* head1 = createList({1, 2, 1, 1, 2, 1});
    cout << "Example 1 List: ";
    printList(head1);

    SolutionOptimal solver;
    cout << "Example 1 Is Palindrome: " << (solver.isPalindrome(head1) ? "true" : "false") << "\n\n";

    // Example 2: 10 -> 20 -> 30 -> 40 -> 50
    // Expected Output: false
    Node* head2 = createList({10, 20, 30, 40, 50});
    cout << "Example 2 List: ";
    printList(head2);

    cout << "Example 2 Is Palindrome: " << (solver.isPalindrome(head2) ? "true" : "false") << "\n";

    return 0;
}
