/*
LeetCode 445: Add Two Numbers II

You are given two non-empty linked lists representing two non-negative integers. 
The most significant digit comes first and each of their nodes contains a single digit. 
Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Output: [7,8,0,7]
Explanation: 7243 + 564 = 7807
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

// Approach 1: Using Stacks
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
/*
 * Problem: Add Two Numbers II
 *
 * LeetCode 445: Add Two Numbers II
 *
 * Add two numbers represented as linked lists (most significant digit first).
 * Example: [7,2,4,3] + [5,6,4] = [7,8,0,7] (7243 + 564 = 7807)
 *
 * Time: O(max(m,n)) - where m, n are lengths
 * Space: O(m+n) for stacks, O(1) for reverse method
 */

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        
        // Push all digits from l1 into stack (reverses order)
        while (l1 != nullptr) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        
        // Push all digits from l2 into stack (reverses order)
        while (l2 != nullptr) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        
        int carry = 0;
        ListNode* result = nullptr;
        
        // Process digits from both stacks (add from least significant)
        while (!s1.empty() || !s2.empty() || carry != 0) {
            int sum = carry;
            
            // Add digits from both stacks
            if (!s1.empty()) {
                sum += s1.top();
                s1.pop();
            }
            
            if (!s2.empty()) {
                sum += s2.top();
                s2.pop();
            }
            
            carry = sum / 10; // New carry
            int digit = sum % 10; // Current digit
            
            // Create new node and add to front (most significant digit first)
            ListNode* newNode = new ListNode(digit);
            newNode->next = result;
            result = newNode; // Update head
        }
        
        return result;
    }
};

// Approach 2: Reverse Lists, Add, Reverse Result (optimal)
class Solution2 {
private:
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
    
    ListNode* addTwoReversed(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* current = dummy;
        int carry = 0;
        
        while (l1 || l2 || carry) {
            int sum = carry;
            
            if (l1) {
                sum += l1->val;
                l1 = l1->next;
            }
            
            if (l2) {
                sum += l2->val;
                l2 = l2->next;
            }
            
            carry = sum / 10;
            current->next = new ListNode(sum % 10);
            current = current->next;
        }
        
        return dummy->next;
    }
    
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // Reverse both lists
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
        // Add the reversed lists
        ListNode* result = addTwoReversed(l1, l2);
        
        // Reverse the result
        // result = reverseList(result);
        
        // // Restore original lists (optional, if we need to preserve input)
        // l1 = reverseList(l1);
        // l2 = reverseList(l2);
        
        return result;
    }
};

/*
Approach 1: Using Stacks
- Push all digits from both lists into stacks
- Pop digits from stacks and add them (similar to adding from right to left)
- Handle carry while adding
- Build result list from right to left (most significant digit first)

Time Complexity: O(max(m, n)) - where m and n are lengths of l1 and l2
Space Complexity: O(m + n) - stacks to store digits

Approach 2: Reverse Lists, Add, Reverse Result
- Reverse both input lists
- Add them (now we can add from right to left)
- Reverse the result to get most significant digit first
- Optionally restore original lists

Time Complexity: O(max(m, n)) - reverse operations + addition
Space Complexity: O(1) - excluding the result list

Key Insight:
- Since digits are stored with most significant digit first, we need to add from right to left
- Stacks naturally help us process digits in reverse order
- Alternatively, we can reverse the lists, add them, and reverse the result
- Approach 1 is cleaner and doesn't modify input lists

Example Walkthrough:
Input: l1 = [7,2,4,3], l2 = [5,6,4]
Stack 1: [3,4,2,7] (bottom to top)
Stack 2: [4,6,5] (bottom to top)
Add: 3+4=7, 4+6=10 (carry 1), 2+5+1=8, 7+0=7
Result: [7,8,0,7]
*/

