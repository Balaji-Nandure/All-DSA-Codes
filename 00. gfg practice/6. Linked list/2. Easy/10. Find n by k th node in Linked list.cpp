/*
GeeksforGeeks: Find n/k th node in Linked list
Difficulty: Easy

Problem:
Given the head of a singly linked list and an integer k, find the (n/k)th node in the linked list, where n is the total number of nodes.
If the value of n/k is not an integer, then consider its ceiling value.

Example 1:
Input: head: 1->2->3->4->5->6 , k = 2
Output: 3
Explanation: 6/2th element is the 3rd(1-based indexing) element which is 3.

Example 2:
Input: head: 2->7->9->3->5 , k = 3
Output: 7
Explanation: The 5/3rd element is the 2nd element as mentioned in the question that we need to consider ceil value in the case of decimals. So 2nd element is 7.

Core Idea:
To find the ceil(n/k)-th node, we first need to know the total length `n` of the linked list. 
Once we find `n`, we calculate the target index using the ceiling division formula `(n + k - 1) / k`. 
Then we do a second traversal to reach that specific 1-based index and return its data.

Approach:
1. Traverse the linked list from `head` to count the total number of nodes `n`.
2. Calculate the target index `idx = (n + k - 1) / k`. (This computes the ceiling of n/k in integer arithmetic).
3. Reset a pointer `curr = head`.
4. Run a loop `idx - 1` times: move `curr = curr->next`. This is because we want the `idx`-th element (1-based), so we make `idx - 1` jumps from the head.
5. Return `curr->data`.

Time Complexity: O(N) where N is the number of nodes in the linked list. We traverse the list at most twice.
Space Complexity: O(1) as we only use a few variables for counting.

GFG Link:
https://www.geeksforgeeks.org/problems/find-nk-th-node-in-linked-list/1
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
    int fractional_node(struct Node *head, int k) {
        if (head == NULL) return -1;
        
        // Step 1: Find the length of the linked list
        int n = 0;
        Node* curr = head;
        while (curr != NULL) {
            n++;
            curr = curr->next;
        }
        
        // Step 2: Calculate the target index using ceil(n/k)
        int targetIndex = (n + k - 1) / k;
        
        // Step 3: Find the node at targetIndex (1-based indexing)
        curr = head;
        for (int i = 1; i < targetIndex; i++) {
            curr = curr->next;
        }
        
        return curr->data;
    }
};

/*
Dry Run — Example 2:
Input: head: 2->7->9->3->5 , k = 3

Initial state:
head -> [2] -> [7] -> [9] -> [3] -> [5] -> NULL
k = 3

Step 1 (Find Length):
- Traverse from head to NULL.
- Total length `n` becomes 5.

Step 2 (Calculate Target Index):
- targetIndex = (n + k - 1) / k
- targetIndex = (5 + 3 - 1) / 3 = 7 / 3 = 2.
- The target is the 2nd node.

Step 3 (Find Target Node):
- curr = head (points to 2)
- i = 1 to targetIndex - 1 (i = 1 to 1). Loop runs 1 time.
- i = 1: curr = curr->next (curr now points to 7)

Step 4 (Return):
- Return curr->data (7)

Final Output: 7
*/
