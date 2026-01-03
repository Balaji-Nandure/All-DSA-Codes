/*
Problem:
Delete a Node in a Doubly Linked List (Using Dummy Node)

Given the head of a doubly linked list and an integer x,
delete the node at position x (1-based indexing) and
return the head of the modified list.

Why Dummy Node?
- Simplifies edge cases (especially deletion of head).
- Makes pointer handling uniform.
- Avoids writing separate logic for x == 1.

Examples:
Input  : 1 <-> 2 <-> 3 <-> 4, x = 3
Output : 1 <-> 2 <-> 4

Input  : 10 <-> 20 <-> 30, x = 1
Output : 20 <-> 30

Input  : 5, x = 1
Output : NULL


-----------------------------------
Approach (Expected / Optimal – Dummy Node Technique):
-----------------------------------
1. Create a dummy node:
   - dummy->next = head
   - dummy acts as the previous node of head
2. Traverse from dummy to reach the (x+1)-th node.
3. Delete the x-th node by relinking pointers.
4. Update head from dummy->next.
5. Return updated head.

Why this works:
- Deleting head becomes identical to deleting any other node.
- Cleaner and safer pointer manipulation.
- Single traversal ensures optimal performance.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/delete-node-doubly-linked-list/

LeetCode:
No direct equivalent problem.
*/


// Definition for Doubly Linked List Node
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int x) {
        data = x;
        next = NULL;
        prev = NULL;
    }
};


Node* deleteNode(Node* head, int x) {

    // Case: Empty list
    if (head == NULL) {
        return NULL;
    }

    // Step 1: Create dummy node
    Node* dummy = new Node(-1);
    dummy->next = head;
    head->prev = dummy;

    Node* curr = dummy;
    int count = 0;

    // Step 2: Move to node just before position x
    while (curr->next != NULL && count < x - 1) {
        curr = curr->next;
        count++;
    }

    // Step 3: Delete x-th node if exists
    if (curr->next != NULL) {
        Node* del = curr->next;
        curr->next = del->next;

        if (del->next != NULL) {
            del->next->prev = curr;
        }
        // delete del;  // optional based on platform
    }

    // Step 4: Update head and clean dummy
    head = dummy->next;
    if (head != NULL) {
        head->prev = NULL;
    }

    // delete dummy;  // optional

    return head;
}
