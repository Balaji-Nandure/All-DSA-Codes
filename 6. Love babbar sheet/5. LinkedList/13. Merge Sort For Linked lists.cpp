/**
 * ============================================================================
 * Problem: Merge Sort for Linked Lists
 * Category: LinkedList / Sorting
 * 
 * Problem Statement:
 * Given Pointer to the head of the linked list, sort the given linked list using
 * Merge Sort and return the head of the sorted linked list.
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * Required Time Complexity: O(N log N)
 * Auxiliary Space: O(log N) recursive call stack frames.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Linked List Merge vs Array Merge:
 *    - In arrays (Category 4, Problem 33), Merge Sort requires an O(N) temporary
 *      buffer to merge two sorted subarrays.
 *    - In linked lists, merging two sorted lists requires ZERO auxiliary memory (O(1) space)
 *      by simply re-linking existing node `next` pointers!
 * 2. Splitting via Slow & Fast Pointers:
 *    - Because linked lists do not support O(1) random indexing (`mid = (low + high) / 2`),
 *      we find the middle node using Tortoise & Hare (slow & fast pointers).
 *    - The link `mid->next` is severed to create two completely decoupled sublists.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Divide and Conquer (Merge Sort):
 *   - Base Case: If head is NULL or head->next is NULL, list is already sorted.
 *   - Step 1 (Find Middle):
 *       Use slow and fast pointers. Advance slow by 1, fast by 2.
 *       When fast reaches end, slow points to the exact middle node.
 *   - Step 2 (Divide):
 *       `rightHead = slow->next;`
 *       `slow->next = nullptr;` // Sever connection into two independent lists
 *   - Step 3 (Conquer):
 *       `leftSorted = mergeSort(head);`
 *       `rightSorted = mergeSort(rightHead);`
 *   - Step 4 (Combine / Merge):
 *       Merge `leftSorted` and `rightSorted` in O(1) space using dummy head.
 *   - Total Time: T(N) = 2T(N/2) + O(N) = O(N log N).
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
    /**
     * Finds the middle node of the linked list using slow and fast pointers.
     * For even lengths, returns the first middle node so left and right split evenly.
     */
    Node* getMiddle(Node* head) {
        if (head == nullptr) return head;

        Node* slow = head;
        Node* fast = head->next; // Start fast at head->next for first middle in even length

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    /**
     * Merges two sorted linked lists into one sorted linked list in O(1) auxiliary space.
     */
    Node* merge(Node* l1, Node* l2) {
        Node* dummy = new Node(0);
        Node* tail = dummy;

        while (l1 != nullptr && l2 != nullptr) {
            if (l1->data <= l2->data) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }

        // Attach remaining elements directly
        if (l1 != nullptr) tail->next = l1;
        if (l2 != nullptr) tail->next = l2;

        Node* result = dummy->next;
        delete dummy;
        return result;
    }

public:
    /**
     * Sorts the linked list using Merge Sort in O(N log N) time.
     * @param head Head pointer of the linked list.
     * @return Head pointer of the sorted linked list.
     */
    Node* mergeSort(Node* head) {
        // Base case: list of length 0 or 1 is already sorted
        if (head == nullptr || head->next == nullptr) {
            return head;
        }

        // Step 1: Find middle of list
        Node* mid = getMiddle(head);
        Node* rightHead = mid->next;

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Severing the middle node's 'next' pointer physically splits the linked list
        // into two isolated, independent halves for recursion to operate correctly.
        mid->next = nullptr;

        // Step 2: Recursively sort left and right halves
        Node* left = mergeSort(head);
        Node* right = mergeSort(rightHead);

        // Step 3: Merge the two sorted halves
        return merge(left, right);
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

    // Test Case: 3 -> 5 -> 2 -> 4 -> 1 -> NULL
    Node* head = new Node(3);
    head->next = new Node(5);
    head->next->next = new Node(2);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(1);

    cout << "Original List: ";
    printList(head);

    head = solver.mergeSort(head);
    cout << "Sorted List:   ";
    printList(head); // Expected: 1 -> 2 -> 3 -> 4 -> 5 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Finding middle takes O(N) time.
 *   - Merging two halves takes O(N) time.
 *   - Recurrence: T(N) = 2T(N/2) + O(N).
 *   - By Master Theorem: Total Time is O(N log N) in all cases (worst, best, average).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) beyond the O(log N) recursive call stack frames.
 *   - Unlike array merge sort, no auxiliary vector or heap buffer of size N is needed!
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Notice initializing `fast = head->next` in `getMiddle`. If `fast = head`,
 *    a list of size 2 will return `slow = second node`, causing `mid->next = nullptr`
 *    to fail to split the list, resulting in infinite recursion!
 * 2. Merge sort is the preferred sorting algorithm for linked lists due to O(1) merge space.
 */
