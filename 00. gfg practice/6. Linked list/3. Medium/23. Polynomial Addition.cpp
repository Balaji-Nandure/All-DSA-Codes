/*
    Problem Name: Polynomial Addition
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two polynomials represented by singly linked lists, add them by summing the coefficients of terms
    with the same power. Both linked lists are sorted in descending order of powers.
    If the sum of coefficients for a specific power becomes zero, that term should NOT be included in the result.

    Examples:
    Input: head1 = [1, 3], head2 = [1, 2]
    Output: [1, 3] -> [1, 2]
    Explanation: 1x^3 + 1x^2 = 1x^3 + 1x^2.

    Input: head1 = [1, 3] -> [2, 2], head2 = [3, 3] -> [4, 2]
    Output: [4, 3] -> [6, 2]
    Explanation: (1+3)x^3 + (2+4)x^2 = 4x^3 + 6x^2.

    Constraints:
    1 <= no. of nodes in head1, head2 <= 10^5
    1 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N + M)
    Space Complexity: O(1) auxiliary space (excluding output list)

    Approach 1: Map / TreeMap Aggregation (O((N + M) log K) Time, O(N + M) Space - Striver & Love Babbar)
    Approach 2: 2-Pointer Merge Traversal (Optimal O(N + M) Time, O(1) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Map Aggregation (Approach 1):
       - Store power -> coeff in `map<int, int, greater<int>> polyMap` (keeps powers in descending order).
       - Accumulate coefficients for matching powers.
       - Construct resulting linked list for non-zero sum coefficients.
       - Time: O((N + M) log K), Space: O(N + M).

    2. Optimal 2-Pointer Merge (Approach 2):
       - Maintain `p1` for list 1, `p2` for list 2, and `dummy = new Node(-1, -1)`.
       - While `p1 != nullptr && p2 != nullptr`:
         * If `p1->pow == p2->pow`: Sum `coeff1 + coeff2`. If non-zero, append `new Node(sum, p1->pow)`. Advance both.
         * If `p1->pow > p2->pow`: Append `p1` term to result. Advance `p1`.
         * If `p1->pow < p2->pow`: Append `p2` term to result. Advance `p2`.
       - Append remaining terms of `p1` or `p2`.
       - Time: O(N + M), Auxiliary Space: O(1).

    DRY RUN:
    Example: head1 = [1, 3] -> [2, 2], head2 = [3, 3] -> [4, 2]
    - Compare powers: 3 == 3. sumCoeff = 1 + 3 = 4. Append [4, 3]. Advance p1 & p2.
    - Compare powers: 2 == 2. sumCoeff = 2 + 4 = 6. Append [6, 2]. Advance p1 & p2.
    - Both lists exhausted.
    - Result: [4, 3] -> [6, 2].
*/

#include <iostream>
#include <map>

using namespace std;

// Definition for polynomial linked list node
struct Node {
    int coeff;
    int pow;
    Node* next;
    Node(int c, int p) : coeff(c), pow(p), next(nullptr) {}
};

// ============================================================================
// Approach 1: Map Aggregation (O((N + M) log K) Time, O(N + M) Space)
// ============================================================================
class SolutionMapAggregation {
public:
    Node* addPolynomial(Node* p1, Node* p2) {
        map<int, int, greater<int>> polyMap; // Sort powers in descending order

        while (p1 != nullptr) {
            polyMap[p1->pow] += p1->coeff;
            p1 = p1->next;
        }

        while (p2 != nullptr) {
            polyMap[p2->pow] += p2->coeff;
            p2 = p2->next;
        }

        Node* dummy = new Node(-1, -1);
        Node* temp = dummy;

        for (auto const& [power, coefficient] : polyMap) {
            if (coefficient != 0) {
                temp->next = new Node(coefficient, power);
                temp = temp->next;
            }
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// ============================================================================
// Approach 2: 2-Pointer Merge Traversal (Optimal O(N + M) Time, O(1) Space)
// ============================================================================
class SolutionOptimal {
public:
    Node* addPolynomial(Node* p1, Node* p2) {
        Node* dummy = new Node(-1, -1);
        Node* temp = dummy;

        while (p1 != nullptr && p2 != nullptr) {
            if (p1->pow == p2->pow) {
                int sumCoeff = p1->coeff + p2->coeff;
                if (sumCoeff != 0) {
                    temp->next = new Node(sumCoeff, p1->pow);
                    temp = temp->next;
                }
                p1 = p1->next;
                p2 = p2->next;
            } else if (p1->pow > p2->pow) {
                if (p1->coeff != 0) {
                    temp->next = new Node(p1->coeff, p1->pow);
                    temp = temp->next;
                }
                p1 = p1->next;
            } else {
                if (p2->coeff != 0) {
                    temp->next = new Node(p2->coeff, p2->pow);
                    temp = temp->next;
                }
                p2 = p2->next;
            }
        }

        // Append remaining nodes of p1
        while (p1 != nullptr) {
            if (p1->coeff != 0) {
                temp->next = new Node(p1->coeff, p1->pow);
                temp = temp->next;
            }
            p1 = p1->next;
        }

        // Append remaining nodes of p2
        while (p2 != nullptr) {
            if (p2->coeff != 0) {
                temp->next = new Node(p2->coeff, p2->pow);
                temp = temp->next;
            }
            p2 = p2->next;
        }

        Node* result = dummy->next;
        delete dummy;
        return result;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* addPolynomial(Node* p1, Node* p2) {
        SolutionOptimal solver;
        return solver.addPolynomial(p1, p2);
    }
};
