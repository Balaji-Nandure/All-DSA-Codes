/*
Problem:
Sublist Search (Search a Linked List in Another Linked List)

Given two singly linked lists:
- First list (L1) → the main list
- Second list (L2) → the sublist

Determine whether L2 is present in L1 as a CONTIGUOUS sublist.
Return true if L2 is a sublist of L1, otherwise return false.

Important:
- Matching must be continuous (like substring).
- Node values are compared (not node addresses).
- Order must be preserved.

Examples:
Input:
L1: 1 -> 2 -> 3 -> 4 -> 5
L2: 2 -> 3 -> 4
Output: true

Input:
L1: 1 -> 2 -> 3 -> 4 -> 5
L2: 3 -> 5
Output: false

Input:
L1: 1 -> 2 -> 3
L2: 1 -> 2 -> 3
Output: true

Input:
L1: 1 -> 2 -> 3
L2: NULL
Output: true   (empty list is always a sublist)


-----------------------------------
Approach (Expected / Optimal – Brute Force Matching):
-----------------------------------
1. If L2 is NULL, return true.
2. Traverse L1 node by node.
3. For each node in L1, try to match L2 starting from that node:
   - Move forward in both lists as long as data matches.
4. If L2 reaches NULL → complete match found.
5. If mismatch occurs, move to next node of L1 and retry.
6. If L1 ends without match, return false.

Why this works:
- Linked lists do not support random access.
- This is analogous to substring search in strings.
- Simple and reliable solution.

Time Complexity:
O(n * m)
where:
n = length of L1  
m = length of L2

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/sublist-search-search-a-linked-list-in-another-list/

LeetCode:
No direct equivalent problem.
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


bool isSubList(Node* head1, Node* head2) {

    // Edge case: empty sublist
    if (head2 == NULL) {
        return true;
    }

    // Traverse main list
    for (Node* curr = head1; curr != NULL; curr = curr->next) {

        Node* p1 = curr;
        Node* p2 = head2;

        // Try to match sublist starting here
        while (p1 != NULL && p2 != NULL && p1->data == p2->data) {
            p1 = p1->next;
            p2 = p2->next;
        }

        // If reached end of sublist, match found
        if (p2 == NULL) {
            return true;
        }
    }

    return false;
}
