/*
LeetCode 382: Linked List Random Node

Given a singly linked list, return a random node's value from the linked list. 
Each node must have the same probability of being chosen.

Implement the Solution class:
- Solution(ListNode head) Initializes the object with the head of the singly-linked list head.
- int getRandom() Chooses a node randomly from the list and returns its value. 
  All the nodes of the list should be equally likely to be chosen.

Example:
Input
["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
[[[1, 2, 3]], [], [], [], [], []]
Output
[null, 1, 3, 2, 2, 3]

Explanation
Solution solution = new Solution([1, 2, 3]);
solution.getRandom(); // return 1
solution.getRandom(); // return 3
solution.getRandom(); // return 2
solution.getRandom(); // return 2
solution.getRandom(); // return 3
// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
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

// Approach 1: Reservoir Sampling (Space Efficient)
class Solution {
private:
    ListNode* head;
    
public:
    Solution(ListNode* head) {
        this->head = head;
    }

    // P(Node 1 stays) = 1 × (1 - 1/2) × (1 - 1/3) = 1 × 1/2 × 2/3 = 1/3
    // after 3rd iteration, P(Node 1 stays) = 1/3
    // after 4th iteration, P(Node 1 stays) = 1/4
    // after 5th iteration, P(Node 1 stays) = 1/5 and so on...
    
/*
 * Problem: Linked List Random Node
 *
 * LeetCode 382: Linked List Random Node
 *
 * Return a random node's value with equal probability for all nodes.
 * Use Reservoir Sampling algorithm for O(1) space.
 *
 * Time: O(n) for each getRandom() call
 * Space: O(1) - no extra space needed
 */

    int getRandom() {
        int result = 0;
        int count = 0;
        ListNode* current = head;
        
        // Reservoir Sampling Algorithm
        // For each node at position i, probability of selecting it is 1/i
        // This ensures each node has equal probability 1/n overall
        while (current != nullptr) {
            count++;
            // Probability of selecting current node is 1/count
            // rand() % count == 0 happens with probability 1/count
            if (rand() % count == 0) {
                result = current->val; // Update result
            }
            current = current->next;
        }
        
        return result;
    }
};

/*
Approach 1: Reservoir Sampling
- We traverse the list once
- For each node at position i, we have a 1/i probability of selecting it
- This ensures each node has equal probability (1/n) of being selected
- No extra space needed

Time Complexity: O(n) for each getRandom() call
Space Complexity: O(1)

Approach 2: Store in Vector (Alternative)
- Store all values in a vector during initialization
- Use rand() to get random index
- Faster getRandom() but uses O(n) space

class Solution {
private:
    vector<int> values;
    
public:
    Solution(ListNode* head) {
        while (head != nullptr) {
            values.push_back(head->val);
            head = head->next;
        }
    }
    
    int getRandom() {
        int randomIndex = rand() % values.size();
        return values[randomIndex];
    }
};

Time Complexity: O(n) for constructor, O(1) for getRandom()
Space Complexity: O(n)
*/

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

