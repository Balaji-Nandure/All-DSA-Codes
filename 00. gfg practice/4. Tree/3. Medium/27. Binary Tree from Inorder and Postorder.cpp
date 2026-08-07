/*
    Problem Name: Binary Tree from Inorder and Postorder
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays representing the inorder and postorder traversals of a binary tree,
    construct the binary tree and return its root.
    Note: All values are unique.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. Each node visited once, O(1) lookups.
    Space Complexity: O(N), for the hash map and recursion stack.

    Love Babbar Style Approach:
    This is the MIRROR of Problem #10 (Inorder & Preorder)!

    In Preorder (Node-Left-Right), the FIRST element is the root.
    In Postorder (Left-Right-Node), the LAST element is the root!

    Key differences from the Preorder version:
    1. We traverse Postorder from RIGHT to LEFT (decrementing postIndex).
    2. We build the RIGHT subtree FIRST, then the LEFT subtree!
       WHY? Because in postorder [Left, Right, Node], going backwards gives us
       [Node, Right, Left]. So after the root, the NEXT element (going backward)
       belongs to the RIGHT subtree, not the left!

    CRITICAL RULE: Pass `postIndex` by REFERENCE (int&) so it decrements globally
    across all recursive branches — same trick as the preorder version!

    Algorithm:
    1. Build a HashMap: inorder value → index (for O(1) position lookup).
    2. Start postIndex at n-1 (last element = root).
    3. Recursive solve:
       a) postorder[postIndex--] is the current root.
       b) Find its position in inorder → split into left and right subtrees.
       c) Build RIGHT subtree first (postIndex is going backward!).
       d) Build LEFT subtree second.

    Dry Run:
    inorder  = [4, 8, 2, 5, 1, 6, 3, 7]
    postorder = [8, 4, 5, 2, 6, 7, 3, 1]
    Map: {4:0, 8:1, 2:2, 5:3, 1:4, 6:5, 3:6, 7:7}

    - solve(inStart=0, inEnd=7, postIndex=7)
      - postIndex=7 → val=1. Root is 1! postIndex=6.
      - pos = map[1] = 4.
      - RIGHT first: solve(inStart=5, inEnd=7, postIndex=6)
        - postIndex=6 → val=3. Root is 3! postIndex=5.
        - pos = map[3] = 6.
        - RIGHT: solve(7, 7) → postIndex=5, val=7 → Node(7). postIndex=4.
        - LEFT:  solve(5, 5) → postIndex=4, val=6 → Node(6). postIndex=3.
        - returns Node(3) with left=6, right=7
      - LEFT second: solve(inStart=0, inEnd=3, postIndex=3)
        - postIndex=3 → val=2. Root is 2! postIndex=2.
        - pos = map[2] = 2.
        - RIGHT: solve(3, 3) → postIndex=2, val=5 → Node(5). postIndex=1.
        - LEFT: solve(0, 1) → postIndex=1, val=4 → Node(4).
          - pos=0. RIGHT: solve(1,1) → val=8 → Node(8). LEFT: solve(0,-1) → NULL.
          - Node(4) with right=8
        - returns Node(2) with left=4(right=8), right=5
      - Returns Node(1) with left=2, right=3. Tree built! ✓
*/

#include <iostream>
#include <vector>
#include <unordered_map>

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
    Node* solve(vector<int>& inorder, vector<int>& postorder, int& postIndex, int inStart, int inEnd, unordered_map<int, int>& nodeToIndex) {
        // Base Case: If start > end, no elements to process
        if (inStart > inEnd) {
            return NULL;
        }

        // 1. Get the current root from the END of postorder (going backward!)
        int element = postorder[postIndex--];
        Node* root = new Node(element);

        // 2. Find position in inorder using our O(1) map
        int pos = nodeToIndex[element];

        // 3. Build RIGHT subtree FIRST, then LEFT!
        // NOTE: We MUST build right first because postorder backwards goes Root → Right → Left
        root->right = solve(inorder, postorder, postIndex, pos + 1, inEnd, nodeToIndex);
        root->left  = solve(inorder, postorder, postIndex, inStart, pos - 1, nodeToIndex);

        return root;
    }

public:
    // GFG Signature
    Node* buildTree(vector<int>& inorder, vector<int>& postorder) {
        // Map to quickly find the exact index of any element in the inorder array in O(1)
        unordered_map<int, int> nodeToIndex;

        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            nodeToIndex[inorder[i]] = i;
        }

        // Start from the LAST element of postorder (it's the root!)
        int postIndex = n - 1;
        return solve(inorder, postorder, postIndex, 0, n - 1, nodeToIndex);
    }
};

// Helper function to print Inorder traversal to verify tree construction
void printInorder(Node* root) {
    if (root == NULL) return;
    printInorder(root->left);
    cout << root->data << " ";
    printInorder(root->right);
}

// Helper function to print Preorder traversal to verify tree construction
void printPreorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    printPreorder(root->left);
    printPreorder(root->right);
}

int main() {
    // Example 1:
    // inorder  = [4, 8, 2, 5, 1, 6, 3, 7]
    // postorder = [8, 4, 5, 2, 6, 7, 3, 1]
    // Expected tree: [1, 2, 3, 4, 5, 6, 7, N, 8]
    //           1
    //          / \
    //         2   3
    //        / \ / \
    //       4  5 6  7
    //        \
    //         8

    vector<int> inorder1  = {4, 8, 2, 5, 1, 6, 3, 7};
    vector<int> postorder1 = {8, 4, 5, 2, 6, 7, 3, 1};

    Solution ob;
    Node* root1 = ob.buildTree(inorder1, postorder1);

    // Verify: Preorder should be: 1 2 4 8 5 3 6 7
    cout << "Preorder (Example 1): ";
    printPreorder(root1);
    cout << "\n";

    // Verify: Inorder should match input: 4 8 2 5 1 6 3 7
    cout << "Inorder  (Example 1): ";
    printInorder(root1);
    cout << "\n\n";

    // Example 2:
    // inorder  = [9, 5, 2, 3, 4]
    // postorder = [5, 9, 3, 4, 2]
    // Expected tree:
    //       2
    //      / \
    //     9   4
    //      \ /
    //      5 3

    vector<int> inorder2  = {9, 5, 2, 3, 4};
    vector<int> postorder2 = {5, 9, 3, 4, 2};

    Node* root2 = ob.buildTree(inorder2, postorder2);

    // Verify: Preorder should be: 2 9 5 4 3
    cout << "Preorder (Example 2): ";
    printPreorder(root2);
    cout << "\n";

    // Verify: Inorder should match input: 9 5 2 3 4
    cout << "Inorder  (Example 2): ";
    printInorder(root2);
    cout << "\n";

    return 0;
}
