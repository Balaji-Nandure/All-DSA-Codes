/*
LeetCode 1171: Remove Zero Sum Consecutive Nodes from Linked List

Given the head of a linked list, we repeatedly delete consecutive sequences of nodes 
that sum to 0 until there are no such sequences.
After doing so, return the head of the final linked list. You may return any such answer.

Example:
Input: head = [1,2,-3,3,1]
Output: [3,1]
Note: The answer [1,2,1] would also be accepted.
Explanation: We remove the sequence [2,-3] which sums to 0, leaving [1,3,1] or [3,1].
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

class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        // Create a dummy node to handle edge cases
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // Map to store prefix sum and corresponding node
        unordered_map<int, ListNode*> prefixSum;
        
        int sum = 0;
        prefixSum[0] = dummy;
        
        ListNode* current = head;
        
        // First pass: Build prefix sum map
        while (current != nullptr) {
            sum += current->val;
            
            // If we've seen this prefix sum before, it means the subarray
            // between the previous occurrence and current sums to zero
            if (prefixSum.count(sum)) {
                // Remove all nodes between the previous occurrence and current
                ListNode* prev = prefixSum[sum];
                ListNode* toDelete = prev->next;
                int tempSum = sum;
                
                // Remove intermediate prefix sums from map
                while (toDelete != current) {
                    tempSum += toDelete->val;
                    prefixSum.erase(tempSum);
                    toDelete = toDelete->next;
                }
                
                // Skip the zero-sum subarray
                prev->next = current->next;
            } else {
                // Store the prefix sum and current node
                prefixSum[sum] = current;
            }
            
            current = current->next;
        }
        
        return dummy->next;
    }
};

/*
Approach: Prefix Sum with Hash Map
- Use prefix sum to detect zero-sum subarrays
- If prefix sum at index i equals prefix sum at index j (i < j), 
  then the subarray from i+1 to j sums to zero
- Use a hash map to store prefix sums and their corresponding nodes
- When we find a duplicate prefix sum, remove all nodes between the two occurrences
- Also remove intermediate prefix sums from the map

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - hash map to store prefix sums

Key Insight:
- If prefix_sum[i] == prefix_sum[j], then sum of elements from i+1 to j is zero
- We need to remove all nodes from i+1 to j, and also clean up the prefix sums
- Using a dummy node makes it easier to handle edge cases like removing from the beginning

Example Walkthrough:
Input: [1, 2, -3, 3, 1]
Prefix sums: 0 -> 1 -> 3 -> 0 -> 3 -> 4
When we see prefix sum 0 again at index 3, we know [2, -3] sums to zero
Remove [2, -3] and update the list to [1, 3, 1]
*/

