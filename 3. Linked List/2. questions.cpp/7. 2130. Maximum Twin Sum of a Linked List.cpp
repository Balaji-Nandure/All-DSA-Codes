/*
LeetCode 2130: Maximum Twin Sum of a Linked List

In a linked list of size n, where n is even, the ith node (0-indexed) of the linked list 
is known as the twin of the (n-1-i)th node, if 0 <= i <= (n / 2) - 1.
For example, if n = 4, then node 0 is the twin of node 3, and node 1 is the twin of node 2. 
These are the only nodes with twins for n = 4.
The twin sum is defined as the sum of a node and its twin.
Given the head of a linked list with even length, return the maximum twin sum of the linked list.

Example:
Input: head = [5,4,2,1]
Output: 6
Explanation:
Nodes 0 and 1 are the twins of nodes 3 and 2, respectively. All have twin sum = 6.
There are no nodes with twin sum greater than 6. Thus, the answer is 6.
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

// Approach 1: Reverse Second Half (optimal)
class Solution {
private:
    // Helper function to reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* current = head;
        
        while (current != nullptr) {
            ListNode* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        
        return prev;
    }
    
public:
    int pairSum(ListNode* head) {
        // Find the middle of the linked list using two pointers
        ListNode* slow = head;
        ListNode* fast = head;

        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // Reverse the second half
        ListNode* secondHalf = reverseList(slow);
        ListNode* firstHalf = head;
        ListNode* reversedHead = secondHalf; // Remember the head of reversed part

        // Calculate maximum twin sum
        int maxSum = 0;
        while (secondHalf != nullptr) {
            maxSum = max(maxSum, firstHalf->val + secondHalf->val);
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }

        // Restore the list by reversing the second half back
        reverseList(reversedHead);

        return maxSum;
    }
};

// Approach 2: Using Stack
class Solution2 {
public:
    int pairSum(ListNode* head) {
        stack<int> st;
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Push first half into stack
        while (fast != nullptr && fast->next != nullptr) {
            st.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Now slow is at the start of second half
        // Calculate maximum twin sum
        int maxSum = 0;
        while (slow != nullptr) {
            maxSum = max(maxSum, st.top() + slow->val);
            st.pop();
            slow = slow->next;
        }
        
        return maxSum;
    }
};

// Approach 3: Using Vector
class Solution3 {
public:
    int pairSum(ListNode* head) {
        vector<int> values;
        ListNode* current = head;
        
        // Store all values in a vector
        while (current != nullptr) {
            values.push_back(current->val);
            current = current->next;
        }
        
        // Calculate maximum twin sum
        int maxSum = 0;
        int n = values.size();
        for (int i = 0; i < n / 2; i++) {
            maxSum = max(maxSum, values[i] + values[n - 1 - i]);
        }
        
        return maxSum;
    }
};

/*
Approach 1: Reverse Second Half (Space Efficient)
- Find the middle of the linked list using two pointers
- Reverse the second half of the list
- Traverse both halves simultaneously and calculate twin sums
- Return the maximum twin sum

Time Complexity: O(n) - single pass to find middle, reverse, and calculate
Space Complexity: O(1) - only using constant extra space

Approach 2: Using Stack
- Use two pointers to find the middle
- Push first half values into a stack
- Traverse second half and pop from stack to get twin pairs
- Calculate maximum twin sum

Time Complexity: O(n) - single pass through the list
Space Complexity: O(n) - stack to store first half values

Approach 3: Using Vector
- Store all node values in a vector
- Calculate twin sums by pairing values[i] with values[n-1-i]
- Return the maximum twin sum

Time Complexity: O(n) - two passes (store + calculate)
Space Complexity: O(n) - vector to store all values

Key Insight:
- Twin nodes are at positions i and n-1-i (0-indexed)
- For even length n, we have n/2 twin pairs
- We need to find the maximum sum among all twin pairs
- Approach 1 is most space-efficient as it doesn't require extra data structures

Example Walkthrough:
Input: [5,4,2,1]
Twin pairs: (0,3) = 5+1 = 6, (1,2) = 4+2 = 6
Maximum twin sum: 6
*/

