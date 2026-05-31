/*
GeeksforGeeks: Merge Lists Alternatingly
Difficulty: Easy

Problem:
Given two linked lists head1 and head2, insert nodes of the second list into the first list at alternate positions. If all nodes cannot be inserted, keep the remaining nodes unchanged.
Return an array containing the heads of the modified lists in their original order.

Example 1:
Input: head1: 10 -> 9, head2: 6 -> 1 -> 2 -> 3 -> 4 -> 5
Output: head1: 10 -> 6 -> 9 -> 1, head2: 2 -> 3 -> 4 -> 5
Explanation: After inserting nodes of head2 alternately into head1, the modified lists become 10 -> 6 -> 9 -> 1 and 2 -> 3 -> 4 -> 5, as the remaining nodes of head2 cannot be inserted.

Example 2:
Input: head1: 1 -> 2 -> 3, head2: 4 -> 5 -> 6
Output: head1: 1 -> 4 -> 2 -> 5 -> 3 -> 6, head2: <empty>
Explanation: After inserting nodes of head2 alternately into head1, the merged list becomes 1 -> 4 -> 2 -> 5 -> 3 -> 6, and head2 becomes empty as all its nodes are used.

Core Idea:
We can solve this problem in place by simultaneously iterating through both linked lists.
For each step, we detach one node from the second list (`head2`) and insert it immediately after the current node in the first list (`head1`). 
We continue this alternating process until we reach the end of either list. Whatever is left in the second list (if anything) stays in place, and its new head will be the point where we stopped.

Approach:
1. If `head1` is `NULL`, we cannot insert anything at alternate positions, so we just return `{head1, head2}`.
2. Initialize two pointers, `curr1 = head1` and `curr2 = head2`.
3. Loop while `curr1 != NULL && curr2 != NULL`:
   a. Store the next pointers: `next1 = curr1->next` and `next2 = curr2->next`.
   b. Insert `curr2` between `curr1` and `next1`:
      - `curr1->next = curr2`
      - `curr2->next = next1`
   c. Advance the pointers:
      - `curr1 = next1`
      - `curr2 = next2`
4. After the loop, `curr2` will point to the start of the remaining nodes in the second list (if any).
5. Return `{head1, curr2}`.

Time Complexity: O(min(N, M)) where N and M are the sizes of the two linked lists. We stop as soon as we reach the end of either list.
Space Complexity: O(1) since we are modifying the lists in-place using a few pointers.

GFG Link:
https://www.geeksforgeeks.org/problems/merge-list-alternatingly/1
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
    vector<Node*> mergeList(Node* head1, Node* head2) {
        if (!head1) {
            return {head1, head2};
        }

        Node* curr1 = head1;
        Node* curr2 = head2;

        while (curr1 != NULL && curr2 != NULL) {
            // Save next pointers
            Node* next1 = curr1->next;
            Node* next2 = curr2->next;

            // Make curr2 the next node of curr1
            curr1->next = curr2;
            
            // Make next1 the next node of curr2
            curr2->next = next1;

            // Move pointers ahead for the next iteration
            curr1 = next1;
            curr2 = next2;
        }

        // Return the modified head1 and the remaining head2 (curr2)
        return {head1, curr2};
    }
};

/*
Dry Run — Example 1:
Input: head1: 10 -> 9, head2: 6 -> 1 -> 2 -> 3 -> 4 -> 5

Initial State:
curr1 -> 10 -> 9
curr2 -> 6 -> 1 -> 2 -> ...

Iteration 1:
next1 = 9, next2 = 1
curr1->next = curr2 (10 -> 6)
curr2->next = next1 (6 -> 9)
curr1 = next1 (9)
curr2 = next2 (1)

Iteration 2:
curr1 is 9, curr2 is 1
next1 = NULL, next2 = 2
curr1->next = curr2 (9 -> 1)
curr2->next = next1 (1 -> NULL)
curr1 = next1 (NULL)
curr2 = next2 (2)

Loop ends because curr1 is NULL.
Return {head1, curr2}
head1: 10 -> 6 -> 9 -> 1 -> NULL
curr2 (new head2): 2 -> 3 -> 4 -> 5 -> NULL
*/
