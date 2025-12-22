/*
LeetCode 725: Split Linked List in Parts

Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.
The length of each part should be as equal as possible: no two parts should have a size differing by more than 1. 
This may lead to some parts being null.
The parts should be in the order of occurrence in the input list, and parts occurring earlier should always have 
a size greater than or equal to parts occurring later.
Return an array of k parts.

Example:
Input: head = [1,2,3], k = 5
Output: [[1],[2],[3],[],[]]
Explanation:
The input list has been split into 5 consecutive parts as equal as possible, 
and earlier parts are a larger size than the later parts.
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
 * Problem: Split Linked List in Parts
 *
 * LeetCode 725: Split Linked List in Parts
 *
 * Split linked list into k consecutive parts as equal as possible.
 * Earlier parts should have size >= later parts.
 * Example: [1,2,3], k=5 -> [[1],[2],[3],[],[]]
 *
 * Time: O(n) - calculate length + split
 * Space: O(k) - result array
 */

    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        // Step 1: Calculate length of list
        int length = 0;
        ListNode* current = head;
        while (current) {
            length++;
            current = current->next;
        }
        
        // Step 2: Calculate sizes
        // baseSize = length/k, extraNodes = length%k
        // First 'extraNodes' parts have size (baseSize+1), rest have baseSize
        int baseSize = length / k;
        int extraNodes = length % k;
        
        vector<ListNode*> result(k, nullptr);
        current = head;
        
        // Step 3: Split list into k parts
        for (int i = 0; i < k && current; i++) {
            result[i] = current; // Head of current part
            
            // Calculate size: first 'extraNodes' parts get one extra node
            int partSize = baseSize + (i < extraNodes ? 1 : 0);
            
            // Move to end of current part
            for (int j = 1; j < partSize; j++) {
                current = current->next;
            }
            
            // Disconnect current part from rest
            ListNode* next = current->next;
            current->next = nullptr; // Terminate current part
            current = next; // Move to start of next part
        }
        
        return result;
    }
};

/*
Approach: Calculate Sizes and Split
- First, calculate the total length of the linked list
- Calculate base size (length / k) and number of extra nodes (length % k)
- First 'extraNodes' parts will have size (baseSize + 1), rest will have baseSize
- Traverse the list and split it into k parts
- Disconnect each part from the rest by setting next to nullptr

Time Complexity: O(n) - two passes: one to calculate length, one to split
Space Complexity: O(k) - result array of size k

Key Insight:
- If length = n and k parts, then:
  - baseSize = n / k
  - extraNodes = n % k
  - First (n % k) parts have size (baseSize + 1)
  - Remaining parts have size baseSize
- Earlier parts should be larger or equal to later parts
- Some parts may be null if k > length

Example Walkthrough:
Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
Length = 10, baseSize = 3, extraNodes = 1
Part 0: size 4 (baseSize + 1) -> [1,2,3,4]
Part 1: size 3 (baseSize) -> [5,6,7]
Part 2: size 3 (baseSize) -> [8,9,10]
Output: [[1,2,3,4], [5,6,7], [8,9,10]]
*/

