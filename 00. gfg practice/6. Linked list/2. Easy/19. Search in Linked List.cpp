/*
GeeksforGeeks: Search in Linked List
Difficulty: Easy

Problem:
Given a linked list with the head node and a key, the task is to check if the key is present in the linked list or not. Return true if key is present, else return false.

Example 1:
Input: key = 3, Linked List: 1 -> 2 -> 3 -> 4
Output: true 
Explanation: 3 is present in Linked List.

Example 2:
Input: key = 4, Linked List: 1 -> 2 -> 3
Output: false
Explanation: 4 is not present in Linked List.

Core Idea:
To find a key in a singly linked list, we need to iterate through the list starting from the head. At each node, we check if the node's data matches the given key. If we find a match, we return true immediately. If we reach the end of the list (NULL) without finding the key, it means the key is not present, and we return false.

Approach:
1. Initialize a pointer `curr` to the `head` of the linked list.
2. Run a `while` loop until `curr` becomes `NULL`.
3. In each iteration, check if `curr->data == key`.
   - If true, return `true`.
4. If not true, move `curr` to the next node (`curr = curr->next`).
5. If the loop terminates, it means the key was not found. Return `false`.

Time Complexity: O(N) where N is the number of nodes in the linked list. In the worst case, we might have to traverse the entire list.
Space Complexity: O(1) as we only use a single pointer for traversal.

GFG Link:
https://www.geeksforgeeks.org/problems/search-in-linked-list-1611824497/1
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
    // Function to check if the key is present in the linked list.
    // Note: GFG signature might vary slightly (e.g., passing 'n' as well).
    bool searchKey(Node* head, int key) {
        Node* curr = head;
        
        while (curr != NULL) {
            if (curr->data == key) {
                return true;
            }
            curr = curr->next;
        }
        
        return false;
    }
};

/*
Dry Run — Example 1:
Input: key = 3, Linked List: 1 -> 2 -> 3 -> 4

Initial State:
head -> 1 -> 2 -> 3 -> 4 -> NULL
curr = head (1)
key = 3

Iteration 1:
curr != NULL is true.
curr->data (1) == key (3) ? False.
curr = curr->next (curr is now at node 2)

Iteration 2:
curr != NULL is true.
curr->data (2) == key (3) ? False.
curr = curr->next (curr is now at node 3)

Iteration 3:
curr != NULL is true.
curr->data (3) == key (3) ? True.
Return true.

Final Output: true
*/
