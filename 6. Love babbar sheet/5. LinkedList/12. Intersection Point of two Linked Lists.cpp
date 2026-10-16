/**
 * ============================================================================
 * Problem: Intersection Point in Y-Shaped Linked Lists (LeetCode 160)
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given the heads of two singly linked-lists headA and headB, return the node 
 * at which the two lists intersect. If the two linked lists have no intersection 
 * at all, return NULL.
 * 
 * The two lists merge into a common segment (forming a "Y" shape), sharing 
 * the exact same node addresses from the intersection point to the end.
 * 
 * Constraints:
 * 1 <= Number of nodes in each list <= 10^5
 * -10^9 <= Node.val <= 10^9
 * Must run in O(N + M) time and O(1) auxiliary space without modifying the list structure.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Reference / Memory Address vs Value Equality:
 *    - In Problem 11, intersection was defined by identical VALUES in two sorted lists.
 *    - Here, the lists can contain any arbitrary unsorted values.
 *    - Intersection is defined by MEMORY ADDRESS (i.e. `ptrA == ptrB`).
 * 2. Asymmetric Prefix Lengths:
 *    - List A might have 10 nodes before the junction, while List B might have only 2.
 *    - Because both lists share the exact same suffix of length C, any algorithm
 *      must align the two traversal pointers equidistant from the end.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: Dual-Pointer End-to-End Switching (The Gold Standard)
 *   - Initialize `ptrA = headA` and `ptrB = headB`.
 *   - While `ptrA != ptrB`:
 *       - If `ptrA == nullptr`: switch to `headB`. Else `ptrA = ptrA->next`.
 *       - If `ptrB == nullptr`: switch to `headA`. Else `ptrB = ptrB->next`.
 *   - Mathematical Proof:
 *       Let list A have length (a + c), where 'a' is unique prefix, 'c' is shared suffix.
 *       Let list B have length (b + c), where 'b' is unique prefix, 'c' is shared suffix.
 *       Pointer A travels: a + c (List A) + b (to intersection in List B) = a + b + c.
 *       Pointer B travels: b + c (List B) + a (to intersection in List A) = a + b + c.
 *       Both pointers travel the EXACT SAME TOTAL DISTANCE (a + b + c)!
 *       Therefore, they are guaranteed to meet at the intersection node on the second pass,
 *       or simultaneously land on `nullptr` if no intersection exists.
 *   - Zero length counting passes, pure O(1) space, and zero pointer modifications.
 * 
 * Approach 2: Length Difference Method
 *   - Count lengths lenA and lenB. Advance the longer list pointer by |lenA - lenB|.
 *   - Advance both pointers in lockstep until they collide.
 * ============================================================================
 */

#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Method 1: Dual-Pointer Switching (Optimal O(N + M) Time, O(1) Auxiliary Space)
     */
    Node* getIntersectionNode(Node* headA, Node* headB) {
        if (headA == nullptr || headB == nullptr) return nullptr;

        Node* ptrA = headA;
        Node* ptrB = headB;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Switching each pointer to the OTHER list's head upon reaching NULL
        // guarantees that both pointers traverse exactly (lenA + lenB) distance,
        // synchronizing their arrival at the shared junction node or terminating at NULL.
        while (ptrA != ptrB) {
            ptrA = (ptrA == nullptr) ? headB : ptrA->next;
            ptrB = (ptrB == nullptr) ? headA : ptrB->next;
        }

        return ptrA; // Either the intersection node, or nullptr if no intersection exists
    }

    /**
     * Method 2: Length Difference Calculation
     */
    Node* getIntersectionNodeByLength(Node* headA, Node* headB) {
        int lenA = 0, lenB = 0;
        Node* currA = headA;
        Node* currB = headB;

        while (currA) { lenA++; currA = currA->next; }
        while (currB) { lenB++; currB = currB->next; }

        currA = headA;
        currB = headB;

        // Advance the longer list by the difference in lengths
        if (lenA > lenB) {
            for (int i = 0; i < lenA - lenB; ++i) currA = currA->next;
        } else {
            for (int i = 0; i < lenB - lenA; ++i) currB = currB->next;
        }

        // Walk in tandem until pointers match
        while (currA != nullptr && currB != nullptr) {
            if (currA == currB) return currA;
            currA = currA->next;
            currB = currB->next;
        }

        return nullptr;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Shared suffix: 8 -> 4 -> 5 -> NULL
    Node* common = new Node(8);
    common->next = new Node(4);
    common->next->next = new Node(5);

    // List A: 4 -> 1 -> [common]
    Node* headA = new Node(4);
    headA->next = new Node(1);
    headA->next->next = common;

    // List B: 5 -> 6 -> 1 -> [common]
    Node* headB = new Node(5);
    headB->next = new Node(6);
    headB->next->next = new Node(1);
    headB->next->next->next = common;

    Node* intersection = solver.getIntersectionNode(headA, headB);
    cout << "Test 1 Intersection Value = " 
         << (intersection ? to_string(intersection->data) : "NULL")
         << " (Expected: 8)\n";

    // Test 2: Two separate non-intersecting lists
    Node* headC = new Node(10);
    headC->next = new Node(20);
    Node* headD = new Node(30);
    headD->next = new Node(40);

    Node* intersection2 = solver.getIntersectionNode(headC, headD);
    cout << "Test 2 Non-intersecting = " 
         << (intersection2 ? to_string(intersection2->data) : "NULL")
         << " (Expected: NULL)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Each pointer traverses at most (lenA + lenB) nodes.
 *   - Total Time: O(N + M) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Swapping paths `(A -> B)` and `(B -> A)` equalizes the total traversed path
 *    without explicit length computation.
 * 2. Never confuse node address equality (`ptrA == ptrB`) with value equality (`ptrA->data == ptrB->data`).
 */
