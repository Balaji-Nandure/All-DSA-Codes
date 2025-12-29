/*
GeeksforGeeks:
https://practice.geeksforgeeks.org/problems/merge-two-sorted-linked-lists/1

LeetCode:
https://leetcode.com/problems/merge-two-sorted-lists/
*/


// Approach 1: merge iterative
Node* merge2(Node* l1, Node* l2) {
    /*
    Approach (Iterative):
    1. Use a dummy node to simplify handling of head.
    2. Maintain a tail pointer that always points to last node of merged list.
    3. Compare l1 and l2:
       - Attach smaller node to tail.
       - Move the chosen list forward.
    4. Attach remaining nodes once one list is exhausted.

    Time: O(n + m)
    Space: O(1)
    */

    Node dummy(0);
    Node* tail = &dummy;

    while (l1 && l2) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach remaining nodes
    if (l1) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;
}



// Approach 2: merge recursive
Node* merge(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data <= l2->data) {
        l1->next = merge(l1->next, l2);
        return l1;
    } else {
        l2->next = merge(l1, l2->next);
        return l2;
    }
}