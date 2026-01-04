/*
Problem:
Split a Circular Linked List into Two Halves

Given the head of a circular singly linked list,
split it into two halves:
- The first half should contain the first ⌈n/2⌉ nodes
- The second half should contain the remaining ⌊n/2⌋ nodes

Both halves must also be circular linked lists.

Rules:
- If the number of nodes is odd, the first list gets one extra node.
- Do NOT create new nodes; only adjust links.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5 -> (back to 1)
Output :
First half : 1 -> 2 -> 3 -> (back to 1)
Second half: 4 -> 5 -> (back to 4)

Input  : 1 -> 2 -> 3 -> 4 -> (back to 1)
Output :
First half : 1 -> 2 -> (back to 1)
Second half: 3 -> 4 -> (back to 3)

-----------------------------------
Approach (Expected / Optimal – Slow & Fast Pointers):
-----------------------------------
1. Use slow and fast pointers starting from head.
2. Move:
   - slow by 1 step
   - fast by 2 steps
3. Stop when:
   - fast->next == head  (even number of nodes)
   - OR fast->next->next == head (odd number of nodes)
4. At this point:
   - slow is at the end of the first half.
5. Split:
   - head1 = head
   - head2 = slow->next
6. Make both halves circular:
   - slow->next = head1
   - fast->next = head2

Why this works:
- Fast pointer detects list midpoint.
- Ensures correct split for both even and odd lengths.
- Only one traversal needed.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/split-a-circular-linked-list-into-two-halves/

LeetCode:
No direct equivalent problem.
(Related to circular linked list manipulation)
*/


// Definition for circular linked list node
struct Node {
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
// function which splits the circular linked list. head is pointer
// to head Node of given linked list. 
// Returns pair of head pointers of resultant two halves.

class Solution {
  public:
    pair<Node *, Node *> splitList(struct Node *head) {
        if (!head) return {NULL, NULL};

        Node* slow = head;
        Node* fast = head;

        // Use slow and fast pointers to find the midpoint
        while (fast->next != head && fast->next->next != head) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // For odd number of nodes, move fast one more step  
        if (fast->next->next == head) {
            fast = fast->next;
        }

        // Setup the two new heads
        Node* head1 = head;
        Node* head2 = slow->next;

        // Make the two halves circular
        slow->next = head1;
        fast->next = head2;

        return {head1, head2};
    }
};
