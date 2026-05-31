/*
GeeksforGeeks: Decimal Equivalent of Binary Linked List
Difficulty: Easy

Problem:
You are given a singly linked list where each node contains either 0 or 1. The linked list represents a binary number, where the head node is the most significant bit (MSB).
Convert this binary number into its decimal equivalent. If the linked list is empty, it represents the number 0.
Since the result can be very large, return the answer modulo 10^9+7.

Example 1:
Input: LinkedList: 1 -> 1 -> 1 -> 0
Output: 14
Explanation: 1*2^3 + 1*2^2 + 1*2^1 + 0*2^0 = 8 + 4 + 2 + 0 = 14

Example 2:
Input: LinkedList: 0 -> 1 -> 1
Output: 3
Explanation: 0*2^2 + 1*2^1 + 1*2^0 = 1 + 2 + 0 = 3

Core Idea:
Since the head of the linked list is the MSB, as we traverse the list we can continuously multiply our accumulated result by 2 (which represents shifting left in binary) and add the current node's value. 
To avoid overflow and since the problem asks for the result modulo 10^9+7, we take the modulo at each step of the calculation.

Approach:
1. Initialize a variable `ans = 0` of type `long long unsigned int` to hold the decimal equivalent.
2. Define the modulo `MOD = 1000000007`.
3. Traverse the linked list starting from the `head`.
4. For each node, update `ans` as: `ans = (ans * 2 + curr->data) % MOD`.
5. Return the final `ans`.

Time Complexity: O(N) where N is the number of nodes in the linked list. We traverse the list exactly once.
Space Complexity: O(1) as we only use a few variables to store the intermediate sum.

GFG Link:
https://www.geeksforgeeks.org/problems/decimal-equivalent-of-binary-linked-list/1
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
    long long unsigned int decimalValue(Node *head) {
        long long unsigned int MOD = 1000000007;
        long long unsigned int ans = 0;
        
        Node* curr = head;
        while (curr != NULL) {
            ans = (ans * 2 + curr->data) % MOD;
            curr = curr->next;
        }
        
        return ans;
    }
};

/*
Dry Run — Example 1:
Input: LinkedList: 1 -> 1 -> 1 -> 0

Initial state:
head -> [1] -> [1] -> [1] -> [0] -> NULL
MOD = 1000000007
ans = 0
curr = head

Step 1:
curr points to 1st [1].
ans = (0 * 2 + 1) % MOD = 1
curr = curr->next

Step 2:
curr points to 2nd [1].
ans = (1 * 2 + 1) % MOD = 3
curr = curr->next

Step 3:
curr points to 3rd [1].
ans = (3 * 2 + 1) % MOD = 7
curr = curr->next

Step 4:
curr points to [0].
ans = (7 * 2 + 0) % MOD = 14
curr = curr->next

Step 5:
curr is NULL. Loop terminates.

Final Output: 14
*/
