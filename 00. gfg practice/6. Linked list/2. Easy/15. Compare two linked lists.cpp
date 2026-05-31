/*
GeeksforGeeks: Compare two linked lists
Difficulty: Easy

Problem:
Given two strings, head1 and head2, represented as linked lists where each character is stored in a node's data field, complete the function compare() that mimics the behavior of strcmp(). 
Specifically, the function should return:
0 if both strings are identical,
1 if the first linked list is lexicographically greater, and
-1 if the second linked list is lexicographically greater.

Example 1:
Input: head1 = a->b->a->b->a , head2 = a->b->a->a
Output: 1
Explanation: String consisting of nodes of first linked list is lexicographically greater than the second one. So, the result is 1.

Example 2:
Input: head1 = a->a->b , head2 = a->a->b
Output: 0
Explanation: Both strings are identical.

Example 3:
Input: head1 = a->b->c->d , head2 = a->b->c->e
Output: -1
Explanation: String consisting of nodes of second linked list is lexicographically greater than the first one. So, the result is -1.

Core Idea:
This is similar to `strcmp()` in C. We compare characters one by one by traversing both linked lists simultaneously.
As long as the characters match and we haven't reached the end of either list, we continue to the next nodes.
When we encounter a mismatch or reach the end of one (or both) lists, we stop and evaluate:
1. If both reached the end simultaneously, they are exactly the same (return 0).
2. If the first list ended but the second hasn't, the second is longer and therefore lexicographically greater (return -1).
3. If the second list ended but the first hasn't, the first is longer (return 1).
4. If there's a mismatch, we simply compare the ASCII values of the mismatched characters to determine which is lexicographically greater.

Approach:
1. Initialize two pointers `curr1 = head1` and `curr2 = head2`.
2. Loop while `curr1 != NULL`, `curr2 != NULL`, and `curr1->c == curr2->c`:
   a. Move `curr1 = curr1->next`.
   b. Move `curr2 = curr2->next`.
3. After exiting the loop:
   a. If `curr1 == NULL && curr2 == NULL`: return 0.
   b. If `curr1 == NULL`: return -1 (head2 is longer).
   c. If `curr2 == NULL`: return 1 (head1 is longer).
   d. If `curr1->c > curr2->c`: return 1.
   e. Else return -1.

Time Complexity: O(min(N, M)) where N and M are the lengths of the two linked lists. We traverse until the end of the shorter list or until a mismatch is found.
Space Complexity: O(1) as we only use pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/compare-two-linked-lists/1
*/

#include <iostream>

using namespace std;

struct Node {
    char c;
    struct Node* next;
    
    Node(char x) {
        c = x;
        next = NULL;
    }
};

class Solution {
public:
    int compare(Node *head1, Node *head2) {
        Node* curr1 = head1;
        Node* curr2 = head2;
        
        while (curr1 != NULL && curr2 != NULL && curr1->c == curr2->c) {
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        
        // If both strings are exactly the same
        if (curr1 == NULL && curr2 == NULL) {
            return 0;
        }
        
        // If the first string ended first, it is lexicographically smaller
        if (curr1 == NULL) {
            return -1;
        }
        
        // If the second string ended first, it is lexicographically smaller
        if (curr2 == NULL) {
            return 1;
        }
        
        // If they mismatched at some point
        if (curr1->c > curr2->c) {
            return 1;
        } else {
            return -1;
        }
    }
};

/*
Dry Run — Example 1:
Input: head1 = a->b->a->b->a , head2 = a->b->a->a

Initial state:
curr1 = head1 (points to 'a')
curr2 = head2 (points to 'a')

Loop Iterations:
1. curr1->c ('a') == curr2->c ('a'). Match.
   curr1 = curr1->next ('b')
   curr2 = curr2->next ('b')
   
2. curr1->c ('b') == curr2->c ('b'). Match.
   curr1 = curr1->next ('a')
   curr2 = curr2->next ('a')
   
3. curr1->c ('a') == curr2->c ('a'). Match.
   curr1 = curr1->next ('b')
   curr2 = curr2->next ('a')

4. curr1->c ('b') == curr2->c ('a'). Mismatch!
   Loop terminates.

Evaluation:
- curr1 is not NULL.
- curr2 is not NULL.
- curr1->c ('b') > curr2->c ('a'). Returns 1.

Final Output: 1
*/
