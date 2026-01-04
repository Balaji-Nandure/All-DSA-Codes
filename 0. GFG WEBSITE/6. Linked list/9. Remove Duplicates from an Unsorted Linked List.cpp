/*
Problem:
Remove Duplicates from an Unsorted Linked List

Given the head of a singly linked list which is NOT sorted,
remove all duplicate nodes so that each value appears only once.
Preserve the order of first occurrence of elements.

Examples:
Input  : 1 -> 3 -> 2 -> 3 -> 1 -> 4 -> NULL
Output : 1 -> 3 -> 2 -> 4 -> NULL

Input  : 5 -> 5 -> 5 -> 5 -> NULL
Output : 5 -> NULL

Input  : 1 -> 2 -> 3 -> NULL
Output : 1 -> 2 -> 3 -> NULL


-----------------------------------
Approach (Expected / Optimal – Hashing):
-----------------------------------
1. Use an unordered_set to keep track of values already seen.
2. Traverse the linked list using two pointers:
   - curr → current node
   - prev → previous node
3. For each node:
   - If curr->data is already present in the set:
       • Remove curr by linking prev->next to curr->next
   - Else:
       • Insert curr->data into the set
       • Move prev to curr
4. Continue till the end of the list.

Why this works:
- Hash set allows O(1) average-time lookup.
- First occurrence is kept; later duplicates are removed.
- Order of unique elements is preserved.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/

LeetCode:
https://leetcode.com/problems/remove-duplicates-from-unsorted-list/
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

    unordered_set<int> seen;

    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL) {

        // If duplicate found
        if (seen.find(curr->data) != seen.end()) {
            prev->next = curr->next;
        }
        else {
            seen.insert(curr->data);
            prev = curr;
        }

        curr = curr->next;
    }

    return head;
}
