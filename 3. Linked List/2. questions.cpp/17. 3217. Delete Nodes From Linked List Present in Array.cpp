/*
LeetCode 3217: Delete Nodes From Linked List Present in Array

You are given the head of a linked list and an array nums.
Delete every node whose value is present in nums.
Return the head of the modified linked list.

Example:
Input: head = [1,2,3,4,5], nums = [1,2,3]
Output: [4,5]
Explanation: Nodes 1, 2, and 3 are deleted because their values are in nums.
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
 * Problem: Delete Nodes From Linked List Present in Array
 *
 * LeetCode 3217: Delete Nodes From Linked List Present in Array
 *
 * Delete all nodes whose values are present in the given array.
 * Example: [1,2,3,4,5], nums=[1,2,3] -> [4,5]
 *
 * Time: O(n + m) - where n is list length, m is array length
 * Space: O(m) - hash set for array values
 */

    ListNode* modifiedList(vector<int>& nums, ListNode* head) {
        // Step 1: Store nums in hash set for O(1) lookup
        unordered_set<int> st(nums.begin(), nums.end());

        // Step 2: Dummy node handles edge case (deleting head)
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;
        ListNode* curr = head;

        // Step 3: Traverse and remove nodes whose values are in set
        while (curr != nullptr) {
            if (st.count(curr->val)) {
                // Delete node: bypass it
                prev->next = curr->next;
            } else {
                // Keep node: move prev forward
                prev = curr;
            }
            curr = curr->next;
        }

        // Step 4: Return new head (skip dummy)
        return dummy->next;
    }
};
    

/*
Approach: Hash Set with Dummy Node
- Create a hash set from the nums array for O(1) lookup
- Use a dummy node to handle edge case of deleting the head
- Traverse the list and remove nodes whose values are in the set
- Update pointers to skip deleted nodes

Time Complexity: O(n + m) - where n is length of list, m is length of nums array
Space Complexity: O(m) - hash set to store nums values

Key Insight:
- Using a hash set allows O(1) lookup to check if a value should be deleted
- Dummy node simplifies handling the case where head needs to be deleted
- We need to properly update pointers and delete nodes to avoid memory leaks

Example Walkthrough:
Input: head = [1,2,3,4,5], nums = [1,2,3]
Step 1: Create set {1, 2, 3}
Step 2: Traverse list:
  - Node 1: in set, delete -> [2,3,4,5]
  - Node 2: in set, delete -> [3,4,5]
  - Node 3: in set, delete -> [4,5]
  - Node 4: not in set, keep
  - Node 5: not in set, keep
Output: [4,5]
*/
