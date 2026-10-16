/**
 * ============================================================================
 * Problem: Find Pairs with a Given Sum in a Sorted Doubly Linked List
 * Category: LinkedList / Doubly Linked List
 * 
 * Problem Statement:
 * Given a sorted Doubly Linked List of positive distinct integers, find all pairs
 * of nodes whose sum is equal to a given value `target`.
 * 
 * Example:
 * Input:  1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9 -> NULL, Target = 7
 * Output: (1, 6), (2, 5)
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data, target <= 10^9
 * Must run in O(N) time and O(1) auxiliary space (excluding result pairs).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Bidirectional Convergent Two Pointers in Linked Structures:
 *    - In a Singly Linked List (Problem 10/11), two pointers can only move FORWARD.
 *      Finding pairs with a sum in a sorted SLL would require an O(N) hash set
 *      or repeated O(N^2) scans.
 *    - In a Doubly Linked List, because every node contains a `prev` pointer,
 *      we can directly adapt the classic Array Two-Pointer Convergent technique!
 * 2. Pointer Collision & Crossing Termination:
 *    - In arrays, pointers terminate when `left >= right` (index comparison).
 *    - In a DLL, pointers do not have numeric indices.
 *    - Crossing occurs when:
 *        1. `left == right` (met at the exact same node, odd distance).
 *        2. `right->next == left` (crossed past each other, even distance).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Two-Pointer Convergent Scan O(N) Time, O(1) Space:
 *   - Step 1: Initialize `left = head`.
 *   - Step 2: Traverse to find the tail: `right = head; while (right->next) right = right->next;`.
 *   - Step 3: While `left != right && right->next != left`:
 *       - `currentSum = left->data + right->data;`
 *       - If `currentSum == target`:
 *           Record pair `(left->data, right->data)`.
 *           `left = left->next;`
 *           `right = right->prev;`
 *       - Else if `currentSum < target`:
 *           `left = left->next;` // Need larger sum
 *       - Else:
 *           `right = right->prev;` // Need smaller sum
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class Solution {
public:
    /**
     * Finds all pairs in a sorted Doubly Linked List that sum to target.
     * @param head Pointer to the head of the sorted DLL.
     * @param target Target sum.
     * @return Vector of pairs summing to target.
     */
    vector<pair<int, int>> findPairsWithGivenSum(Node* head, int target) {
        vector<pair<int, int>> result;
        if (head == nullptr || head->next == nullptr) {
            return result;
        }

        // Initialize left at head and right at tail
        Node* left = head;
        Node* right = head;
        while (right->next != nullptr) {
            right = right->next;
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // In a DLL without numeric indices, termination occurs when pointers meet
        // (left == right) OR when they step past each other (right->next == left).
        while (left != right && right->next != left) {
            int currentSum = left->data + right->data;

            if (currentSum == target) {
                result.push_back({left->data, right->data});
                left = left->next;
                right = right->prev;
            } else if (currentSum < target) {
                left = left->next;
            } else {
                right = right->prev;
            }
        }

        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create sorted DLL: 1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9 -> NULL
    vector<int> values = {1, 2, 4, 5, 6, 8, 9};
    Node* head = new Node(values[0]);
    Node* curr = head;

    for (size_t i = 1; i < values.size(); ++i) {
        Node* newNode = new Node(values[i]);
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }

    int target = 7;
    vector<pair<int, int>> pairs = solver.findPairsWithGivenSum(head, target);

    cout << "Pairs with sum " << target << ":\n";
    for (auto& p : pairs) {
        cout << "(" << p.first << ", " << p.second << ")\n";
    }
    // Expected: (1, 6), (2, 5)

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Finding the tail takes N steps: O(N).
 *   - Two pointers converge in at most N steps: O(N).
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond the output list of pairs.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Doubly linked lists bridge the gap between arrays and pointer structures,
 *    restoring the power of convergent two-pointer algorithms.
 * 2. Crucial termination check: `left != right && right->next != left`.
 */
