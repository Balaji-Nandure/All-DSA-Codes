/*
Problem:
Length of Cycle in a Linked List

Given the head of a singly linked list,
find the length of the cycle (loop) present in the list.
If there is no cycle, return 0.

Examples:
Input  : 1 -> 2 -> 3 -> 4 -> 5
               ^              |
               |--------------|
Output : 3

Input  : 1 -> 2 -> 3 -> NULL
Output : 0


-----------------------------------
Approach (Expected / Optimal – Floyd’s Cycle Detection + Counting):
-----------------------------------
1. Use Floyd’s Cycle Detection Algorithm (slow & fast pointers).
2. If slow and fast pointers meet:
   - A cycle exists.
3. To find the cycle length:
   - Keep one pointer fixed.
   - Move the other pointer until it comes back to the same node,
     counting the number of steps.
4. Return the counted length.
5. If no cycle is detected, return 0.

Why this works:
- Floyd’s algorithm guarantees a meeting point inside the cycle.
- Traversing once around the loop gives exact cycle length.
- No extra data structures needed.

Time Complexity:
O(n)

Space Complexity:
O(1)


GeeksforGeeks:
https://www.geeksforgeeks.org/find-length-of-loop-in-linked-list/

LeetCode:
No direct equivalent problem.
(Related to cycle detection problems)
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


int lengthOfCycle(Node* head) {

    if (head == NULL || head->next == NULL) {
        return 0;
    }

    Node* slow = head;
    Node* fast = head;

    // Step 1: Detect cycle
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        // Cycle detected
        if (slow == fast) {

            // Step 2: Count cycle length
            int count = 1;
            Node* temp = slow->next;

            while (temp != slow) {
                count++;
                temp = temp->next;
            }

            return count;
        }
    }

    // No cycle
    return 0;
}
