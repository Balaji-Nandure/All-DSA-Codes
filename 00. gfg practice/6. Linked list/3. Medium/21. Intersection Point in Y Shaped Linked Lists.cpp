/*
    Problem Name: Intersection Point in Y Shaped Linked Lists
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode 160

    Problem Statement:
    Given the head pointers of two singly linked lists head1 and head2, find and return the exact node
    (or value of the node) where the two linked lists merge into a Y-shape. If they never merge, return NULL / -1.

    Examples:
    Input: head1: 3 -> 6 -> 9 -> 15 -> 30, head2: 10 -> 15 -> 30
    Output: 15
    Explanation: Node 15 is the exact merging point of both lists.

    Input: head1: 4 -> 1 -> 8 -> 4 -> 5, head2: 5 -> 6 -> 1 -> 8 -> 4 -> 5
    Output: 8
    Explanation: Both lists merge at node with value 8.

    Constraints:
    1 <= N, M <= 10^5
    0 <= node->data <= 10^5

    Expected Complexities:
    Time Complexity: O(N + M)
    Space Complexity: O(1) auxiliary space

    Approach 1: HashSet Address Storage (O(N + M) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Length Difference Alignment (O(N + M) Time, O(1) Space - Striver & Love Babbar)
    Approach 3: Two Pointers Cycle Redirection (Optimal O(N + M) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. HashSet Approach (Approach 1):
       - Store all node pointers of `head1` in `unordered_set<Node*> st`.
       - Traverse `head2`: the first node found in `st` is the merging point.
       - Time: O(N + M), Space: O(N).

    2. Length Difference Alignment (Approach 2):
       - Find length `L1` of list 1 and `L2` of list 2.
       - Advance the pointer of the longer list by `|L1 - L2|` steps so both pointers are equidistant from the end.
       - Move both pointers 1 step at a time until `p1 == p2`.
       - Time: O(N + M), Space: O(1).

    3. Optimal Two Pointers Cycle Redirection (Approach 3):
       - Maintain two pointers `p1 = head1` and `p2 = head2`.
       - Advance both pointers 1 step. When `p1` hits `nullptr`, redirect it to `head2`.
         When `p2` hits `nullptr`, redirect it to `head1`.
       - `p1` travels total distance `N + M` and `p2` travels `M + N`.
       - They are guaranteed to meet at the intersection node (or both become `nullptr` if no intersection).
       - Time: O(N + M), Space: O(1).

    DRY RUN:
    Example: head1 = 3 -> 6 -> 9 -> 15 -> 30 (L1=5), head2 = 10 -> 15 -> 30 (L2=3)
    - p1 path: 3 -> 6 -> 9 -> 15 -> 30 -> null -> 10 -> 15
    - p2 path: 10 -> 15 -> 30 -> null -> 3 -> 6 -> 9 -> 15
    - Step 8: p1 and p2 both land on node(15) simultaneously!
    - Return node(15).
*/

#include <iostream>
#include <unordered_set>
#include <cmath>

using namespace std;

// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// ============================================================================
// Approach 1: HashSet Address Storage (O(N + M) Time, O(N) Space)
// ============================================================================
class SolutionHashSet {
public:
    Node* intersectPointNode(Node* head1, Node* head2) {
        unordered_set<Node*> st;
        Node* curr1 = head1;
        while (curr1 != nullptr) {
            st.insert(curr1);
            curr1 = curr1->next;
        }

        Node* curr2 = head2;
        while (curr2 != nullptr) {
            if (st.count(curr2)) {
                return curr2;
            }
            curr2 = curr2->next;
        }

        return nullptr;
    }
};

// ============================================================================
// Approach 2: Length Difference Alignment (O(N + M) Time, O(1) Space)
// ============================================================================
class SolutionLengthDifference {
private:
    int getLength(Node* head) {
        int len = 0;
        while (head != nullptr) {
            len++;
            head = head->next;
        }
        return len;
    }

public:
    Node* intersectPointNode(Node* head1, Node* head2) {
        int l1 = getLength(head1);
        int l2 = getLength(head2);

        Node* p1 = head1;
        Node* p2 = head2;

        if (l1 > l2) {
            for (int i = 0; i < l1 - l2; i++) p1 = p1->next;
        } else {
            for (int i = 0; i < l2 - l1; i++) p2 = p2->next;
        }

        while (p1 != nullptr && p2 != nullptr) {
            if (p1 == p2) return p1;
            p1 = p1->next;
            p2 = p2->next;
        }

        return nullptr;
    }
};

// ============================================================================
// Approach 3: Two Pointers Cycle Redirection (Optimal O(N + M) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* intersectPointNode(Node* head1, Node* head2) {
        if (!head1 || !head2) return nullptr;

        Node* p1 = head1;
        Node* p2 = head2;

        while (p1 != p2) {
            p1 = (p1 == nullptr) ? head2 : p1->next;
            p2 = (p2 == nullptr) ? head1 : p2->next;
        }

        return p1; // Either intersection node or nullptr
    }

    int intersectPoint(Node* head1, Node* head2) {
        Node* node = intersectPointNode(head1, head2);
        return (node != nullptr) ? node->data : -1;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    int intersectPoint(Node* head1, Node* head2) {
        SolutionOptimal solver;
        return solver.intersectPoint(head1, head2);
    }

    Node* intersectPointNode(Node* head1, Node* head2) {
        SolutionOptimal solver;
        return solver.intersectPointNode(head1, head2);
    }
};
