/*
    Problem Name: QuickSort on Doubly Linked List
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the head of a doubly linked list, sort the linked list using the Quick Sort algorithm
    and return the head of the sorted list.

    Examples:
    Input: head: 4 <-> 2 <-> 9
    Output: 2 <-> 4 <-> 9
    Explanation: After sorting, the doubly linked list becomes 2 <-> 4 <-> 9.

    Input: head: 1 <-> 4 <-> 9 <-> 2
    Output: 1 <-> 2 <-> 4 <-> 9
    Explanation: After sorting, the doubly linked list becomes 1 <-> 2 <-> 4 <-> 9.

    Constraints:
    1 <= no. of nodes <= 10^5
    1 <= node->data <= 10^6

    Expected Complexities:
    Time Complexity: O(N log N) average, O(N^2) worst case.
    Space Complexity: O(log N) recursive call stack space.

    Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: In-Place Lomuto Partitioning on DLL (Optimal O(N log N) Avg Time, O(log N) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect all node values into `vector<int> arr`, sort `arr`, overwrite node values in DLL.
       - Time: O(N log N), Space: O(N).

    2. In-Place Lomuto Partitioning on DLL (Approach 2):
       - Find the `tail` node of the doubly linked list.
       - Implement recursive `_quickSort(head, tail)`:
         * Base condition: Return if `tail == nullptr || head == tail || head == tail->next`.
         * Select `tail` as pivot element.
         * Partition elements around pivot using two-pointer swapping (`i` and `j`).
         * Place pivot in its correct sorted position `p`.
         * Recursively call `_quickSort(head, p->prev)` and `_quickSort(p->next, tail)`.
       - Time: O(N log N) average, Space: O(log N) recursive stack.

    DRY RUN:
    Example: 1 <-> 4 <-> 9 <-> 2
    - head = 1, tail = 2, pivot = 2
    - j traverses:
      j = 1 <= 2 -> i = 1, swap(1, 1) -> [1, 4, 9, 2]
      j = 4 > 2  -> skip
      j = 9 > 2  -> skip
    - Swap i->next(4) and tail(2) -> [1, 2, 9, 4]. Pivot index node is 2.
    - Recurse left on [1] -> sorted.
    - Recurse right on [9, 4] -> partitions into [4, 9].
    - Result: 1 <-> 2 <-> 4 <-> 9.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for Doubly Linked List Node
struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

// ============================================================================
// Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionVectorSort {
public:
    Node* quickSort(Node* head) {
        if (!head || !head->next) return head;

        vector<int> arr;
        Node* curr = head;
        while (curr != nullptr) {
            arr.push_back(curr->data);
            curr = curr->next;
        }

        sort(arr.begin(), arr.end());

        curr = head;
        int i = 0;
        while (curr != nullptr) {
            curr->data = arr[i++];
            curr = curr->next;
        }

        return head;
    }
};

// ============================================================================
// Approach 2: In-Place Lomuto Partitioning on DLL (Optimal O(N log N) Avg Time, O(log N) Space)
// ============================================================================
class SolutionQuickSort {
private:
    // Helper to find the last node of DLL
    Node* lastNode(Node* head) {
        while (head != nullptr && head->next != nullptr) {
            head = head->next;
        }
        return head;
    }

    // Lomuto Partition using tail as pivot
    Node* partition(Node* l, Node* h) {
        int pivot = h->data;
        Node* i = l->prev;

        for (Node* j = l; j != h; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr) ? l : i->next;
                swap(i->data, j->data);
            }
        }

        i = (i == nullptr) ? l : i->next;
        swap(i->data, h->data);
        return i;
    }

    // Recursive helper for QuickSort
    void _quickSort(Node* l, Node* h) {
        if (h != nullptr && l != h && l != h->next) {
            Node* p = partition(l, h);
            _quickSort(l, p->prev);
            _quickSort(p->next, h);
        }
    }

public:
    Node* quickSort(Node* head) {
        if (!head || !head->next) return head;

        Node* tail = lastNode(head);
        _quickSort(head, tail);

        return head;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    Node* quickSort(Node* head) {
        SolutionQuickSort solver;
        return solver.quickSort(head);
    }
};
