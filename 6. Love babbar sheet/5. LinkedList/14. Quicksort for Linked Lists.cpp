/**
 * ============================================================================
 * Problem: QuickSort on Singly Linked List
 * Category: LinkedList / Sorting
 * 
 * Problem Statement:
 * Given Pointer to the head and tail of a singly linked list, sort the linked list
 * in-place using QuickSort.
 * 
 * Constraints:
 * 1 <= Number of nodes <= 10^5
 * -10^9 <= Node.data <= 10^9
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. QuickSort on Arrays vs QuickSort on Singly Linked Lists:
 *    - In arrays, Hoare's partition uses two pointers moving towards each other
 *      from opposite ends (`left++`, `right--`).
 *    - In singly linked lists, backward movement (`right--`) is IMPOSSIBLE without
 *      O(N) backward scans, because there are no `prev` pointers.
 *    - Therefore, singly linked list quicksort must use Lomuto's unidirectional
 *      partitioning: both pointers move strictly FORWARD.
 * 2. Merge Sort vs QuickSort for Linked Lists:
 *    - As established in Problem 13, Merge Sort is generally preferred for linked lists
 *      because merging requires O(1) extra space and guarantees O(N log N) worst-case time.
 *    - QuickSort on linked lists is useful when we want to sort strictly in-place
 *      without breaking and re-linking pointer graphs.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Lomuto Partition over Node Range [head, tail]:
 *   - Step 1: Select the `tail` node as the pivot.
 *   - Step 2: Maintain pointer `i = head`, pointer `curr = head`.
 *   - Step 3: Iterate `curr` from `head` up to `tail`:
 *       - If `curr->data < pivot`:
 *           Swap `i->data` with `curr->data`.
 *           `prev_i = i;`
 *           `i = i->next;`
 *   - Step 4: After loop, swap `i->data` with `tail->data`.
 *     Now, all nodes before `i` have values < pivot, and all nodes after `i` have values >= pivot.
 *   - Step 5: Recurse on `[head, prev_i]` and `[i->next, tail]`.
 * ============================================================================
 */

#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class Solution {
private:
    /**
     * Finds the tail node of a linked list starting from head.
     */
    Node* getTail(Node* curr) {
        while (curr != nullptr && curr->next != nullptr) {
            curr = curr->next;
        }
        return curr;
    }

    /**
     * Unidirectional Lomuto Partition on linked list range [head, tail].
     * Returns the partition node (pivot's final resting place).
     */
    Node* partition(Node* head, Node* tail) {
        int pivot = tail->data;
        Node* i = head;
        Node* curr = head;

        // Traverse from head to the node just before tail
        while (curr != tail) {
            if (curr->data < pivot) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Lomuto partition in singly linked list: swap data values in-place
                // using strictly unidirectional forward pointers, since backward navigation is impossible.
                swap(i->data, curr->data);
                i = i->next;
            }
            curr = curr->next;
        }

        // Place pivot in its correct position by swapping with node 'i'
        swap(i->data, tail->data);
        return i;
    }

    /**
     * Recursive quicksort helper for sublist [head, tail].
     */
    void quickSortHelper(Node* head, Node* tail) {
        // Base case: 0 or 1 node
        if (head == nullptr || head == tail || head == tail->next) {
            return;
        }

        // Partition the list and get pivot node
        Node* pivotNode = partition(head, tail);

        // Sort left partition: find node immediately preceding pivotNode
        if (head != pivotNode) {
            Node* temp = head;
            while (temp->next != pivotNode) {
                temp = temp->next;
            }
            quickSortHelper(head, temp);
        }

        // Sort right partition: from pivotNode->next to tail
        quickSortHelper(pivotNode->next, tail);
    }

public:
    /**
     * Sorts the singly linked list using QuickSort.
     * @param head Pointer to the head of the list.
     * @return Head of the sorted list.
     */
    Node* quickSort(Node* head) {
        if (head == nullptr || head->next == nullptr) return head;

        Node* tail = getTail(head);
        quickSortHelper(head, tail);
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

    // Test Case: 30 -> 3 -> 4 -> 20 -> 5 -> NULL
    Node* head = new Node(30);
    head->next = new Node(3);
    head->next->next = new Node(4);
    head->next->next->next = new Node(20);
    head->next->next->next->next = new Node(5);

    cout << "Original List: ";
    printList(head);

    head = solver.quickSort(head);
    cout << "Sorted List:   ";
    printList(head); // Expected: 3 -> 4 -> 5 -> 20 -> 30 -> NULL

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Best / Average Case: O(N log N) when pivot partitions the list evenly.
 *   - Worst Case: O(N^2) if the list is already sorted or reverse sorted.
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) in-place value swapping.
 *   - Call Stack Space: O(log N) average, O(N) worst case.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Singly linked lists restrict partition algorithms to unidirectional schemes (Lomuto).
 * 2. Finding the predecessor of `pivotNode` in singly linked list takes O(K) where K is
 *    sublist length, but does not increase the asymptotic O(N log N) average complexity.
 */
