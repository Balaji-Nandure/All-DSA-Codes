/**
 * ============================================================================
 * Problem: Count Triplets in a Sorted Doubly Linked List with Sum Equal to X
 * Category: LinkedList / Doubly Linked List
 * 
 * Problem Statement:
 * Given a sorted Doubly Linked List of distinct positive integers, count the 
 * number of triplets in the list whose sum of data values is equal to a given value `X`.
 * 
 * Example:
 * Input:  1 <-> 2 <-> 4 <-> 5 <-> 6 <-> 8 <-> 9 -> NULL, X = 17
 * Output: 2
 * Explanation:
 *   Triplet 1: (2, 6, 9) -> 2 + 6 + 9 = 17
 *   Triplet 2: (4, 5, 8) -> 4 + 5 + 8 = 17
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^4
 * 1 <= Node.data, X <= 10^9
 * Must run in O(N^2) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. From 2Sum to 3Sum on Bidirectional Graphs:
 *    - In Problem 21, we solved 2Sum on a sorted DLL using convergent two pointers in O(N).
 *    - Here, we extend this to 3Sum: fixing one node and running a 2Sum two-pointer
 *      search on the remaining suffix of the DLL.
 * 2. Strict O(1) Auxiliary Space vs Hashing:
 *    - A hash map would consume O(N) heap allocations.
 *    - The bidirectional nature of the DLL allows O(1) space two-pointer convergence,
 *      matching the efficiency of array 3Sum without converting the DLL into an array!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Fixed-Node + Convergent Two Pointers O(N^2) Time, O(1) Space:
 *   - Step 1: Find the tail node of the DLL once in O(N) time.
 *   - Step 2: Iterate pointer `curr` from `head` up to the third-to-last node.
 *   - Step 3: For each fixed node `curr`:
 *       - Desired pair sum: `target = X - curr->data`.
 *       - Set `left = curr->next`, and `right = tail`.
 *       - While `left != right && right->next != left`:
 *           - If `left->data + right->data == target`:
 *               count++;
 *               left = left->next;
 *               right = right->prev;
 *           - Else if `left->data + right->data < target`:
 *               left = left->next;
 *           - Else:
 *               right = right->prev;
 *   - Total Time: O(N * N) = O(N^2), Space: O(1).
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
     * Counts the number of triplets in a sorted DLL whose sum equals X.
     * @param head Pointer to the head of the sorted DLL.
     * @param x Target sum.
     * @return Number of unique triplets.
     */
    int countTriplets(Node* head, int x) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {
            return 0;
        }

        // Find the tail node
        Node* tail = head;
        while (tail->next != nullptr) {
            tail = tail->next;
        }

        int count = 0;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Fixing 'curr' and applying bidirectional convergence on [curr->next, tail]
        // enables 3Sum on a linked list in strict O(1) auxiliary space without hashing.
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            int target = x - curr->data;
            Node* left = curr->next;
            Node* right = tail;

            while (left != nullptr && right != nullptr && left != right && right->next != left) {
                int pairSum = left->data + right->data;

                if (pairSum == target) {
                    count++;
                    left = left->next;
                    right = right->prev;
                } else if (pairSum < target) {
                    left = left->next;
                } else {
                    right = right->prev;
                }
            }
        }

        return count;
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

    int X = 17;
    int ans = solver.countTriplets(head, X);
    cout << "Triplets with sum " << X << " = " << ans << " (Expected: 2)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Outer loop runs N times.
 *   - Inner two-pointer convergence runs in O(N).
 *   - Total Time: O(N^2) quadratic time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly. Zero heap structures allocated.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Two-pointer convergence can be nested within an outer iterator over a DLL
 *    to solve 3Sum with zero extra memory.
 */
