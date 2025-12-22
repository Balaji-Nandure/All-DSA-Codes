/*
LeetCode 2807: Insert Greatest Common Divisors in Linked List

Given the head of a linked list head, in which each node contains an integer value.
Between every pair of adjacent nodes, insert a new node with a value equal to the greatest common divisor of them.
Return the linked list after insertion.
The number of nodes in the list will be in the range [1, 5000].

Example:
Input: head = [18,6,10,3]
Output: [18,6,6,2,10,1,3]
Explanation: The 1st diagram denotes the initial linked list and the 2nd diagram denotes the linked list after inserting the new nodes (nodes in blue are the inserted nodes).
- We insert 6 between 18 and 6 because gcd(18,6) = 6.
- We insert 2 between 6 and 10 because gcd(6,10) = 2.
- We insert 1 between 10 and 3 because gcd(10,3) = 1.
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
private:
    // Helper function to calculate GCD using Euclidean algorithm
    int gcd(int a, int b) {
        // Step 1:
        // Base case: if b is 0, then GCD is a
        if (b == 0) {
            return a;
        }
        
        // Step 2:
        // Recursively calculate GCD using Euclidean algorithm
        // GCD(a, b) = GCD(b, a % b)
        return gcd(b, a % b);
    }
    
public:
/*
 * Problem: Insert Greatest Common Divisors in Linked List
 *
 * LeetCode 2807: Insert Greatest Common Divisors in Linked List
 *
 * Insert GCD node between every pair of adjacent nodes.
 * Example: [18,6,10,3] -> [18,6,6,2,10,1,3] (GCD(18,6)=6, GCD(6,10)=2, GCD(10,3)=1)
 *
 * Time: O(n * log(min(a,b))) - n nodes, GCD calculation
 * Space: O(1) - excluding new nodes created
 */

    ListNode* insertGreatestCommonDivisors(ListNode* head) {
        // Edge case: need at least 2 nodes to insert between
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        ListNode* curr = head;
        
        // Traverse and insert GCD nodes between consecutive pairs
        while (curr != nullptr && curr->next != nullptr) {
            // Calculate GCD of current and next node values
            int gcdValue = __gcd(curr->val, curr->next->val);
            
            // Create new node with GCD value
            ListNode* newNode = new ListNode(gcdValue);
            
            // Insert between curr and curr->next
            newNode->next = curr->next;
            curr->next = newNode;
            
            // Move to node after inserted node (skip inserted node)
            curr = newNode->next;
        }
        
        return head;
    }
};

/*
Approach: Traverse and Insert GCD Nodes
- Traverse the linked list
- For each pair of consecutive nodes, calculate their GCD
- Insert a new node with the GCD value between them
- Continue until we've processed all pairs

Time Complexity: O(n * log(min(a, b))) - where n is number of nodes, and we calculate GCD for each pair
Space Complexity: O(1) - only using constant extra space (excluding the new nodes we create)

Key Insight:
- We need to insert nodes between every pair of adjacent nodes
- GCD can be calculated efficiently using Euclidean algorithm
- After inserting a node, we need to move forward by 2 positions (skip the inserted node)
- The insertion modifies the list in-place

Example Walkthrough:
Input: head = [18,6,10,3]
Step 1: curr = 18, next = 6
  - GCD(18, 6) = 6
  - Insert node(6) between 18 and 6
  - List: [18,6,6,10,3]
  - Move curr to 6 (the original next)
Step 2: curr = 6, next = 10
  - GCD(6, 10) = 2
  - Insert node(2) between 6 and 10
  - List: [18,6,6,2,10,3]
  - Move curr to 10
Step 3: curr = 10, next = 3
  - GCD(10, 3) = 1
  - Insert node(1) between 10 and 3
  - List: [18,6,6,2,10,1,3]
  - Move curr to 3
Step 4: curr->next is null, stop
Output: [18,6,6,2,10,1,3]
*/

