/*
GeeksforGeeks: Move all zeros to the front of the linked list
Difficulty: Easy

Problem:
Given the head of a linked list, move all nodes with value 0 to the front while preserving the relative order of all non-zero nodes.

Example 1:
Input: head: 0 -> 4 -> 0 -> 5 -> 0
Output: 0 -> 0 -> 0 -> 4 -> 5
Explanation: After moving all 0s of the given list to the front, the list is: 0 -> 0 -> 0 -> 4 -> 5

Example 2:
Input: head: 0 -> 1 -> 0 -> 1 -> 2
Output: 0 -> 0 -> 1 -> 1 -> 2
Explanation: After moving all 0s of the given list to the front, the list is: 0 -> 0 -> 1 -> 1 -> 2

Core Idea:
We need to move every zero-valued node to the front of the list. We can traverse the list while maintaining a `prev` and `curr` pointer. 
Whenever we encounter a `curr` node with data 0 (and it's not already at the front), we remove it from its current position by linking `prev` to `curr->next`. 
Then, we insert `curr` at the beginning of the list, updating the `head`.
This ensures all non-zero nodes remain in their relative order, and all zeros end up at the front.

Approach:
1. If the list is empty or has only one node, return `head`.
2. Initialize two pointers: `prev` as NULL and `curr` as `head`.
3. Loop through the list while `curr != NULL`:
   a. If `curr->data == 0` and `prev != NULL`:
      - Disconnect `curr` from its position: `prev->next = curr->next`.
      - Move `curr` to the front: `curr->next = head`.
      - Update `head`: `head = curr`.
      - Advance `curr` to the next node in the original sequence: `curr = prev->next`.
   b. Else (if `curr->data != 0` or it's the very first node):
      - Update `prev`: `prev = curr`.
      - Advance `curr`: `curr = curr->next`.
4. Return the new `head`.

Time Complexity: O(N) where N is the number of nodes. We traverse the list exactly once.
Space Complexity: O(1) as we are only changing pointers in place.

GFG Link:
https://www.geeksforgeeks.org/problems/move-all-zeros-to-the-front-of-the-linked-list/1
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
    Node* moveZeroes(Node* head) {
        if (!head || !head->next) {
            return head;
        }

        Node* curr = head;
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->data == 0 && prev != NULL) {
                // Detach curr from the current position
                prev->next = curr->next;
                
                // Move curr to the front
                curr->next = head;
                head = curr;
                
                // Advance curr to the next node in the iteration
                curr = prev->next;
            } else {
                // Move forward normally
                prev = curr;
                curr = curr->next;
            }
        }
        
        return head;
    }
};

/*
Dry Run — Example 1:
Input: head: 0 -> 4 -> 0 -> 5 -> 0

Initial State:
head -> 0 -> 4 -> 0 -> 5 -> 0 -> NULL
prev = NULL
curr = 0 (1st node)

Iteration 1:
curr->data == 0, but prev is NULL.
We hit the else block:
prev = 0 (1st node)
curr = 4

Iteration 2:
curr->data == 4, prev != NULL.
else block:
prev = 4
curr = 0 (2nd node)

Iteration 3:
curr->data == 0, prev != NULL.
if block:
prev->next = curr->next (4 -> 5)
curr->next = head (0 -> 0(1st))
head = 0 (2nd node)
curr = prev->next (5)
List state: head -> 0(2nd) -> 0(1st) -> 4 -> 5 -> 0(3rd) -> NULL

Iteration 4:
curr->data == 5, prev = 4.
else block:
prev = 5
curr = 0 (3rd node)

Iteration 5:
curr->data == 0, prev = 5.
if block:
prev->next = curr->next (5 -> NULL)
curr->next = head (0(3rd) -> 0(2nd))
head = 0 (3rd node)
curr = prev->next (NULL)
List state: head -> 0(3rd) -> 0(2nd) -> 0(1st) -> 4 -> 5 -> NULL

Loop terminates since curr is NULL.
Return head.

Final Output: 0 -> 0 -> 0 -> 4 -> 5
*/
