/*
LeetCode 2181: Merge Nodes in Between Zeros

You are given the head of a linked list, which contains a series of integers separated by 0's. 
The beginning and end of the linked list will have Node.val == 0.
For every two consecutive 0's, merge all the nodes lying in between them into a single node 
whose value is the sum of all the merged nodes. The modified list should not contain any 0's.
Return the head of the modified linked list.

Example:
Input: head = [0,3,1,0,4,5,2,0]
Output: [4,11]
Explanation: 
The above figure represents the given linked list. The modified list contains:
- The sum of the nodes marked in green: 3 + 1 = 4.
- The sum of the nodes marked in red: 4 + 5 + 2 = 11.
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
/*
 * Problem: Merge Nodes in Between Zeros
 *
 * LeetCode 2181: Merge Nodes in Between Zeros
 *
 * Merge all nodes between consecutive zeros into single node with sum.
 * Example: [0,3,1,0,4,5,2,0] -> [4,11] (3+1=4, 4+5+2=11)
 *
 * Time: O(n) - single pass
 * Space: O(n) - new list for result
 */

    ListNode* mergeNodes(ListNode* head) {
        // Dummy node simplifies result list construction
        ListNode* dummy = new ListNode(0);
        ListNode* result = dummy;
        
        ListNode* current = head->next;  // Skip first 0
        int sum = 0;
        
        while (current != nullptr) {
            if (current->val == 0) {
                // End of segment: create node with sum
                if (sum > 0) {
                    result->next = new ListNode(sum);
                    result = result->next;
                    sum = 0; // Reset for next segment
                }
            } else {
                // Add to current segment sum
                sum += current->val;
            }
            current = current->next;
        }
        
        return dummy->next;
    }
};

// Approach 2: In-place (Modify existing list)
class Solution2 {
    public:
        ListNode* mergeNodes(ListNode* head) {
            ListNode* prev = head;
            for(ListNode* curr = head->next; curr->next; curr = curr->next){
                if(curr->val == 0){
                    prev->next = curr;
                    prev = prev -> next;
                } else {
                    prev->val += curr->val;
                    prev->next = curr->next->next;
                }
            }
            return head;
        }
    };

/*
Approach 1: Using Dummy Node
- Create a dummy node to simplify result list construction
- Traverse the list starting from head->next (skip first 0)
- Sum values between consecutive zeros
- When we encounter a zero, create a new node with the sum and add to result
- Continue until the end

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - new list for result

Approach 2: In-place (Similar logic, different structure)
- Traverse the list starting from head->next
- Sum values between consecutive zeros
- Create new nodes and build result list
- Return the head of result list

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - new nodes for result

Key Insight:
- The list starts and ends with 0
- We need to merge all nodes between consecutive 0's
- Sum all values between two zeros and create a single node
- Skip the first 0 and process segments until we reach the end

Example Walkthrough:
Input: head = [0,3,1,0,4,5,2,0]
Step 1: Skip first 0, start at node 3
Step 2: Sum segment 1: 3 + 1 = 4, create node(4)
Step 3: Sum segment 2: 4 + 5 + 2 = 11, create node(11)
Step 4: Reached end (last 0)
Output: [4,11]
*/

