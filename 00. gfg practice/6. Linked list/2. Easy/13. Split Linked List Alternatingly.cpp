/*
GeeksforGeeks: Split Linked List Alternatingly
Difficulty: Easy

Problem:
Given a singly linked list's head. Your task is to complete the function alternatingSplitList() that splits the given linked list into two smaller lists. The sublists should be made from alternating elements from the original list.
Note: 
- The sublist should be in the order with respect to the original list.
- You have to return an array containing both sub-linked lists.

Example 1:
Input: LinkedList = 0->1->0->1->0->1
Output: 0->0->0 , 1->1->1
Explanation: After forming two sublists of the given list as required, we have two lists as: 0->0->0 and 1->1->1.

Example 2:
Input: LinkedList = 2->5->8->9->6
Output: 2->8->6 , 5->9
Explanation: After forming two sublists of the given list as required, we have two lists as: 2->8->6 and 5->9.

Example 3:
Input: LinkedList: 7 
Output: 7 , <empty linked list>

Core Idea:
We can maintain two pointers, `curr1` starting at `head` and `curr2` starting at `head->next`. 
These will trace out the two alternating sublists.
In each step, `curr1->next` should point to the node after `curr2` (which is `curr2->next`), and then `curr1` should jump to that node.
Similarly, `curr2->next` should point to the node after the newly moved `curr1` (which is `curr1->next`), and `curr2` jumps to that node.
We continue this alternating jump until we run out of nodes.

Approach:
1. Base cases: 
   - If `head == NULL`, return `{NULL, NULL}`.
   - If `head->next == NULL`, return `{head, NULL}`.
2. Initialize `head1 = head` and `head2 = head->next`.
3. Initialize iterators `curr1 = head1` and `curr2 = head2`.
4. Loop while `curr1 != NULL && curr2 != NULL`:
   a. Update `curr1->next = curr2->next` (skipping one node).
   b. Move `curr1 = curr1->next`.
   c. If `curr1` is not `NULL` (we haven't reached the end):
      i. Update `curr2->next = curr1->next` (skipping one node).
      ii. Move `curr2 = curr2->next`.
5. Return `{head1, head2}`.

Time Complexity: O(N) where N is the number of nodes. We traverse the linked list exactly once.
Space Complexity: O(1) as we only rearrange the existing nodes and use a few pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/split-singly-linked-list-alternatingly/1
*/

#include <iostream>
#include <vector>

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
    vector<Node*> alternatingSplitList(Node* head) {
        if (head == NULL) {
            return {NULL, NULL};
        }
        if (head->next == NULL) {
            return {head, NULL};
        }
        
        Node* head1 = head;
        Node* head2 = head->next;
        
        Node* curr1 = head1;
        Node* curr2 = head2;
        
        while (curr1 != NULL && curr2 != NULL) {
            // Update curr1's next pointer to skip the alternate node
            curr1->next = curr2->next;
            curr1 = curr1->next;
            
            if (curr1 != NULL) {
                // Update curr2's next pointer to skip the alternate node
                curr2->next = curr1->next;
                curr2 = curr2->next;
            }
        }
        
        return {head1, head2};
    }
};

/*
Dry Run — Example 2:
Input: LinkedList = 2->5->8->9->6

Initial state:
head -> [2] -> [5] -> [8] -> [9] -> [6] -> NULL
head1 = 2
head2 = 5
curr1 = head1 (points to 2)
curr2 = head2 (points to 5)

Loop Iteration 1:
- `curr1 != NULL && curr2 != NULL` is TRUE
- `curr1->next = curr2->next` => `2->next = 8`
- `curr1 = curr1->next` => curr1 is now 8
- `curr1 != NULL` (8 != NULL) is TRUE
- `curr2->next = curr1->next` => `5->next = 9`
- `curr2 = curr2->next` => curr2 is now 9

Loop Iteration 2:
- `curr1 != NULL && curr2 != NULL` (8 and 9) is TRUE
- `curr1->next = curr2->next` => `8->next = 6`
- `curr1 = curr1->next` => curr1 is now 6
- `curr1 != NULL` (6 != NULL) is TRUE
- `curr2->next = curr1->next` => `9->next = NULL`
- `curr2 = curr2->next` => curr2 is now NULL

Loop Iteration 3:
- `curr1 != NULL && curr2 != NULL` (6 and NULL) is FALSE
- Loop terminates.

Final Output:
head1: 2 -> 8 -> 6 -> NULL
head2: 5 -> 9 -> NULL
Return {head1, head2}
*/
