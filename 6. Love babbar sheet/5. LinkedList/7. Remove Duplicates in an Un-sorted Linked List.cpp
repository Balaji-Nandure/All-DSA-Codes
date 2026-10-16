/**
 * ============================================================================
 * Problem: Remove Duplicates from an Unsorted Linked List
 * Category: LinkedList
 * 
 * Problem Statement:
 * Given an UNSORTED singly linked list of N nodes. Remove all duplicate elements
 * such that only the FIRST occurrence of every element is retained in the list,
 * preserving their original relative ordering.
 * 
 * Example 1:
 * Input:  5 -> 2 -> 2 -> 4 -> NULL
 * Output: 5 -> 2 -> 4 -> NULL
 * 
 * Example 2:
 * Input:  10 -> 25 -> 10 -> 30 -> 25 -> NULL
 * Output: 10 -> 25 -> 30 -> NULL
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Unsorted vs Sorted Topology:
 *    - In Problem 6, duplicates were strictly adjacent, allowing O(1) space detection.
 *    - In an unsorted linked list, duplicate values can appear anywhere throughout
 *      the list, potentially separated by thousands of other nodes.
 * 2. Order Preservation:
 *    - Sorting the list using Merge Sort would take O(N log N) time, but it destroys
 *      the original order of elements (which is strictly disallowed).
 *    - Therefore, an `unordered_set` is required to achieve linear O(N) time while
 *      faithfully preserving the earliest appearance order.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Approach 1: Hash Set Lookup (Optimal O(N) Time, O(N) Space)
 *   - Use an `unordered_set<int> visitedValues`.
 *   - Traverse with two pointers: `prev` and `curr`.
 *   - If `visitedValues` contains `curr->data`:
 *       - Duplicate! Link `prev->next = curr->next`.
 *       - Deallocate `delete curr`.
 *       - Advance `curr = prev->next`.
 *   - Else:
 *       - Insert `curr->data` into set.
 *       - Advance `prev = curr`, `curr = curr->next`.
 *   - Runs in O(N) average time.
 * 
 * Approach 2: Runner Pointer Technique (O(N^2) Time, O(1) Auxiliary Space)
 *   - For each node, run an inner loop through the rest of the list to delete duplicates.
 *   - Useful when memory is extremely constrained (embedded systems).
 * ============================================================================
 */

#include <iostream>
#include <unordered_set>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
public:
    /**
     * Method 1: Optimal O(N) Time Hash Set approach.
     * Retains the first occurrence of each value and deletes subsequent duplicates.
     */
    Node* removeDuplicatesHashSet(Node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        unordered_set<int> seen;
        Node* curr = head;
        Node* prev = nullptr;

        while (curr != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Hash table lookup identifies duplicate values in O(1) average time regardless
            // of where they appear in the unsorted sequence, without altering original order.
            if (seen.find(curr->data) != seen.end()) {
                prev->next = curr->next;  // Bypass duplicate node
                Node* duplicate = curr;
                curr = curr->next;
                delete duplicate;         // Clean up memory
            } else {
                seen.insert(curr->data);  // Mark value as seen
                prev = curr;
                curr = curr->next;
            }
        }

        return head;
    }

    /**
     * Method 2: Runner Technique (O(N^2) Time, O(1) Space)
     */
    Node* removeDuplicatesRunner(Node* head) {
        Node* ptr1 = head;

        while (ptr1 != nullptr && ptr1->next != nullptr) {
            Node* ptr2 = ptr1;
            while (ptr2->next != nullptr) {
                if (ptr1->data == ptr2->next->data) {
                    Node* dup = ptr2->next;
                    ptr2->next = ptr2->next->next;
                    delete dup;
                } else {
                    ptr2 = ptr2->next;
                }
            }
            ptr1 = ptr1->next;
        }

        return head;
    }
};

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1: 10 -> 25 -> 10 -> 30 -> 25 -> NULL
    Node* head1 = new Node(10);
    head1->next = new Node(25);
    head1->next->next = new Node(10);
    head1->next->next->next = new Node(30);
    head1->next->next->next->next = new Node(25);

    cout << "Original Unsorted List: ";
    printList(head1);

    head1 = solver.removeDuplicatesHashSet(head1);
    cout << "Deduplicated (HashSet):  ";
    printList(head1);

    // Test Case 2: 5 -> 2 -> 2 -> 4 -> NULL
    Node* head2 = new Node(5);
    head2->next = new Node(2);
    head2->next->next = new Node(2);
    head2->next->next->next = new Node(4);

    head2 = solver.removeDuplicatesHashSet(head2);
    cout << "\nDeduplicated Test 2:     ";
    printList(head2);

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Method 1 (Hash Set):
 *   - Time Complexity: O(N) average time for N hash set lookups and insertions.
 *   - Space Complexity: O(N) to store distinct elements in the unordered_set.
 * 
 * Method 2 (Runner Technique):
 *   - Time Complexity: O(N^2) worst case due to nested loops.
 *   - Space Complexity: O(1) auxiliary space.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. When problem statement requires retaining original relative ordering in an
 *    unsorted sequence, hashing is mandatory for achieving linear O(N) performance.
 * 2. Always maintain `prev` to perform single-link pointer bypasses efficiently.
 */
