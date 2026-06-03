/*
GeeksforGeeks: Find Sum Pairs Across Two BSTs
Difficulty: Easy

Problem:
You are given the roots of two BSTs, root1 and root2, and an integer x, returns the count of all pairs of (a, b), where a belongs to one BST and b belongs to another BST, such that a + b = x.

Examples:
Input: root1 = [2, 1, 3], root2 = [5, 4, 6], x = 6
Output: 2
Explanation: The pairs are: (2, 4) and (1, 5) whose sum is equal to x.

Input: root1 = [7, 5, 10, 1], root2 = [2, N, 6], x = 9
Output: 1
Explanation: The pair is: (7, 2)

Core Idea:
For every node value 'a' in BST1, we need to find if (x - a) exists in BST2.
Using a HashSet gives O(1) lookup. For every node in BST1, we can directly check whether its complement exists in BST2.
This approach is much easier to implement and reason about compared to the two-stack or two-pointer approach, while still maintaining an optimal Time Complexity.

Approach (HashSet - Optimal & Easy):
1. Traverse BST2 and store all its node values in a hash set.
2. Traverse BST1.
3. For each node value 'a' in BST1:
      if (x - a) exists in the hash set:
          increment the count
4. Return the count.

Time Complexity: O(N + M) where N and M are the number of nodes in root1 and root2 respectively. We visit each node once.
Space Complexity: O(M) to store the values of the second BST in the hash set, plus recursion stack space.

GFG Link: https://www.geeksforgeeks.org/problems/brothers-from-different-root/1
*/

#include <iostream>
#include <unordered_set>

using namespace std;

// Definition for a binary tree node.
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    void storeBST2(Node* root, unordered_set<int>& st) {
        if (!root) return;

        st.insert(root->data);

        storeBST2(root->left, st);
        storeBST2(root->right, st);
    }

    void countPairsBST1(Node* root, unordered_set<int>& st, int x, int& count) {
        if (!root) return;

        if (st.count(x - root->data))
            count++;

        countPairsBST1(root->left, st, x, count);
        countPairsBST1(root->right, st, x, count);
    }

    int countPairs(Node* root1, Node* root2, int x) {
        unordered_set<int> st;

        storeBST2(root2, st);

        int count = 0;
        countPairsBST1(root1, st, x, count);

        return count;
    }
};

/*
Dry Run — Example 1:
BST1: 2 1 3
BST2: 5 4 6
x = 6

1. storeBST2: 
   Traverses BST2 and inserts all its values into the set.
   Set = {4, 5, 6}

2. countPairsBST1:
   Traverses BST1 and checks if (x - root->data) exists in the set.
   
   Node 2:
   need = 6 - 2 = 4 → found in set
   count = 1

   Node 1:
   need = 6 - 1 = 5 → found in set
   count = 2

   Node 3:
   need = 6 - 3 = 3 → not found

Final count = 2.
Output: 2
*/
