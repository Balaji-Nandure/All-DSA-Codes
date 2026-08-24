/*
    Problem Name: First Node of Loop in Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 142

    Problem Statement:
    Given the head of a singly linked list. If a loop is present in the linked list, return the first node
    (or value of the first node) of the loop. If no loop exists, return -1.

    Examples:
    Input: pos = 2, list = 1 -> 2 -> 3 -> 4 -> 5 -> 3 (loop back to 3)
    Output: 3
    Explanation: The first node of the loop is node with data 3.

    Input: pos = 0, list = 1 -> 2 -> 3 -> nullptr
    Output: -1
    Explanation: No loop exists in the linked list.

    Constraints:
    1 <= no. of nodes <= 10^6
    1 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N)
    Space Complexity: O(1) auxiliary space (Optimal Floyd's Algorithm)

    Approach 1: HashSet Visited Storage (O(N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Floyd's Cycle Detection Algorithm (Optimal O(N) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. HashSet Approach (Approach 1):
       - Traverse the linked list while storing visited node pointers in `unordered_set<Node*>`.
       - The first node encountered that is ALREADY present in the set is the loop's starting node.
       - Time: O(N), Space: O(N).

    2. Optimal Floyd's Cycle Detection (Approach 2):
       - Step 1 (Detect Loop): Use slow pointer (1 step) and fast pointer (2 steps).
         If `slow == fast`, a loop exists. If `fast == nullptr || fast->next == nullptr`, no loop exists.
       - Step 2 (Find Loop Start): Reset a new pointer `ptr` to `head`. Move both `ptr` and `slow` 1 step at a time.
         The node where they meet is the FIRST node of the loop!
       - Mathematical Proof:
         Let distance from head to loop start = L.
         Distance from loop start to meeting point = d.
         Loop perimeter = C.
         When slow and fast meet, `fast` has traveled `2 * (L + d)`, and `slow` has traveled `L + d`.
         Difference = `(L + d) = k * C` (multiple of loop perimeter).
         Thus `L = k * C - d`.
         Moving `ptr` from `head` (L steps) and `slow` from meeting point (L steps) guarantees they meet at loop start!
       - Time: O(N), Space: O(1).

    DRY RUN:
    Example: 1 -> 2 -> 3 -> 4 -> 5 -> (loop to 3)
    - Step 1 (Detect):
      slow: 1 -> 2 -> 3 -> 4 -> 5 -> 3 -> 4
      fast: 1 -> 3 -> 5 -> 4 -> 3 -> 5 -> 4
      slow and fast meet at node(4).
    - Step 2 (Find Loop Start):
      ptr = head (1), slow = node(4).
      Move both 1 step:
      ptr = 2, slow = 5
      ptr = 3, slow = 3 (Met at node 3!).
    - Output: 3 (value of first node of loop).
*/

#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: HashSet Visited Storage (O(N) Space - Striver & Love Babbar)
// ============================================================================
class SolutionHashSet {
public:
    int findFirstNode(Node* head) {
        unordered_set<Node*> visited;
        Node* curr = head;

        while (curr != nullptr) {
            if (visited.count(curr)) {
                return curr->data; // First node of loop
            }
            visited.insert(curr);
            curr = curr->next;
        }

        return -1; // No loop
    }
};

// ============================================================================
// Approach 2: Floyd's Cycle Detection Algorithm (Optimal O(1) Space - Striver & Love Babbar)
// ============================================================================
class SolutionOptimal {
public:
    int findFirstNode(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return -1;
        }

        Node* slow = head;
        Node* fast = head;

        // Step 1: Detect loop using slow and fast pointers
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast) {
                break;
            }
        }

        // If no loop exists
        if (fast == nullptr || fast->next == nullptr) {
            return -1;
        }

        // Step 2: Find starting node of the loop
        Node* ptr = head;

        while (ptr != slow) {
            ptr = ptr->next;
            slow = slow->next;
        }

        return ptr->data; // First node of loop
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int findFirstNode(Node* head) {
        SolutionOptimal solver;
        return solver.findFirstNode(head);
    }
};
