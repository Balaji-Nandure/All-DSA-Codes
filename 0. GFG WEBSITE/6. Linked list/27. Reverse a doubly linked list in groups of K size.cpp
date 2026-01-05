/*
Problem:
Reverse a Doubly Linked List in Groups of Size K

Given the head of a doubly linked list and an integer K,
reverse the list in groups of size K and return the new head.

Rules:
- Reverse nodes in groups of exactly K.
- If remaining nodes are fewer than K, they should ALSO be reversed
  (this is the standard GfG interpretation unless stated otherwise).
- Do NOT create new nodes.
- Properly update BOTH next and prev pointers.

Examples:
Input  : 1 <-> 2 <-> 3 <-> 4 <-> 5 <-> 6, K = 2
Output : 2 <-> 1 <-> 4 <-> 3 <-> 6 <-> 5

Input  : 1 <-> 2 <-> 3 <-> 4 <-> 5, K = 3
Output : 3 <-> 2 <-> 1 <-> 5 <-> 4


-----------------------------------
Approach (Expected / Optimal – Recursive Group Reversal):
-----------------------------------
1. Reverse the first K nodes using pointer manipulation.
2. While reversing:
   - Swap next and prev pointers carefully.
3. After reversing K nodes:
   - Recursively reverse the remaining list.
4. Attach the last node of the reversed group
   to the head of the next reversed group.
5. Return new head of the current group.

Why this works:
- Similar to singly linked list k-group reversal.
- Extra care for prev pointers.
- Clean recursive structure.

Time Complexity:
O(n)

Space Complexity:
O(n / k)   (recursion stack)


GeeksforGeeks:
https://www.geeksforgeeks.org/reverse-a-doubly-linked-list-in-groups-of-given-size/

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


Node* reverseKGroupDLL(Node* head, int k) {

    if (head == NULL || k <= 1) {
        return head;
    }

    // Check if there are at least k nodes
    Node* temp = head;
    for (int i = 0; i < k; i++) {
        if (temp == NULL)
            return head;
        temp = temp->next;
    }

    Node* curr = head;
    Node* prev = NULL;
    Node* next = NULL;
    int count = 0;

    // Reverse first k nodes (swap next and prev)
    while (curr != NULL && count < k) {
        next = curr->next;
        // Swap next and prev
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
        count++;
    }

    // Recursively reverse remaining list and adjust pointers
    if (next != NULL) {
        head->next = reverseKGroupDLL(next, k);
        if (head->next != NULL) {
            head->next->prev = head;
        }
    }

    return prev;
}

