/*
Problem:
Insert a Value in Sorted Order in a Sorted Doubly Linked List
(using Dummy Node with INT_MIN)

Given the head of a sorted doubly linked list (ascending order)
and an integer x, insert x so that the list remains sorted.
Return the updated head.

Why Dummy Node?
- Eliminates special cases (insertion at head).
- Uniform pointer handling.
- Cleaner and safer logic.

Rules:
- Create a new node for x.
- Correctly update both next and prev pointers.
- Do NOT change existing node values.

Examples:
Input  : 1 <-> 3 <-> 5 <-> 7,  x = 4
Output : 1 <-> 3 <-> 4 <-> 5 <-> 7

Input  : 2 <-> 4 <-> 6,  x = 1
Output : 1 <-> 2 <-> 4 <-> 6

Input  : 1 <-> 2 <-> 3,  x = 10
Output : 1 <-> 2 <-> 3 <-> 10


-----------------------------------
Approach (Expected / Optimal – Dummy Node Technique):
-----------------------------------
1. Create a dummy node with value = INT_MIN.
2. Link dummy->next to head.
3. Traverse from dummy to find the insertion position.
4. Insert the new node.
5. Detach dummy and return the real head.

Why this works:
- Head insertion becomes identical to middle insertion.
- No branching for head case.
- One-pass traversal.

Time Complexity:
O(n)

Space Complexity:
O(1)   (excluding the new node)


GeeksforGeeks:
https://www.geeksforgeeks.org/insert-value-sorted-way-sorted-doubly-linked-list/

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


Node* sortedInsert(Node* head, int x) {

    // Step 1: Create dummy node with minimum value
    Node* dummy = new Node(INT_MIN);
    dummy->next = head;

    if (head != NULL) {
        head->prev = dummy;
    }

    Node* curr = dummy;

    // Step 2: Find correct position
    while (curr->next != NULL && curr->next->data < x) {
        curr = curr->next;
    }

    // Step 3: Insert new node
    Node* newNode = new Node(x);
    newNode->next = curr->next;
    newNode->prev = curr;

    if (curr->next != NULL) {
        curr->next->prev = newNode;
    }

    curr->next = newNode;

    // Step 4: Detach dummy and fix head
    head = dummy->next;
    head->prev = NULL;

    // delete dummy; // optional (platform dependent)

    return head;
}
