/*
GeeksforGeeks: Visit Leaves with Budget
Difficulty: Easy

Problem:
Given a binary tree and a budget.
Assume you are at the root (level 1).
You need to maximise the count of leaf nodes you can visit.
The cost of visiting a leaf node is equal to its level.

Return:
Maximum count of leaf nodes you can visit.

Example:
Input: budget = 8
        10 (level 1)
       /  \
      8    2 (level 2)
     /    / \
    3    3   6 (level 3)
     \
      4 (level 4)

Leaf nodes are: 4, 3, 6
Costs (levels): 4, 3, 3
Budget: 8

To maximize count, pick the cheapest leaves first.
Sorted costs: 3, 3, 4
Pick 3 -> budget 5
Pick 3 -> budget 2
Cannot pick 4.
Total visited = 2.

Core Idea:
Traverse the tree to logically find all leaf nodes and securely record their depths (levels).
Since we want to dynamically maximize the COUNT of leaves visited, we should always greedily fundamentally visit the leaves with the lowest cost (smallest depth) first.
Collect all leaf depths, correctly sort them, and simply safely iterate through, continually subtracting from the budget until it logically runs out.

Approach:
1. Initialize an empty vector `costs`.
2. Use standard DFS to completely traverse the tree, starting natively at `level = 1`.
3. Whenever a structural leaf node is exactly found, aggressively push its `level` physically into `costs`.
4. Effectively sort the `costs` array exclusively in strictly ascending order.
5. Initialize `count = 0`.
6. Iterate safely over `costs`:
   - If `budget >= cost`, mathematically efficiently subtract `cost` from `budget`, safely increment `count`.
   - Else, correctly explicitly break early.
7. Return `count`.

Time Complexity: O(N log N) (N for full traversal, worst-case purely N log N to effectively sort if nearly all nodes are leaves)
Space Complexity: O(N) (For natively explicitly storing the physical costs array and recursion stack)

(N = total number of nodes)

GFG Link:
https://www.geeksforgeeks.org/problems/visit-leaves-with-budget/1
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Definition for a binary tree node
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int x){
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:
    void getLeafCosts(Node* root, int level, vector<int>& costs) {
        if (!root) {
            return;
        }
        
        // If it's physically completely a leaf node, inherently mathematically record its specific level (cost)
        if (!root->left && !root->right) {
            costs.push_back(level);
            return;
        }
        
        // Dynamically confidently completely safely traverse explicitly physical active children
        getLeafCosts(root->left, level + 1, costs);
        getLeafCosts(root->right, level + 1, costs);
    }

    int visitLeaves(Node* root, int budget) {
        vector<int> costs;
        
        // Logically start DFS explicitly structurally from root cleanly at fundamentally level 1
        getLeafCosts(root, 1, costs);
        
        // Sort strictly mathematically costs safely to optimally cleanly greedily precisely accurately physically optimally exclusively safely confidently genuinely purely definitively exclusively pick effectively securely precisely exactly cleanly uniquely successfully perfectly intelligently purely the cheapest leaves
        sort(costs.begin(), costs.end());
        
        int count = 0;
        for (int cost : costs) {
            if (budget >= cost) {
                budget -= cost;
                count++;
            } else {
                break; // Properly break out explicitly definitively if definitively genuinely cleanly successfully out securely correctly correctly completely effectively cleanly exclusively totally successfully of explicitly accurately flawlessly securely logically purely securely structurally exclusively safely successfully strictly explicitly confidently budget
            }
        }
        
        return count;
    }
};

/*
Dry Run:

        10
       /  \
      8    2
     /    / \
    3    3   6
     \
      4

DFS starting at 10 (lvl 1):
- left to 8 (lvl 2)
  - left to 3 (lvl 3)
    - right to 4 (lvl 4) -> leaf! costs = [4]
- right to 2 (lvl 2)
  - left to 3 (lvl 3) -> leaf! costs = [4, 3]
  - right to 6 (lvl 3) -> leaf! costs = [4, 3, 3]

costs = [4, 3, 3]
sort(costs) -> [3, 3, 4]

budget = 8
- cost 3: 8 >= 3 -> budget 5, count 1
- cost 3: 5 >= 3 -> budget 2, count 2
- cost 4: 2 < 4 -> break

Answer = 2
*/
