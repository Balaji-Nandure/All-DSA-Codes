/*
    Problem Name: Construct Tree from Inorder & Preorder
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given two arrays representing the inorder and preorder traversals of a binary tree, 
    your task is to construct the binary tree and return its root.
    Note: The inorder and preorder traversals contain unique values.

    Expected Complexities:
    Time Complexity: O(N), where N is the number of nodes. We visit each node once and lookups take O(1) time.
    Space Complexity: O(N), for the hash map to store inorder indices and the recursion stack.

    Love Babbar Style Approach:
    1. In Preorder Traversal (Node-Left-Right), the VERY FIRST element is ALWAYS the Root of the tree!
    2. We take this root element and search for it in the Inorder Traversal (Left-Node-Right).
    3. Once we find the root in the Inorder array (let's say at index `pos`), everything to the LEFT of `pos` strictly belongs to the Left Subtree, and everything to the RIGHT strictly belongs to the Right Subtree!
    4. We can do this recursively! However, searching for `pos` linearly every time makes it O(N^2).
    5. O(N) Optimization Trick: Before starting the recursion, we just dump all elements of the `inorder` array into a Hash Map `nodeToIndex` (value -> index). Now finding `pos` is instant O(1)!
    6. CRITICAL RULE: We must pass our `preIndex` (which tracks our position in the preorder array) BY REFERENCE `int& preIndex` so that it increments globally across all recursive branches!

    Dry Run:
    inorder = [3, 1, 4, 0, 5, 2]
    preorder = [0, 1, 3, 4, 2, 5]

    - Map: {3:0, 1:1, 4:2, 0:3, 5:4, 2:5}
    - solve(inStart=0, inEnd=5, preIndex=0)
      - preIndex=0 -> val=0. Root is 0! Increment preIndex to 1.
      - pos = map[0] = 3.
      - left = solve(inStart=0, inEnd=2, preIndex=1)
        - preIndex=1 -> val=1. Root is 1! preIndex=2.
        - pos = map[1] = 1.
        - left = solve(0, 0) -> preIndex=2, val=3 -> pos=0. -> returns Node(3)
        - right = solve(2, 2) -> preIndex=3, val=4 -> pos=2. -> returns Node(4)
        - returns Node(1)
      - right = solve(inStart=4, inEnd=5, preIndex=4)
        - preIndex=4 -> val=2. Root is 2! preIndex=5.
        - pos = map[2] = 5.
        - left = solve(4, 4) -> preIndex=5, val=5 -> pos=4. returns Node(5)
        - right = solve(6, 5) -> returns NULL.
        - returns Node(2)
      - Returns Node(0).
      
    Tree constructed correctly!
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
    Node* solve(vector<int>& inorder, vector<int>& preorder, int& preIndex, int inStart, int inEnd, unordered_map<int, int>& nodeToIndex) {
        // Base Case: If the start index is greater than the end index, there are no elements to process
        if (inStart > inEnd) {
            return NULL;
        }
        
        // 1. Get the current root node from the preorder array and magically increment preIndex!
        int element = preorder[preIndex++];
        Node* root = new Node(element);
        
        // 2. Find the exact position of this root element in the inorder array using our O(1) map
        int pos = nodeToIndex[element];
        
        // 3. Recursively build the Left and Right subtrees!
        // NOTE: We MUST build the left subtree first because preorder ALWAYS goes Root -> Left -> Right
        root->left = solve(inorder, preorder, preIndex, inStart, pos - 1, nodeToIndex);
        root->right = solve(inorder, preorder, preIndex, pos + 1, inEnd, nodeToIndex);
        
        return root;
    }

public:
    Node* buildTree(vector<int> &inorder, vector<int> &preorder) {
        // Map to quickly find the exact index of any element in the inorder array in O(1) time
        unordered_map<int, int> nodeToIndex;
        
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            nodeToIndex[inorder[i]] = i;
        }
        
        // Start recursive construction from the 0th index of preorder
        int preIndex = 0;
        return solve(inorder, preorder, preIndex, 0, n - 1, nodeToIndex);
    }
};

// Helper function to print Postorder traversal to verify tree construction visually
void printPostOrder(Node* root) {
    if (root == NULL) return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    cout << root->data << " ";
}

int main() {
    // Example test case 
    // inorder[] = [3, 1, 4, 0, 5, 2]
    // preorder[] = [0, 1, 3, 4, 2, 5]
    
    vector<int> inorder = {3, 1, 4, 0, 5, 2};
    vector<int> preorder = {0, 1, 3, 4, 2, 5};
    
    Solution ob;
    Node* root = ob.buildTree(inorder, preorder);
    
    // Output should be Postorder traversal to verify
    // For this exact tree, postorder is: 3 4 1 5 2 0
    printPostOrder(root);
    cout << "\n";
    
    return 0;
}
