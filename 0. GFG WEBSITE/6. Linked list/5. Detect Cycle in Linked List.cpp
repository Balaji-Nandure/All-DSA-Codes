/*
Problem:
Detect Cycle in a Linked List

Given the head of a singly linked list,
check whether the linked list contains a cycle (loop).

A cycle exists if some node in the list can be reached again
by continuously following the next pointer.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5 -> (points back to 2)
Output : true

Input  : 1 -> 2 -> 3 -> 4 -> NULL
Output : false

Input  : NULL
Output : false


-----------------------------------
Approach (Expected / Optimal – Floyd’s Cycle Detection Algorithm):
-----------------------------------
Also known as the "Tortoise and Hare" algorithm.

1. Use two pointers:
   - slow → moves one step at a time
   - fast → moves two steps at a time
2. Start both pointers at the head.
3. Traverse the list:
   - slow = slow->next
   - fast = fast->next->next
4. If at any point slow == fast:
   - A cycle exists → return true
5. If fast or fast->next becomes NULL:
   - No cycle → return false

Why this works:
- In a cyclic list, the fast pointer eventually laps
  the slow pointer.
- In an acyclic list, fast reaches NULL first.
- No extra memory is used.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/

LeetCode:
https://leetcode.com/problems/linked-list-cycle/
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


bool detectCycle(Node* head) {

    // Empty list or single node cannot form a cycle
    if (head == NULL || head->next == NULL) {
        return false;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {

        slow = slow->next;           // move by 1
        fast = fast->next->next;     // move by 2

        // Cycle detected
        if (slow == fast) {
            return true;
        }
    }

    // No cycle
    return false;
}
