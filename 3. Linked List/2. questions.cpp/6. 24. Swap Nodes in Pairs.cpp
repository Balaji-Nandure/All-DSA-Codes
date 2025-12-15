/*
 * Problem: Swap Nodes in Pairs
 *
 * LeetCode 24: Swap Nodes in Pairs
 * GeeksforGeeks: https://www.geeksforgeeks.org/pairwise-swap-elements-of-a-given-linked-list/
 *
 * Given a linked list, swap every two adjacent nodes and return its head. 
You must solve the problem without modifying the values in the list's nodes 
(i.e., only nodes themselves may be changed.)

Example:
Input: head = [1,2,3,4]
Output: [2,1,4,3]
Explanation: We swap nodes 1-2 and 3-4 to get [2,1,4,3].
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// Approach 1: Iterative
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // Create a dummy node to simplify edge cases
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* prev = dummy;
        
        while (prev->next && prev->next->next) {
            // Nodes to be swapped
            ListNode* first = prev->next;
            ListNode* second = prev->next->next;
            
            // Perform the swap
            prev->next = second;        // prev -> second
            first->next = second->next;  // first -> third
            second->next = first;        // second -> first
            
            // Move prev to the node before the next pair
            prev = first;
        }
        
        return dummy->next;
    }
};

// Approach 2: Recursive
class Solution2 {
public:
    ListNode* swapPairs(ListNode* head) {
        // Base case: if list is empty or has only one node
        if (!head || !head->next) {
            return head;
        }
        
        // Nodes to be swapped
        ListNode* first = head;
        ListNode* second = head->next;
        
        // Recursively swap the rest of the list
        ListNode* rest = swapPairs(second->next);
        
        // Perform the swap
        second->next = first;
        first->next = rest;
        
        // Return the new head (which is second)
        return second;
    }
};

/*
Approach 1: Iterative
- Use a dummy node to handle edge cases (swapping first two nodes)
- For each pair of nodes:
  1. Store references to first and second nodes
  2. Update pointers to swap them
  3. Move to the next pair
- Continue until we reach the end or have less than 2 nodes left

Time Complexity: O(n) - single pass through the list
Space Complexity: O(1) - only using constant extra space

Approach 2: Recursive
- Base case: if list is empty or has only one node, return head
- For each pair:
  1. Store references to first and second nodes
  2. Recursively swap the rest of the list
  3. Connect second -> first, and first -> rest
  4. Return second as the new head

Time Complexity: O(n) - visit each node once
Space Complexity: O(n) - recursion stack depth

Key Insight:
- We need to swap nodes, not just values
- Use a dummy node to simplify handling the first pair
- After swapping, the first node becomes the second, and second becomes first
- The first node should point to the result of swapping the rest

Example Walkthrough:
Input: [1,2,3,4]
- Pair 1: Swap 1 and 2 -> [2,1,3,4]
- Pair 2: Swap 3 and 4 -> [2,1,4,3]
Output: [2,1,4,3]
*/

