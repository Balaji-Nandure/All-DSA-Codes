/*
 * Problem: Swap Nodes in Pairs
 *
 * LeetCode 24: Swap Nodes in Pairs
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/pairwise-swap-elements-of-a-linked-list-by-swapping-data/1
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

/*
 * Problem: Swap Nodes in Pairs
 *
 * LeetCode 24: Swap Nodes in Pairs
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/pairwise-swap-elements-of-a-linked-list-by-swapping-data/1
 *
 * Swap every two adjacent nodes. Only swap nodes, not values.
 * Example: [1,2,3,4] -> [2,1,4,3]
 *
 * Time: O(n) - single pass
 * Space: O(1) for iterative, O(n) for recursive
 */

// Approach 1: Iterative (Optimal Space)
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        // Dummy node simplifies edge case (swapping first two nodes)
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        ListNode* prev = dummy; // Points to node before current pair
        
        while (prev->next && prev->next->next) {
            // Store references to nodes in current pair
            ListNode* first = prev->next;
            ListNode* second = prev->next->next;
            
            // Perform swap: prev -> second -> first -> third
            prev->next = second;        // prev points to second
            first->next = second->next;  // first points to node after pair
            second->next = first;        // second points to first
            
            // Move prev to node before next pair (first is now second in pair)
            prev = first;
        }
        
        return dummy->next;
    }
};

// Approach 2: Recursive
class Solution2 {
public:
    ListNode* swapPairs(ListNode* head) {
        // Base case: empty list or single node (nothing to swap)
        if (!head || !head->next) {
            return head;
        }
        
        // Store references to first two nodes
        ListNode* first = head;
        ListNode* second = head->next;
        
        // Recursively swap the rest of the list (starting from second->next)
        ListNode* rest = swapPairs(second->next);
        
        // Perform swap: second -> first -> rest
        second->next = first;  // second points to first
        first->next = rest;    // first points to swapped rest
        
        // Return new head (second is now first)
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

