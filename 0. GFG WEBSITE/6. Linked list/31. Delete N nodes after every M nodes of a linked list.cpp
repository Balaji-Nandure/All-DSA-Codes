/*
Problem:
Delete N Nodes After Every M Nodes of a Linked List

Given a singly linked list, an integer M and an integer N,
delete N nodes after every M nodes in the list and
return the modified head.

Rules:
- Traverse the list from the beginning.
- Skip (keep) M nodes.
- Then delete the next N nodes.
- Repeat the process until the list ends.
- If fewer than M nodes remain, stop (nothing to delete).
- If fewer than N nodes are available to delete, delete all of them.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10
M = 2, N = 3
Output : 1 -> 2 -> 6 -> 7

Explanation:
Keep 1,2 → delete 3,4,5
Keep 6,7 → delete 8,9,10

Input:
1 -> 2 -> 3 -> 4 -> 5
M = 1, N = 1
Output:
1 -> 3 -> 5


-----------------------------------
Approach (Expected / Optimal – Iterative Pointer Traversal):
-----------------------------------
1. Use a pointer `curr` starting from head.
2. While `curr` is not NULL:
   a) Skip M-1 nodes (keep M nodes total).
      - If list ends, stop.
   b) From `curr->next`, delete next N nodes:
      - Move a temporary pointer N steps forward.
   c) Connect current node to the node after deleted segment.
   d) Move `curr` to the next node after deletions.
3. Return head.

Why this works:
- Each node is visited at most once.
- Only pointer adjustments are used.
- No extra data structures needed.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/delete-n-nodes-after-m-nodes-of-a-linked-list/

LeetCode:
No direct equivalent problem.
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


class Solution {
public:
    Node* deleteNodes(Node* head, int M, int N) {

        if (head == NULL || M == 0) {
            return NULL;
        }

        Node* curr = head;

        while (curr != NULL) {

            // Step 1: Skip M-1 nodes (keep M nodes)
            for (int i = 1; i < M && curr != NULL; i++) {
                curr = curr->next;
            }

            if (curr == NULL) {
                break;
            }

            // Step 2: Delete next N nodes
            Node* temp = curr->next;
            for (int i = 0; i < N && temp != NULL; i++) {
                temp = temp->next;
            }

            // Step 3: Link remaining list
            curr->next = temp;

            // Step 4: Move curr forward
            curr = temp;
        }

        return head;
    }
};
