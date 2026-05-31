/*
GeeksforGeeks: Delete Middle of Linked List
Difficulty: Easy

Problem:
Given a singly linked list, delete the middle of the linked list.
Note:
- If there are even nodes, then there would be two middle nodes, we need to delete the second middle element.
- If the input linked list has a single node, then it should return NULL.

Example 1:
Input: LinkedList: 1->2->3->4->5
Output: 1->2->4->5
Explanation: The middle node is 3.

Example 2:
Input: LinkedList: 2->4->6->7->5->1
Output: 2->4->6->5->1
Explanation: There are 6 nodes. The two middle nodes are 6 and 7. We delete the second middle node, which is 7.

Example 3:
Input: LinkedList: 7 
Output: <empty linked list>
Explanation: There was only one node and it was deleted.

Core Idea:
We can find the middle node using the Tortoise and Hare (slow and fast pointer) approach. 
The fast pointer moves two steps at a time while the slow pointer moves one step. When the fast pointer reaches the end, the slow pointer will be at the middle.
Since we need to delete the middle node, we need to keep track of the node immediately preceding the middle node (`prev`).
Once the middle node is found, we bypass it by linking `prev->next` to `slow->next`, and then delete `slow`.

Approach:
1. Handle base cases: If the list is empty (`head == NULL`) or has only one node (`head->next == NULL`), return `NULL` (after deleting the head if it exists).
2. Initialize three pointers: `slow = head`, `fast = head`, and `prev = NULL`.
3. Loop while `fast != NULL` and `fast->next != NULL`:
   - `prev = slow`
   - `slow = slow->next`
   - `fast = fast->next->next`
4. After the loop terminates, `slow` points to the middle node, and `prev` points to the node just before it.
5. Set `prev->next = slow->next` to detach the middle node.
6. Delete the `slow` node.
7. Return the `head` of the list.

Time Complexity: O(N) where N is the number of nodes. We traverse the linked list half-way to find the middle.
Space Complexity: O(1) as only a few pointers are used.

GFG Link:
https://www.geeksforgeeks.org/problems/delete-middle-of-linked-list/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    struct Node* next;
    
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    Node* deleteMid(Node* head) {
        // Base Case 1: Empty list
        if (head == NULL) {
            return NULL;
        }
        
        // Base Case 2: List with only one node
        if (head->next == NULL) {
            delete head;
            return NULL;
        }

        Node* slow = head;
        Node* fast = head;
        Node* prev = NULL;

        // Find the middle node and the node just before it
        while (fast != NULL && fast->next != NULL) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // prev points to the node before the middle node
        // slow points to the middle node
        // Bypass the middle node
        prev->next = slow->next;

        // Free the memory
        delete slow;

        return head;
    }
};

/*
Dry Run — Example 1:
Input: LinkedList: 1->2->3->4->5

Initial State:
slow = 1, fast = 1, prev = NULL

Iteration 1:
fast (1) != NULL and fast->next (2) != NULL
prev = slow (1)
slow = slow->next (2)
fast = fast->next->next (3)

Iteration 2:
fast (3) != NULL and fast->next (4) != NULL
prev = slow (2)
slow = slow->next (3)
fast = fast->next->next (5)

Iteration 3:
fast (5) != NULL, but fast->next is NULL.
Loop terminates.

Current pointers:
prev points to 2
slow points to 3 (the middle node)

Deletion step:
prev->next = slow->next  =>  node 2's next now points to node 4
delete slow              =>  node 3 is deleted

Final Output: 1->2->4->5
Return: head
*/
