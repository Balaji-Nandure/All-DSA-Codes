/*
Problem:
Merge K Sorted Linked Lists

Given an array of K linked lists, each sorted in increasing order,
merge all the linked lists into one sorted linked list
and return its head.

Important:
- Nodes should be reused (do NOT create new nodes unnecessarily).
- Result list should be sorted.
- Efficient solution expected.

Examples:
Input:
lists = [
  1 -> 4 -> 5,
  1 -> 3 -> 4,
  2 -> 6
]
Output:
1 -> 1 -> 2 -> 3 -> 4 -> 4 -> 5 -> 6


-----------------------------------
Approach (Expected / Optimal – Min Heap / Priority Queue):
-----------------------------------
1. Use a min-heap (priority_queue) that compares nodes by data.
2. Insert the head of each non-empty list into the heap.
3. Create a dummy node to build the result list.
4. While heap is not empty:
   - Extract the smallest node.
   - Attach it to the result list.
   - If extracted node has a next node,
     push that next node into the heap.
5. Return dummy->next as the merged list head.

Why this works:
- Heap always gives the smallest current node among K lists.
- Each node is pushed and popped exactly once.
- Much faster than merging lists one by one.

Time Complexity:
O(N log K)
where N = total number of nodes across all lists

Space Complexity:
O(K)   (heap space)


GeeksforGeeks:
https://www.geeksforgeeks.org/merge-k-sorted-linked-lists/

LeetCode:
https://leetcode.com/problems/merge-k-sorted-lists/
*/


// Definition for singly-linked list node
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


// Comparator for min-heap
struct compare {
    bool operator()(Node* a, Node* b) {
        return a->data > b->data;
    }
};


Node* mergeKLists(vector<Node*>& lists) {

    // Min heap
    priority_queue<Node*, vector<Node*>, compare> pq;

    // Step 1: Push head of each list
    for (Node* head : lists) {
        if (head != NULL) {
            pq.push(head);
        }
    }

    // Dummy node to build result
    Node dummy(-1);
    Node* tail = &dummy;

    // Step 2: Extract minimum and build merged list
    while (!pq.empty()) {

        Node* curr = pq.top();
        pq.pop();

        tail->next = curr;
        tail = curr;

        if (curr->next != NULL) {
            pq.push(curr->next);
        }
    }

    tail->next = NULL; // safety

    return dummy.next;
}
