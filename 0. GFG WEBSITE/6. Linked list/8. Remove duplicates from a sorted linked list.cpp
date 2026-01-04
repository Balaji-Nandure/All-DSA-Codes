/*
Problem:
Remove Duplicates from a Sorted Linked List

Given the head of a singly linked list sorted in non-decreasing order,
remove all duplicate nodes such that each element appears only once.
Return the head of the modified linked list.

Important:
- The linked list is already SORTED.
- Only pointers should be adjusted.
- No extra data structures are required.

Examples:
Input  : 1 -> 1 -> 2 -> 2 -> 3 -> 3 -> NULL
Output : 1 -> 2 -> 3 -> NULL

Input  : 1 -> 1 -> 1 -> 1 -> NULL
Output : 1 -> NULL

Input  : 1 -> 2 -> 3 -> NULL
Output : 1 -> 2 -> 3 -> NULL


-----------------------------------
Approach (Expected / Optimal – Single Traversal):
-----------------------------------
1. Start from the head node.
2. Traverse the list while current and current->next exist.
3. If current->data == current->next->data:
   - Skip the next node by adjusting the link.
4. Else:
   - Move current forward.
5. Continue till the end.

Why this works:
- Since the list is sorted, duplicates always appear consecutively.
- One comparison per node is sufficient.
- No extra space needed.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/remove-duplicates-from-a-sorted-linked-list/

LeetCode:
https://leetcode.com/problems/remove-duplicates-from-sorted-list/
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


Node* removeDuplicates(Node* head) {

    // Empty list or single node
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* curr = head;

    while (curr != NULL && curr->next != NULL) {

        // If duplicate found, skip next node
        if (curr->data == curr->next->data) {
            curr->next = curr->next->next;
        }
        else {
            curr = curr->next;
        }
    }

    return head;
}
