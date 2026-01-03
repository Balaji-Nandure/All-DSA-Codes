/*
Problem:
Remove Every K-th Node of a Linked List

Given the head of a singly linked list and an integer k,
remove every k-th node from the linked list and return
the head of the modified list.

Rules:
- Positions are 1-based.
- If k == 1, remove all nodes → result is NULL.
- The order of remaining nodes must be preserved.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5 -> 6, k = 2
Output : 1 -> 3 -> 5

Input  : 1 -> 2 -> 3 -> 4 -> 5, k = 3
Output : 1 -> 2 -> 4 -> 5

Input  : 1 -> 2 -> 3, k = 1
Output : NULL


-----------------------------------
Approach (Expected / Optimal – Single Traversal):
-----------------------------------
1. If head is NULL, return NULL.
2. If k == 1, all nodes are removed → return NULL.
3. Traverse the list while maintaining:
   - a counter to track node positions.
4. For each node:
   - If counter == k:
       • unlink the current node from the list
       • reset counter to 1
     Else:
       • move to next node and increment counter
5. Continue until end of list.

Why this works:
- We remove nodes exactly at multiples of k.
- One pass ensures O(n) time.
- Pointer manipulation avoids extra memory.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/remove-every-k-th-node-linked-list/

LeetCode:
No direct equivalent problem.
(Related to linked list traversal and deletion)
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


Node* deleteK(Node* head, int k) {

    // Edge case: empty list
    if (head == NULL) {
        return NULL;
    }

    // If k == 1, remove all nodes
    if (k == 1) {
        return NULL;
    }

    Node* curr = head;
    Node* prev = NULL;
    int count = 1;

    while (curr != NULL) {

        // If current node is k-th
        if (count == k) {
            prev->next = curr->next;
            curr = curr->next;
            count = 1;   // reset counter
        } 
        else {
            prev = curr;
            curr = curr->next;
            count++;
        }
    }

    return head;
}
