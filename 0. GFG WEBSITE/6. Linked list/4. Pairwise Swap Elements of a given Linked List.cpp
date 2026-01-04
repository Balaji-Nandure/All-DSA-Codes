/*
Problem:
Pairwise Swap Elements of a Linked List

Given the head of a singly linked list,
swap elements of the linked list pairwise.
Only links should be swapped (do NOT swap data).

Rules:
- If the list has odd number of nodes, the last node remains as is.
- Return the head of the modified list.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> NULL
Output : 2 -> 1 -> 4 -> 3 -> NULL

Input  : 1 -> 2 -> 3 -> NULL
Output : 2 -> 1 -> 3 -> NULL

Input  : 1 -> NULL
Output : 1 -> NULL


-----------------------------------
Approach (Expected / Optimal – Iterative with Dummy Node):
-----------------------------------
1. Use a dummy node before head to simplify swapping.
2. Maintain a pointer prev pointing to the node before the current pair.
3. For each pair (first, second):
   - prev->next = second
   - first->next = second->next
   - second->next = first
4. Move prev to first (end of swapped pair).
5. Continue until fewer than two nodes remain.

Why this works:
- Dummy node handles head swap cleanly.
- Each node is visited once.
- Only pointers are modified (no data swap).

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/pairwise-swap-elements-of-a-given-linked-list/

LeetCode:
https://leetcode.com/problems/swap-nodes-in-pairs/
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


Node* pairwiseSwap(Node* head) {

    // If list is empty or has only one node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // Dummy node
    Node* dummy = new Node(-1);
    dummy->next = head;

    Node* prev = dummy;

    while (prev->next != NULL && prev->next->next != NULL) {

        Node* first  = prev->next;
        Node* second = first->next;

        // Swapping links
        prev->next = second;
        first->next = second->next;
        second->next = first;

        // Move prev to end of swapped pair
        prev = first;
    }

    head = dummy->next;
    return head;
}
