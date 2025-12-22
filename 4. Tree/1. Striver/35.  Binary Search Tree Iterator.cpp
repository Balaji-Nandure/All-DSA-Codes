/*
 * Problem: Binary Search Tree Iterator
 *
 * LeetCode 173: Binary Search Tree Iterator
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/implement-iterator-for-bst/1
 *
 * Implement the BSTIterator class that represents an iterator over the in-order
 * traversal of a binary search tree (BST):
 *
 * - BSTIterator(TreeNode root) Initializes an object of the BSTIterator class.
 *   The root of the BST is given as part of the constructor. The pointer should
 *   be initialized to a non-existent number smaller than any element in the BST.
 *
 * - boolean hasNext() Returns true if there exists a next number in the traversal,
 *   otherwise returns false.
 *
 * - int next() Moves the pointer to the right, then returns the next smallest
 *   number in the BST.
 *
 * Notice that by initializing the pointer to a non-existent smallest number,
 * the first call to next() will return the smallest element in the BST.
 *
 * You may assume that next() calls will always be valid. That is, there will be
 * at least a next number in the in-order traversal when next() is called.
 *
 * Example:
 * Input:
 * ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
 * [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
 *
 * Output:
 * [null, 3, 7, true, 9, true, 15, true, 20, false]
 *
 * Explanation:
 *       7
 *      / \
 *     3   15
 *        /  \
 *       9    20
 *
 * BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
 * bSTIterator.next();    // return 3
 * bSTIterator.next();    // return 7
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 9
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 15
 * bSTIterator.hasNext(); // return True
 * bSTIterator.next();    // return 20
 * bSTIterator.hasNext(); // return False
 *
 * Approach 1: Controlled Inorder Traversal (Stack-based)
 * - Use a stack to simulate inorder traversal
 * - In constructor, push all left nodes from root
 * - next(): Pop from stack, push all left nodes of right child, return popped value
 * - hasNext(): Check if stack is not empty
 *
 * Approach 2: Flatten BST (Array-based)
 * - Store inorder traversal in array during construction
 * - Use pointer to track current position
 * - Simple but uses O(n) space upfront
 *
 * Time Complexity:
 * - Constructor: O(h) where h is height
 * - next(): O(1) amortized (each node pushed/popped once)
 * - hasNext(): O(1)
 *
 * Space Complexity: O(h) for stack-based approach
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

#include <stack>
using namespace std;

// Solution 1: Stack-based Iterator (Optimal - O(h) space)
class BSTIterator {
private:
    stack<TreeNode*> st;
    
    // Push all left nodes starting from given node
/*
 * Problem: Binary Search Tree Iterator
 *
 * LeetCode 173: Binary Search Tree Iterator
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/implement-iterator-for-bst/1
 *
 * Implement iterator for inorder traversal of BST.
 * next() returns next smallest element, hasNext() checks if more elements exist.
 *
 * Time: O(1) amortized for next(), O(1) for hasNext()
 * Space: O(h) - stack height
 */

    // Push all left nodes from given node (inorder: go left first)
    void pushAllLeft(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        // Initialize: push all left nodes from root (smallest elements)
        pushAllLeft(root);
    }
    
    int next() {
        // Pop top node (next smallest in inorder)
        TreeNode* node = st.top();
        st.pop();
        
        // Push all left nodes of right subtree (next elements in inorder)
        pushAllLeft(node->right);
        
        return node->val;
    }
    
    bool hasNext() {
        // Stack not empty means more elements exist
        return !st.empty();
    }
};

// Solution 2: Array-based Iterator (Simple but O(n) space)
class BSTIteratorArray {
private:
    vector<int> inorder;
    int index;
    
    void inorderTraversal(TreeNode* root) {
        if (root == nullptr) return;
        inorderTraversal(root->left);
        inorder.push_back(root->val);
        inorderTraversal(root->right);
    }
    
public:
    BSTIteratorArray(TreeNode* root) {
        inorderTraversal(root);
        index = 0;
    }
    
    int next() {
        return inorder[index++];
    }
    
    bool hasNext() {
        return index < inorder.size();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

