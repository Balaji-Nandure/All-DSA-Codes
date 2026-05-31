/*
GeeksforGeeks: Move Last to Front of a Linked List
Difficulty: Easy

Problem:
You are given the head of a Linked List. You have to move the last element to the front of the Linked List and return the head the modified linked list.

Example 1:
Input: head: 2->5->6->2->1
Output: 1->2->5->6->2
Explanation: In the given linked list, the last element is 1, after moving the last element to the front the linked list will be 1->2->5->6->2.

Example 2:
Input: head: 2
Output: 2
Explanation: Here 2 is the only element so, the linked list will remain the same.

Core Idea:
To move the last node to the front, we need to access both the last node and the second-to-last node.
Once we reach the end, we simply detach the last node from the second-to-last node (by setting its `next` to NULL), 
make the last node point to the current `head`, and finally return the last node as the new `head`.

Approach:
1. Handle base cases: If the linked list is empty (`head == NULL`) or contains only one node (`head->next == NULL`), returning `head` directly since no changes are needed.
2. Initialize two pointers: `prev = NULL` and `curr = head`.
3. Traverse the linked list until `curr->next == NULL`. During traversal, keep updating `prev = curr` before moving `curr` to the next node.
4. After the loop, `curr` points to the last node and `prev` points to the second-to-last node.
5. Unlink the last node from the rest of the list: `prev->next = NULL`.
6. Make the last node point to the old head: `curr->next = head`.
7. Return `curr` as the new head of the linked list.

Time Complexity: O(N) where N is the number of nodes. We traverse the linked list exactly once.
Space Complexity: O(1) since we only use a couple of pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/move-last-element-to-front-of-a-linked-list/1
*/

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int x) {
        data = x;
        next = NULL;
    }
};

class Solution {
public:
    Node* moveToFront(Node* head) {
        // Base case: empty list or single node
        if (head == NULL || head->next == NULL) {
            return head;
        }
        
        // Pointers to find the last and second last nodes
        Node* prev = NULL;
        Node* curr = head;
        
        while (curr->next != NULL) {
            prev = curr;
            curr = curr->next;
        }
        
        // Unlink the last node
        prev->next = NULL;
        
        // Move the last node to the front
        curr->next = head;
        
        // Return the new head
        return curr;
    }
};

/*
Dry Run — Example 1:
Input: head: 2->5->6->2->1

Initial state:
head -> [2] -> [5] -> [6] -> [2] -> [1] -> NULL
prev = NULL
curr = head (points to 2)

Step 1:
curr->next is not NULL (points to 5)
prev = curr (prev points to 2)
curr = curr->next (curr points to 5)

Step 2:
curr->next is not NULL (points to 6)
prev = curr (prev points to 5)
curr = curr->next (curr points to 6)

Step 3:
curr->next is not NULL (points to 2)
prev = curr (prev points to 6)
curr = curr->next (curr points to 2)

Step 4:
curr->next is not NULL (points to 1)
prev = curr (prev points to 2)
curr = curr->next (curr points to 1)

Step 5:
curr->next is NULL. Loop terminates.
Currently:
prev points to second-last node [2]
curr points to last node [1]

Step 6 (Unlink and move):
prev->next = NULL (list becomes 2->5->6->2->NULL)
curr->next = head (1->next = 2)

Return `curr` (which is 1).

Final Output Linked List:
1 -> 2 -> 5 -> 6 -> 2 -> NULL
*/
