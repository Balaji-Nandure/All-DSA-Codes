/**
 * ============================================================================
 * Problem: Clone a Linked List with Next and Random Pointer (LeetCode 138)
 * Category: LinkedList
 * 
 * Problem Statement:
 * A linked list of length N is given where each node contains an additional 
 * `random` (or `arbitrary`) pointer, which could point to any node in the list,
 * or null.
 * 
 * Construct a deep copy of the list. None of the pointers in the new list should
 * point to nodes in the original list.
 * 
 * Constraints:
 * 0 <= Number of nodes <= 10^5
 * -10^9 <= Node.val <= 10^9
 * Must run in O(N) time and O(1) auxiliary space (no hash map).
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Deep Graph Copy with Cycles and Arbitrary Back-Edges:
 *    - In simple list cloning, we only clone `next` sequentially.
 *    - Here, `random` pointers can form arbitrary forward edges, backward edges,
 *      or self-loops.
 *    - A node's random target might not even exist yet during a single sequential pass!
 * 2. Hash Map O(N) Space vs Interleaving O(1) Space:
 *    - The naive solution uses an `unordered_map<Node*, Node*>` mapping each original
 *      node to its cloned twin, consuming O(N) auxiliary heap space.
 *    - The Interleaving approach achieves O(1) auxiliary space by temporarily weaving
 *      cloned nodes into the original list!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * 3-Pass Node Interleaving Technique O(N) Time, O(1) Auxiliary Space:
 * 
 *   Pass 1 (Interleave Cloned Nodes):
 *     For each node `curr` in the original list, create a copy `clone = new Node(curr->val)`.
 *     Insert `clone` directly between `curr` and `curr->next`:
 *       Original: 1 -> 2 -> 3
 *       Weaved:   1 -> 1' -> 2 -> 2' -> 3 -> 3'
 * 
 *   Pass 2 (Assign Random Pointers):
 *     Because `1'` is immediately after `1`, and any target node `T` is immediately
 *     followed by its clone `T'`, the cloned random pointer is simply:
 *       `curr->next->random = curr->random ? curr->random->next : nullptr;`
 * 
 *   Pass 3 (Detangle the Lists):
 *     Restore the original list's `next` links and isolate the cloned list:
 *       `curr->next = copy->next;`
 *       `copy->next = (copy->next ? copy->next->next : nullptr);`
 * ============================================================================
 */

#include <iostream>

using namespace std;

// Node definition with next and random pointers
struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int v) : val(v), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    /**
     * Clones a linked list with next and random pointers in O(N) time and O(1) space.
     * @param head Pointer to the head of the original list.
     * @return Head of the deeply cloned linked list.
     */
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        Node* curr = head;

        // Pass 1: Create clone nodes and interleave them directly after original nodes
        while (curr != nullptr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next;
        }

        // Pass 2: Assign random pointers for the cloned nodes
        curr = head;
        while (curr != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // The clone of curr->random is guaranteed to be curr->random->next.
            // Interleaving allows O(1) access to cloned targets without requiring a hash map!
            if (curr->random != nullptr) {
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        // Pass 3: Detangle the interleaved list into original and cloned lists
        curr = head;
        Node* clonedHead = head->next;
        Node* cloneCurr = clonedHead;

        while (curr != nullptr) {
            curr->next = curr->next->next;
            if (cloneCurr->next != nullptr) {
                cloneCurr->next = cloneCurr->next->next;
            }
            curr = curr->next;
            cloneCurr = cloneCurr->next;
        }

        return clonedHead;
    }
};

void printListWithRandom(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << "[" << temp->val << " (R: " 
             << (temp->random ? to_string(temp->random->val) : "NULL") << ")]";
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Create list: 1 -> 2 -> 3
    // Randoms: 1->3, 2->1, 3->NULL
    Node* n1 = new Node(1);
    Node* n2 = new Node(2);
    Node* n3 = new Node(3);

    n1->next = n2;
    n2->next = n3;

    n1->random = n3; // 1's random is 3
    n2->random = n1; // 2's random is 1
    n3->random = nullptr;

    cout << "Original List: ";
    printListWithRandom(n1);

    Node* cloned = solver.copyRandomList(n1);
    cout << "Cloned List:   ";
    printListWithRandom(cloned);

    // Verify deep copy: mutate original value and confirm cloned is independent
    n1->val = 999;
    cout << "\nAfter mutating original head to 999:\n";
    cout << "Original:      ";
    printListWithRandom(n1);
    cout << "Cloned:        ";
    printListWithRandom(cloned); // Cloned head remains 1!

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Pass 1 (Interleaving): O(N).
 *   - Pass 2 (Random pointers): O(N).
 *   - Pass 3 (Detangling): O(N).
 *   - Total Time: O(N) linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly (no hash table or recursion stack used).
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Temporary interleaving (`original -> clone -> original -> clone`) enables
 *    referencing cloned nodes in O(1) time without an O(N) hash map.
 * 2. Always restore the original list cleanly in Pass 3.
 */
