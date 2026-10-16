/**
 * ============================================================================
 * Problem: Multiply Two Numbers Represented by Linked Lists
 * Category: LinkedList / Mathematics
 * 
 * Problem Statement:
 * Given two numbers represented by two linked lists, compute their product.
 * Since the numbers can be very large, return the product modulo 10^9 + 7 (1000000007).
 * 
 * Example 1:
 * Input:
 *   List 1: 3 -> 2 -> NULL (32)
 *   List 2: 2 -> NULL (2)
 * Output: 64
 * 
 * Example 2:
 * Input:
 *   List 1: 1 -> 0 -> 0 -> NULL (100)
 *   List 2: 1 -> 0 -> NULL (10)
 * Output: 1000
 * 
 * Constraints:
 * 1 <= Size of List 1, List 2 <= 10^5
 * 0 <= Node.data <= 9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Addition vs Multiplication of Big-Int Lists:
 *    - In Problem 10 (Add Two Numbers), addition proceeds digit-by-digit with
 *      carry propagation from LSD to MSD.
 *    - In Multiplication, full big-integer multiplication requires O(N * M) digit
 *      cross-products.
 *    - However, competitive programming problems specifying "modulo 10^9 + 7"
 *      allow parsing the stream directly into modular integers using Horner's rule
 *      in O(N + M) time!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Modular Horner's Rule Evaluation O(N + M) Time, O(1) Space:
 *   - Initialize `num1 = 0`, `num2 = 0`.
 *   - Traverse List 1:
 *       `num1 = (num1 * 10 + curr->data) % MOD;`
 *   - Traverse List 2:
 *       `num2 = (num2 * 10 + curr->data) % MOD;`
 *   - Product = `(num1 * num2) % MOD`.
 *   - Single pass over each list, strictly O(1) memory.
 * ============================================================================
 */

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
private:
    const long long MOD = 1000000007LL;

public:
    /**
     * Computes (num1 * num2) % (10^9 + 7) in O(N + M) time and O(1) space.
     * @param l1 Head of first linked list.
     * @param l2 Head of second linked list.
     * @return Product modulo 10^9 + 7.
     */
    long long multiplyTwoLists(Node* l1, Node* l2) {
        long long num1 = 0;
        long long num2 = 0;

        // Traverse first list using Horner's method
        while (l1 != nullptr) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Modular Horner's rule evaluates the high-order decimal number sequentially
            // from MSD to LSD without overflow, eliminating the need to reverse the list.
            num1 = ((num1 * 10) % MOD + l1->data) % MOD;
            l1 = l1->next;
        }

        // Traverse second list
        while (l2 != nullptr) {
            num2 = ((num2 * 10) % MOD + l2->data) % MOD;
            l2 = l2->next;
        }

        // Multiply and take modulo
        return (num1 * num2) % MOD;
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

    // List 1: 3 -> 2 (32)
    Node* l1 = new Node(3);
    l1->next = new Node(2);

    // List 2: 2 (2)
    Node* l2 = new Node(2);

    cout << "List 1: ";
    printList(l1);
    cout << "List 2: ";
    printList(l2);

    long long prod = solver.multiplyTwoLists(l1, l2);
    cout << "Product: " << prod << " (Expected: 64)\n";

    // List 3: 1 -> 0 -> 0 (100)
    Node* l3 = new Node(1);
    l3->next = new Node(0);
    l3->next->next = new Node(0);

    // List 4: 1 -> 0 (10)
    Node* l4 = new Node(1);
    l4->next = new Node(0);

    cout << "\nProduct 2: " << solver.multiplyTwoLists(l3, l4) << " (Expected: 1000)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Traversal of list 1 takes O(N) operations.
 *   - Traversal of list 2 takes O(M) operations.
 *   - Total Time: O(N + M) optimal linear time.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) strictly.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. When an answer is requested modulo M, Horner's rule allows accumulating
 *    numbers in O(N) time without requiring arbitrary precision big-integer allocations.
 */
