/*
LeetCode 1669: Merge In Between Linked Lists

You are given two linked lists: list1 and list2 of sizes n and m respectively.
Remove list1's nodes from the ath node to the bth node (0-indexed), and put list2 in their place.
Build the result list and return its head.

Example:
Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Output: [0,1,2,1000000,1000001,1000002,5]
Explanation: We remove the nodes 3 and 4 and put the entire list2 in their place.
The blue edges and nodes in the above figure indicate the result.
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
 * Problem: Merge In Between Linked Lists
 *
 * LeetCode 1669: Merge In Between Linked Lists
 *
 * Remove nodes from index a to b in list1, replace with entire list2.
 * Example: list1=[0,1,2,3,4,5], a=3, b=4, list2=[1000000,1000001,1000002]
 * -> [0,1,2,1000000,1000001,1000002,5]
 *
 * Time: O(n + m) - traverse list1 to find positions, list2 to find tail
 * Space: O(1)
 */

    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        // Find node before position a (prevA) and node after position b (nodeB)
        ListNode* prevA = nullptr;
        ListNode* nodeB = list1;
        // Traverse to position b+1 to find both nodes
        for (int i = 0; i <= b; ++i) {
            if (i == a - 1) {
                prevA = nodeB; // Node before position a
            }
            nodeB = nodeB->next; // Continue to position b+1
        }

        // Connect prevA to list2 head (removes nodes from a to b)
        prevA->next = list2;

        // Find tail of list2
        ListNode* list2Tail = list2;
        while (list2Tail->next != nullptr) {
            list2Tail = list2Tail->next;
        }

        // Connect list2 tail to nodeB (node after position b)
        list2Tail->next = nodeB;

        return list1;
    }
};

/*
Approach: Find Connection Points and Merge
- Find the node before position a (prevA) - this will connect to list2
- Find the node after position b (nodeB) - list2 will connect to this
- Connect prevA->next to list2
- Find the tail of list2 and connect it to nodeB

Time Complexity: O(n + m) - traverse list1 to find positions, traverse list2 to find tail
Space Complexity: O(1) - only using constant extra space

Key Insight:
- We need to remove nodes from index a to b (inclusive) from list1
- Replace them with the entire list2
- The connection points are:
  - Node before position a connects to head of list2
  - Tail of list2 connects to node after position b

Example Walkthrough:
Input: list1 = [0,1,2,3,4,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
Step 1: Find prevA (node at index 2, value 2)
Step 2: Find nodeB (node at index 5, value 5)
Step 3: Connect 2->next to list2 head (1000000)
Step 4: Find list2 tail (1000002) and connect to nodeB (5)
Result: [0,1,2,1000000,1000001,1000002,5]
*/

