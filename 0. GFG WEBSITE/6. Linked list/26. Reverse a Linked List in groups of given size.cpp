/*
Problem:
Reverse a Linked List in Groups of Given Size (k)

Given the head of a singly linked list and an integer k,
reverse the linked list in groups of size k and
return the modified list.

Rules:
- Reverse the FIRST k nodes, then the next k nodes, and so on.
- If the number of remaining nodes is less than k,
  they should remain as they are (as per GfG standard).
- Do NOT create new nodes; only change links.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8,  k = 3
Output : 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 7 -> 8

Input  : 1 -> 2 -> 3 -> 4 -> 5,  k = 2
Output : 2 -> 1 -> 4 -> 3 -> 5

Input  : 1 -> 2 -> 3 -> 4,  k = 5
Output : 1 -> 2 -> 3 -> 4


-----------------------------------
Approach (Expected / Optimal – Recursive Group Reversal):
-----------------------------------
1. Reverse the first k nodes using standard pointer reversal.
2. Keep track of:
   - next pointer after k nodes
   - newHead of the reversed group
3. Recursively call for the remaining list.
4. Connect the last node of the reversed group
   to the head returned by recursion.

Why this works:
- Each group is reversed independently.
- Links are stitched correctly between groups.
- Clean and intuitive recursion.

Time Complexity:
O(n)

Space Complexity:
O(n / k)   (recursive stack)


GeeksforGeeks:
https://www.geeksforgeeks.org/reverse-a-linked-list-in-groups-of-given-size/

LeetCode:
https://leetcode.com/problems/reverse-nodes-in-k-group/
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


Node* reverseKGroup(Node* head, int k) {

    if (head == NULL || k <= 1) {
        return head;
    }

    //Check if there are at least k nodes
    Node* temp = head;
    for (int i = 0; i < k; i++) {
        if (temp == NULL)
            return head;   // Less than k nodes → no reversal
        temp = temp->next;
    }

    Node* curr = head;
    Node* prev = NULL;
    Node* next = NULL;

    int count = 0;

    // Reverse first k nodes
    while (curr != NULL && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }

    // Now:
    // prev → new head of reversed group
    // head → last node of reversed group

    // Recurse for remaining list
    if (next != NULL) {
        head->next = reverseKGroup(next, k);
    }

    return prev;
}
