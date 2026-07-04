/*
    Problem Name: Sum Tree
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a Binary Tree. Check for the Sum Tree for every node except the leaf node. 
    Return true if it is a Sum Tree otherwise, return false.
    A SumTree is a Binary Tree where the value of a node is equal to the sum of the nodes 
    present in its left subtree and right subtree.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We traverse every node exactly once.
    Space Complexity: O(H), where H is the height of the tree, for the recursion stack.

    Love Babbar Style Approach:
    1. A naive approach would be to calculate the sum of the left subtree and right subtree for every node separately, leading to O(N^2) time.
    2. We can drastically optimize this to O(N) by calculating the sum bottom-up. 
    3. We write a single recursive function `getSum(Node* root)`. 
       - If the tree is empty, its sum is 0.
       - If it is a leaf node, it is valid by default, so its sum is simply its own value `root->data`.
    4. For any other node, we recursively get the sum of its left subtree (`ls`) and right subtree (`rs`).
    5. Check the condition: Is `root->data == ls + rs`?
       - If YES: return the total sum of this tree, which is `root->data + ls + rs` (or `2 * root->data`).
       - If NO: return `-1` to indicate this is NOT a sum tree.
    6. Since node values are strictly positive (`node->data >= 1`), a valid sum will never be `-1`. 
       If at any point a subtree returns `-1`, we instantly propagate `-1` upwards to fail the whole tree.
    7. Finally, if the root returns anything other than `-1`, it's a valid Sum Tree!

    Dry Run:
    Tree:
           10
         /    \
       20      30
      /  \
     10  10

    - getSum(10 leaf): returns 10
    - getSum(10 leaf): returns 10
    - getSum(20): ls=10, rs=10. root(20) == ls(10) + rs(10)? YES! returns 20 + 10 + 10 = 40.
    - getSum(30 leaf): returns 30
    - getSum(10 root): ls=40, rs=30. root(10) == ls(40) + rs(30)? NO! 10 != 70. returns -1.
    
    Result: -1 -> false. Matches perfectly!
*/

#include <iostream>

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
private:
    int getSum(Node* root) {
        // Base case 1: Empty tree sum is 0
        if (root == NULL) {
            return 0;
        }
        
        // Base case 2: Leaf node is always a valid sum tree, sum is its own value
        if (root->left == NULL && root->right == NULL) {
            return root->data;
        }
        
        // Recursively get the sum of left and right subtrees
        int ls = getSum(root->left);
        int rs = getSum(root->right);
        
        // If any subtree violates the rule, propagate the failure (-1) upwards
        if (ls == -1 || rs == -1) {
            return -1;
        }
        
        // Check if the current node is a valid Sum Tree
        if (root->data == ls + rs) {
            // Return the total sum of this entire subtree to pass to its parent
            return root->data + ls + rs; 
        } else {
            return -1; // Not a sum tree!
        }
    }

public:
    bool isSumTree(Node* root) {
        // If the recursive function returns -1, it's NOT a Sum Tree
        return getSum(root) != -1;
    }
};

int main() {
    // Example test case 
    //        3
    //      /   \ 
    //     1     2   
    
    Node* root = new Node(3);
    root->left = new Node(1);
    root->right = new Node(2);
    
    Solution ob;
    if (ob.isSumTree(root)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
    
    return 0;
}
