/*
Problem:
Exchange First and Last Nodes in a Circular Linked List

Given the head of a Circular Linked List,
swap (exchange) the first and last nodes and
return the head of the modified list.

Rules:
- Circular linked list means last node points back to head.
- Only links should be changed (do NOT swap data).
- Head may change after swapping.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> (back to 1)
Output : 4 -> 2 -> 3 -> 1 -> (back to 4)

Input  : 10 -> 20 -> (back to 10)
Output : 20 -> 10 -> (back to 20)

Input  : 5 -> (back to 5)
Output : 5


-----------------------------------
Approach (Expected / Optimal – Pointer Manipulation):
-----------------------------------
1. Handle edge cases:
   - If list is empty or has only one node → no change.
2. Traverse to find:
   - last node
   - node just before last (prevLast)
3. Adjust pointers:
   - last->next = head->next
   - prevLast->next = head
   - head->next = last
4. Update head to last node.

Why this works:
- Circular structure is preserved.
- Only links are modified.
- One traversal ensures optimal time.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/exchange-first-last-nodes-circular-linked-list/

LeetCode:
No direct equivalent problem.
(Related to circular linked list manipulation)
*/


struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};


Node* exchangeNodes(Node* head) {

    // Edge cases: empty list or single node
    if (head == NULL || head->next == head) {
        return head;
    }

    Node* prevLast = NULL;
    Node* last = head;

    // Traverse to find last and second-last node
    while (last->next != head) {
        prevLast = last;
        last = last->next;
    }

    // Handle case with exactly two nodes
    if (head->next == last) {
        last->next = head;
        head->next = last;
        return last;
    }

    // General case
    prevLast->next = head;
    last->next = head->next;
    head->next = last;

    // Update head
    head = last;

    return head;
}
