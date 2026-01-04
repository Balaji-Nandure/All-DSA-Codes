/*
Problem:
Merge Two Sorted Linked Lists

Given heads of two singly linked lists head1 and head2,
both sorted in increasing order,
merge them into a single sorted linked list
and return the head of the merged list.

Important:
- The merged list should be formed by reusing existing nodes.
- No new nodes should be created.
- Order must remain sorted.

Examples:
Input:
List1: 1 -> 3 -> 5
List2: 2 -> 4 -> 6
Output:
1 -> 2 -> 3 -> 4 -> 5 -> 6

Input:
List1: 1 -> 2 -> 4
List2: 1 -> 3 -> 4
Output:
1 -> 1 -> 2 -> 3 -> 4 -> 4


-----------------------------------
Approach (Expected / Optimal – Two Pointer Technique):
-----------------------------------
1. Use a dummy node to simplify head handling.
2. Maintain a tail pointer for the merged list.
3. Compare current nodes of both lists:
   - Attach the smaller node to the merged list.
   - Move the corresponding pointer forward.
4. When one list ends:
   - Attach the remaining nodes of the other list.
5. Return dummy->next as the merged list head.

Why this works:
- Both lists are already sorted.
- Each node is visited exactly once.
- Dummy node avoids special-case handling for head.

Time Complexity:
O(n + m)

Space Complexity:
O(1)   (no extra space, nodes are reused)


GeeksforGeeks:
https://www.geeksforgeeks.org/merge-two-sorted-linked-lists/

LeetCode:
https://leetcode.com/problems/merge-two-sorted-lists/
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


Node* mergeSortedLists(Node* head1, Node* head2) {

    // Dummy node
    Node dummy(-1);
    Node* tail = &dummy;

    Node* p1 = head1;
    Node* p2 = head2;

    // Merge while both lists have nodes
    while (p1 != NULL && p2 != NULL) {

        if (p1->data <= p2->data) {
            tail->next = p1;
            p1 = p1->next;
            tail = tail->next;
        }
        else {
            tail->next = p2;
            p2 = p2->next;
            tail = tail->next;
        }

    }

    // Attach remaining nodes
    if (p1 != NULL) {
        tail->next = p1;
    }
    else {
        tail->next = p2;
    }

    return dummy.next;
}
