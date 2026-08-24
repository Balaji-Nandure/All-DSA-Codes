/*
    Problem Name: Sort a linked list of 0s, 1s and 2s
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a linked list where nodes can contain values 0s, 1s, and 2s only. Rearrange the list
    so that all 0s appear at the beginning, followed by all 1s, and all 2s are placed at the end.

    Examples:
    Input: 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2 -> nullptr
    Output: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2 -> nullptr

    Input: 2 -> 2 -> 0 -> 1 -> nullptr
    Output: 0 -> 1 -> 2 -> 2 -> nullptr

    Constraints:
    1 <= no. of nodes <= 10^6
    0 <= node->data <= 2

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space

    Approach 1: Naive — Copy to Array & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Better — Count Frequencies of 0s, 1s, and 2s (O(N) Time, O(1) Space - Striver & Love Babbar)
    Approach 3: Optimal — 3 Dummy List Pointers Partitioning (O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Naive Array Copy (Approach 1):
       - Store node data into `vector<int> arr`, sort `arr`, overwrite list node values.
       - Time: O(N log N), Space: O(N).

    2. Frequency Counting (Approach 2):
       - Pass 1: Count total occurrences of 0s, 1s, and 2s in `count0`, `count1`, and `count2`.
       - Pass 2: Overwrite `temp->data` sequentially with 0s, then 1s, then 2s.
       - Time: O(N), Space: O(1).

    3. Optimal 3 Dummy List Partitioning (Approach 3):
       - Create three dummy nodes: `zeroHead`, `oneHead`, `twoHead` to anchor 0s, 1s, and 2s lists.
       - Traverse original list and append nodes to `zero`, `one`, or `two` tail pointers without modifying data.
       - Reconnect the three sublists:
         * `zero->next = (oneHead->next != nullptr) ? oneHead->next : twoHead->next;`
         * `one->next = twoHead->next;`
         * `two->next = nullptr;`
       - Delete dummy nodes to avoid memory leaks.
       - Time: O(N), Space: O(1).
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Naive — Copy to Array & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionNaive {
public:
    Node* segregate(Node* head) {
        vector<int> arr;
        Node* temp = head;

        while (temp != nullptr) {
            arr.push_back(temp->data);
            temp = temp->next;
        }

        sort(arr.begin(), arr.end());

        temp = head;
        int i = 0;
        while (temp != nullptr) {
            temp->data = arr[i++];
            temp = temp->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 2: Better — Count Frequencies of 0s, 1s, and 2s (O(N) Time, O(1) Space)
// ============================================================================
class SolutionCounting {
public:
    Node* segregate(Node* head) {
        int count0 = 0, count1 = 0, count2 = 0;
        Node* temp = head;

        // Step 1: Count frequencies
        while (temp != nullptr) {
            if (temp->data == 0) count0++;
            else if (temp->data == 1) count1++;
            else count2++;
            temp = temp->next;
        }

        // Step 2: Overwrite values
        temp = head;
        while (temp != nullptr) {
            if (count0 > 0) {
                temp->data = 0;
                count0--;
            } else if (count1 > 0) {
                temp->data = 1;
                count1--;
            } else {
                temp->data = 2;
                count2--;
            }
            temp = temp->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 3: Optimal — 3 Dummy List Pointers Partitioning (O(N) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* segregate(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Dummy nodes for 0, 1, and 2 lists
        Node* zeroHead = new Node(-1);
        Node* oneHead = new Node(-1);
        Node* twoHead = new Node(-1);

        // Pointers to the tail of each list
        Node* zero = zeroHead;
        Node* one = oneHead;
        Node* two = twoHead;

        Node* temp = head;

        // Separate nodes into three distinct lists
        while (temp != nullptr) {
            if (temp->data == 0) {
                zero->next = temp;
                zero = zero->next;
            } else if (temp->data == 1) {
                one->next = temp;
                one = one->next;
            } else {
                two->next = temp;
                two = two->next;
            }
            temp = temp->next;
        }

        // Connect zero list with one list (or two list if one list is empty)
        zero->next = (oneHead->next != nullptr) ? oneHead->next : twoHead->next;

        // Connect one list with two list
        one->next = twoHead->next;

        // End the final linked list
        two->next = nullptr;

        // Capture new head
        Node* newHead = zeroHead->next;

        // Free dummy nodes
        delete zeroHead;
        delete oneHead;
        delete twoHead;

        return newHead;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* segregate(Node* head) {
        SolutionOptimal solver;
        return solver.segregate(head);
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
    // Example 1: 1 -> 2 -> 2 -> 1 -> 2 -> 0 -> 2 -> 2
    // Expected Output: 0 -> 1 -> 1 -> 2 -> 2 -> 2 -> 2 -> 2
    Node* head1 = createList({1, 2, 2, 1, 2, 0, 2, 2});
    cout << "Example 1 Input: ";
    printList(head1);

    SolutionOptimal solver;
    Node* res1 = solver.segregate(head1);
    cout << "Example 1 Segregated: ";
    printList(res1);
    cout << "\n";

    // Example 2: 2 -> 2 -> 0 -> 1
    // Expected Output: 0 -> 1 -> 2 -> 2
    Node* head2 = createList({2, 2, 0, 1});
    cout << "Example 2 Input: ";
    printList(head2);

    Node* res2 = solver.segregate(head2);
    cout << "Example 2 Segregated: ";
    printList(res2);

    return 0;
}
