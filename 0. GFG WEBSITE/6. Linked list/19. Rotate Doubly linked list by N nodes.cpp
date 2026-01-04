/*
Problem:
Rotate a Doubly Linked List by N Nodes

Given the head of a doubly linked list and an integer N,
rotate the list counter-clockwise by N nodes and
return the new head.

Definition (Counter-clockwise rotation):
- Move the first N nodes to the end of the list.

Important:
- Rotation must preserve node order.
- Update BOTH next and prev pointers correctly.
- If N is 0 or a multiple of list length, list remains unchanged.

Examples:
Input  : 1 <-> 2 <-> 3 <-> 4 <-> 5, N = 2
Output : 3 <-> 4 <-> 5 <-> 1 <-> 2

Input  : 10 <-> 20 <-> 30, N = 1
Output : 20 <-> 30 <-> 10

Input  : 1 <-> 2 <-> 3, N = 3
Output : 1 <-> 2 <-> 3


-----------------------------------
Approach (Expected / Optimal – Length + Pointer Re-linking):
-----------------------------------
1. Handle edge cases:
   - Empty list
   - Single node
   - N == 0
2. Traverse to:
   - Find total length of the list.
   - Reach the tail node.
3. Reduce N using:
      N = N % length
4. Traverse to the N-th node.
5. Break the list after N-th node.
6. Connect:
   - tail->next to original head
   - original head->prev to tail
7. New head is (N+1)-th node.
8. Set newHead->prev = NULL.

Why this works:
- Rotation is achieved by cutting and reconnecting the list.
- Only pointer changes are required.
- Works in linear time and constant space.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/rotate-doubly-linked-list-n-nodes/

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


Node* rotateDLL(Node* head, int N) {

    // Edge cases
    if (head == NULL || head->next == NULL || N == 0) {
        return head;
    }

    // Step 1: Find length and tail
    Node* tail = head;
    int length = 1;

    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    // Step 2: Optimize N
    N = N % length;
    if (N == 0) {
        return head;
    }

    // Step 3: Find N-th node
    Node* curr = head;
    for (int i = 1; i < N; i++) {
        curr = curr->next;
    }

    // Step 4: Re-link pointers
    Node* newHead = curr->next;

    curr->next = NULL;
    newHead->prev = NULL;

    tail->next = head;
    head->prev = tail;

    return newHead;
}
