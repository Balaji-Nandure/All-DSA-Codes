/*
Problem:
Rotate a Linked List

Given the head of a singly linked list and an integer k,
rotate the linked list counter-clockwise by k nodes and
return the new head.

Definition (Counter-clockwise rotation):
- Move the first k nodes to the end of the list.

Important:
- Rotation is based on node links, not values.
- If k is 0 or a multiple of list length, the list remains unchanged.

Examples:
Input  : 10 -> 20 -> 30 -> 40 -> 50, k = 2
Output : 30 -> 40 -> 50 -> 10 -> 20

Input  : 1 -> 2 -> 3 -> 4 -> 5, k = 4
Output : 5 -> 1 -> 2 -> 3 -> 4

Input  : 1 -> 2 -> 3, k = 0
Output : 1 -> 2 -> 3


-----------------------------------
Approach (Expected / Optimal – Length + Pointer Re-linking):
-----------------------------------
1. If head is NULL, has one node, or k == 0 → return head.
2. Traverse the list to:
   - Find the length of the list.
   - Get the last node (tail).
3. Reduce k using:
      k = k % length
   (rotating by length brings list to same state)
4. Traverse the list to the k-th node.
5. Break the list after k-th node.
6. Link tail->next to original head.
7. New head = (k+1)-th node.

Why this works:
- Rotation is just cutting and reconnecting the list.
- Only one extra traversal is needed.
- Pointer manipulation keeps space O(1).

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/rotate-a-linked-list/

LeetCode:
https://leetcode.com/problems/rotate-list/
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


Node* rotate(Node* head, int k) {

    // Edge cases
    if (head == NULL || head->next == NULL || k == 0) {
        return head;
    }

    // Step 1: Find length and tail
    Node* tail = head;
    int length = 1;

    while (tail->next != NULL) {
        tail = tail->next;
        length++;
    }

    // Step 2: Optimize k
    k = k % length;
    if (k == 0) {
        return head;
    }

    // Step 3: Find k-th node
    Node* curr = head;
    for (int i = 1; i < k; i++) {
        curr = curr->next;
    }

    // Step 4: Re-link
    Node* newHead = curr->next;
    curr->next = NULL;
    tail->next = head;

    return newHead;
}
