/*
GeeksforGeeks: BST Keys in a Range
Difficulty: Easy

Problem:
Given a BST and range [low, high],
return all nodes lying in this range
in sorted order.

Example:

        17
      /    \
     4      18
    / \
   2   9

low = 4
high = 24

Output:
4 9 17 18

Core BST Property:
left  < root
right >= root

Important Optimization:
1. If root->data > low
   then only LEFT subtree may contain answers

2. If root->data < high
   then only RIGHT subtree may contain answers

This avoids unnecessary traversal.

Approach:
Use inorder traversal with pruning.

Why inorder?
Inorder of BST gives sorted order.

Time Complexity:
O(N) worst case

Space Complexity:
O(H)

(H = height of tree)

GFG Link:
https://www.geeksforgeeks.org/problems/print-bst-elements-in-given-range/1
*/

class Solution {
public:

    void solve(Node* root,
               int low,
               int high,
               vector<int>& ans){

        if(!root)
            return;

        // left subtree may contain valid values
        if(root->data > low)
            solve(root->left, low, high, ans);

        // current node inside range
        if(root->data >= low && root->data <= high)
            ans.push_back(root->data);

        // right subtree may contain valid values
        if(root->data <= high)
            solve(root->right, low, high, ans);
    }

    vector<int> printNearNodes(Node *root, int low, int high) {

        vector<int> ans;

        solve(root, low, high, ans);

        return ans;
    }
};

/*
Dry Run:

        17
      /    \
     4      18
    / \
   2   9

Range = [4,24]

2 -> skipped
4 -> added
9 -> added
17 -> added
18 -> added

Answer:
4 9 17 18

Final Summary:
1. Use inorder traversal
2. Add node if inside range
3. Prune unnecessary BST branches
*/