/*
    Problem Name: Modify Linked List-1
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a singly linked list, modify the list as follows:
    - Pair the 1st node with the last node, 2nd node with 2nd last node, and so on.
    - For each node in the first half, replace its value with: (value of paired node) - (its current value).
    - Replace the values of nodes in the second half with the original values of corresponding first-half nodes.
    - If the list has an odd number of nodes, the middle node remains unchanged.
    - Return the head of the modified linked list.

    Examples:
    Input: 10 -> 4 -> 5 -> 3 -> 6 -> nullptr
    Output: -4 -> -1 -> 5 -> 4 -> 10 -> nullptr
    Explanation: Pair (10, 6) -> 1st node = 6 - 10 = -4, last node = 10.
                 Pair (4, 3)  -> 2nd node = 3 - 4 = -1, 2nd last node = 4.
                 Middle node (5) remains unchanged.

    Input: 2 -> 9 -> 8 -> 12 -> 7 -> 10 -> nullptr
    Output: 8 -> -2 -> 4 -> 8 -> 9 -> 2 -> nullptr

    Constraints:
    1 <= size of linked list <= 10^6
    -10^5 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Vector Storage (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Middle Split + Reverse 2nd Half + Process + Reverse Back (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Copy all node data into `vector<int> arr`.
       - For `i = 0` to `N/2 - 1`:
         * `arr[i] = orig[N - 1 - i] - orig[i];`
         * `arr[N - 1 - i] = orig[i];`
       - Overwrite linked list values with `arr`.
       - Time: O(N), Space: O(N).

    2. Optimal In-Place Reversal (Approach 2):
       - Step 1 (Find Middle): Find middle node `slow` using fast and slow pointers.
       - Step 2 (Reverse 2nd Half): Reverse the sublist starting from `slow->next`.
       - Step 3 (Process): Traverse first half (`p1`) and reversed second half (`p2`).
         Save original `p1->data`, set `p1->data = p2->data - origP1`, and set `p2->data = origP1`.
       - Step 4 (Restore List): Reverse the second half again and reattach to `slow->next`.
       - Time: O(N), Auxiliary Space: O(1).

    DRY RUN:
    Example: 10 -> 4 -> 5 -> 3 -> 6
    - Find middle: slow points to 5.
    - Reverse 2nd half (3 -> 6): 6 -> 3.
    - Process pairs:
      * p1 = 10, p2 = 6 -> p1->data = 6 - 10 = -4, p2->data = 10
      * p1 = 4,  p2 = 3 -> p1->data = 3 - 4 = -1,  p2->data = 4
    - Reverse 2nd half back (10 -> 4): 4 -> 10. Reattach to 5->next.
    - Result: -4 -> -1 -> 5 -> 4 -> 10.
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
// Approach 1: Vector Storage (O(N) Time, O(N) Space)
// ============================================================================
class SolutionVector {
public:
    Node* modifyTheList(Node* head) {
        if (!head || !head->next) return head;

        vector<int> arr;
        Node* curr = head;
        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        int n = arr.size();
        vector<int> orig = arr;

        for (int i = 0; i < n / 2; i++) {
            arr[i] = orig[n - 1 - i] - orig[i];
            arr[n - 1 - i] = orig[i];
        }

        curr = head;
        int i = 0;
        while (curr != nullptr) {
            curr->data = arr[i++];
            curr = curr->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 2: Middle Split + Reverse 2nd Half + Process + Reverse Back (Optimal O(N) Time, O(1) Space)
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
    Node* modifyTheList(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Find the middle of the linked list
        Node* slow = head;
        Node* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // // this following is also valid. you are thinking correctly

        // Node* slow = head;
        // Node* fast = head->next;
        // while (fast && fast->next) {
        //     slow = slow->next;
        //     fast = fast->next->next;
        // }

        // Step 2: Reverse the second half of the linked list
        Node* secondHalfHead = reverseList(slow->next);

        // Step 3: Process paired nodes and update values
        Node* p1 = head;
        Node* p2 = secondHalfHead;

        while (p2 != nullptr) {
            int origP1 = p1->data;
            p1->data = p2->data - origP1;
            p2->data = origP1;

            p1 = p1->next;
            p2 = p2->next;
        }

        // Step 4: Reverse the second half back and restore original structure
        slow->next = reverseList(secondHalfHead);

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* modifyTheList(Node* head) {
        SolutionOptimal solver;
        return solver.modifyTheList(head);
    }
};
