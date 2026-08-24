/*
    Problem Name: Remove Cycle in Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a singly linked list. A cycle exists if the last node points back to a previous node,
    forming a loop. Remove the loop from the linked list if it exists.

    Examples:
    Input: 1 -> 3 -> 4 -> (loop to node 3 at pos x = 2)
    Output: true (loop removed: 1 -> 3 -> 4 -> nullptr)

    Input: 1 -> 2 -> 3 -> nullptr (x = 0)
    Output: true (no loop present)

    Input: 1 -> (loop to node 1 at pos x = 1)
    Output: true (loop removed: 1 -> nullptr)

    Constraints:
    1 <= size of linked list <= 10^5
    0 <= x <= size of linked list

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space (Optimal Floyd's Algorithm)

    Approach 1: Brute Force — Store visited nodes in unordered_set (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Optimal — Floyd's Cycle Detection & Removal Algorithm (O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Brute Force (Approach 1):
       - Traverse the linked list while tracking visited node pointers in `unordered_set<Node*>`.
       - If `curr` is already in set, `prev->next = nullptr` breaks the cycle.
       - Time: O(N), Space: O(N).

    2. Optimal Floyd's Cycle Algorithm (Approach 2):
       - Step 1 (Detect Cycle): Use two pointers `slow` (1 step) and `fast` (2 steps).
         If `slow == fast`, a cycle exists. If `fast == nullptr || fast->next == nullptr`, no cycle exists.
       - Step 2 (Find Loop Start): Reset `ptr = head`. Move both `ptr` and `slow` 1 step at a time until `ptr == slow`.
         Their meeting point `cycleStart` is the start of the loop.
       - Step 3 (Break Loop): Traverse from `cycleStart` using `curr` until `curr->next == cycleStart`.
         Set `curr->next = nullptr` to remove the cycle.
       - Time: O(N), Space: O(1).
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: Brute Force — Store visited nodes in unordered_set (O(N) Space)
// ============================================================================
class SolutionHashSet {
public:
    void removeLoop(Node* head) {
        unordered_set<Node*> visited;

        Node* curr = head;
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (visited.count(curr)) {
                prev->next = nullptr;
                return;
            }

            visited.insert(curr);
            prev = curr;
            curr = curr->next;
        }
    }
};

// ============================================================================
// Approach 2: Optimal — Floyd's Cycle Algorithm (O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    void removeLoop(Node* head) {
        if (head == nullptr || head->next == nullptr)
            return;

        Node* slow = head;
        Node* fast = head;

        // Step 1: Detect cycle using slow and fast pointers
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                break;
        }

        // No cycle present
        if (fast == nullptr || fast->next == nullptr)
            return;

        // Step 2: Find starting node of the cycle
        Node* ptr = head;

        while (ptr != slow) {
            ptr = ptr->next;
            slow = slow->next;
        }

        // ptr == slow is the starting node of the loop
        Node* cycleStart = ptr;

        // Step 3: Find the last node of the cycle and break it
        Node* curr = cycleStart;

        while (curr->next != cycleStart) {
            curr = curr->next;
        }

        // Remove cycle
        curr->next = nullptr;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    void removeLoop(Node* head) {
        SolutionOptimal solver;
        solver.removeLoop(head);
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

// Helper to create a cycle at 1-indexed position x
void createCycle(Node* head, int x) {
    if (x == 0 || !head) return;

    Node* cycleNode = nullptr;
    Node* tail = head;
    int pos = 1;

    while (tail->next) {
        if (pos == x) {
            cycleNode = tail;
        }
        tail = tail->next;
        pos++;
    }

    if (pos == x) {
        cycleNode = tail;
    }

    if (cycleNode) {
        tail->next = cycleNode;
    }
}

// Helper to detect if a cycle exists
bool hasCycle(Node* head) {
    if (!head || !head->next) return false;
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// Helper to print linked list
void printList(Node* head) {
    unordered_set<Node*> visited;
    Node* curr = head;
    while (curr) {
        if (visited.count(curr)) {
            cout << "(Loop detected to node with val " << curr->data << ")\n";
            return;
        }
        visited.insert(curr);
        cout << curr->data << " -> ";
        curr = curr->next;
    }
    cout << "nullptr\n";
}

int main() {
    // Example 1: 1 -> 3 -> 4, loop at pos x = 2 (node 3)
    Node* head1 = createList({1, 3, 4});
    createCycle(head1, 2);

    cout << "Example 1 Before removeLoop: ";
    printList(head1);

    SolutionOptimal solver;
    solver.removeLoop(head1);

    cout << "Example 1 After removeLoop: ";
    printList(head1);
    cout << "Cycle present? " << (hasCycle(head1) ? "true" : "false") << "\n\n";

    // Example 2: 1 -> 2 -> 3 (no loop, x = 0)
    Node* head2 = createList({1, 2, 3});
    cout << "Example 2 Before removeLoop: ";
    printList(head2);

    solver.removeLoop(head2);
    cout << "Example 2 After removeLoop: ";
    printList(head2);
    cout << "Cycle present? " << (hasCycle(head2) ? "true" : "false") << "\n\n";

    // Example 3: 1 -> 1 (loop at pos x = 1, self loop)
    Node* head3 = createList({1});
    createCycle(head3, 1);
    
    cout << "Example 3 Before removeLoop: ";
    printList(head3);

    solver.removeLoop(head3);
    cout << "Example 3 After removeLoop: ";
    printList(head3);
    cout << "Cycle present? " << (hasCycle(head3) ? "true" : "false") << "\n";

    return 0;
}
