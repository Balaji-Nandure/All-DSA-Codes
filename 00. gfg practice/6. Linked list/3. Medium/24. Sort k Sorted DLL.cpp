/*
    Problem Name: Sort k Sorted DLL
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a doubly linked list where each node is at most k-indices away from its target sorted position,
    sort the given doubly linked list in non-decreasing order.

    Examples:
    Input: head : 3 <-> 2 <-> 1 <-> 5 <-> 6 <-> 4, k = 2
    Output: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6
    Explanation: After sorting, the 2-sorted DLL becomes 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6.

    Input: head : 5 <-> 6 <-> 7 <-> 3 <-> 4 <-> 4, k = 3
    Output: 3 <-> 4 <-> 4 <-> 5 <-> 6 <-> 7

    Constraints:
    1 <= number of nodes <= 10^5
    0 <= k < number of nodes
    0 <= node->data <= 10^9

    Expected Complexities:
    Time Complexity: O(N log K)
    Space Complexity: O(K) auxiliary space (for Min-Heap of size k + 1)

    Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space - Striver & Love Babbar)
    Approach 2: Min-Heap Priority Queue of Size (k + 1) (Optimal O(N log K) Time, O(K) Space - Striver & Love Babbar)

    INTUITION & STRATEGY:
    1. Vector Approach (Approach 1):
       - Collect node data into `vector<int> arr`, sort `arr`, overwrite node data in DLL.
       - Time: O(N log N), Space: O(N).

    2. Optimal Min-Heap (Approach 2):
       - Since any node is at most `k` positions away from its sorted position, the minimum element
         among the first `k + 1` nodes MUST be the 1st element of the sorted list.
       - Push the first `k + 1` nodes into a Min-Heap (`priority_queue`).
       - Repeatedly pop the smallest node from the Min-Heap, attach it to the new sorted DLL (updating `next` and `prev`),
         and push the next node from the input list into the heap.
       - Time: O(N log K), Auxiliary Space: O(K).

    DRY RUN:
    Example: 3 <-> 2 <-> 1 <-> 5 <-> 6 <-> 4, k = 2
    - Min-Heap size = k + 1 = 3. Push first 3 nodes: {3, 2, 1}.
    - Pop top -> node(1). Link to sorted DLL: newHead = node(1). Push node(5). Heap: {2, 3, 5}.
    - Pop top -> node(2). Link: 1 <-> 2. Push node(6). Heap: {3, 5, 6}.
    - Pop top -> node(3). Link: 2 <-> 3. Push node(4). Heap: {4, 5, 6}.
    - Pop top -> node(4). Link: 3 <-> 4. Heap: {5, 6}.
    - Pop top -> node(5). Link: 4 <-> 5. Heap: {6}.
    - Pop top -> node(6). Link: 5 <-> 6.
    - Result: 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Definition for Doubly Linked List Node
struct DLLNode {
    int data;
    DLLNode* prev;
    DLLNode* next;
    DLLNode(int val) : data(val), prev(nullptr), next(nullptr) {}
};

// Custom Comparator for Min-Heap of DLLNode pointers
struct CompareDLLNode {
    bool operator()(const DLLNode* a, const DLLNode* b) const {
        return a->data > b->data;
    }
};

// ============================================================================
// Approach 1: Vector Copy & Sort (O(N log N) Time, O(N) Space)
// ============================================================================
class SolutionVectorSort {
public:
    DLLNode* sortAKSortedDLL(DLLNode* head, int k) {
        if (!head || !head->next) return head;

        vector<int> arr;
        DLLNode* curr = head;
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
// Approach 2: Min-Heap of Size (k + 1) (Optimal O(N log K) Time, O(K) Space)
// ============================================================================
class SolutionMinHeap {
public:
    DLLNode* sortAKSortedDLL(DLLNode* head, int k) {
        if (!head || !head->next || k <= 0) return head;

        priority_queue<DLLNode*, vector<DLLNode*>, CompareDLLNode> pq;

        DLLNode* curr = head;

        // Step 1: Push first k + 1 nodes into Min-Heap
        for (int i = 0; curr != nullptr && i <= k; i++) {
            pq.push(curr);
            curr = curr->next;
        }

        DLLNode* dummy = new DLLNode(-1); // User Preferred Heap Dummy Allocation
        DLLNode* newHead = nullptr;
        DLLNode* last = dummy;

        // Step 2: Extract top node, re-link pointers, and push next node from list
        while (!pq.empty()) {
            DLLNode* minNode = pq.top();
            pq.pop();

            if (newHead == nullptr) {
                newHead = minNode;
                newHead->prev = nullptr;
                last = newHead;
            } else {
                last->next = minNode;
                minNode->prev = last;
                last = minNode;
            }

            if (curr != nullptr) {
                pq.push(curr);
                curr = curr->next;
            }
        }

        last->next = nullptr; // Terminate DLL tail
        delete dummy;

        return newHead;
    }
};

// Default Solution Class for GFG Submission
class Solution {
public:
    DLLNode* sortAKSortedDLL(DLLNode* head, int k) {
        SolutionMinHeap solver;
        return solver.sortAKSortedDLL(head, k);
    }
};
