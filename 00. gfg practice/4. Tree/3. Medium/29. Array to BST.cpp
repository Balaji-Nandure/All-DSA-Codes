/*
    Problem Name: Array to BST
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a sorted array arr[]. Convert it into a Height Balanced Binary Search Tree (BST)
    and return the root of the BST.

    Height-balanced BST means a binary tree in which the depth of the left subtree
    and the right subtree of every node never differ by more than 1.

    Note: You can return any valid BST, the driver code will check if it is a Height-balanced BST.

    Examples:
    Input: arr[] = [10, 20, 30]
    Output: true (Root = 20, Left = 10, Right = 30)

    Input: arr[] = [1, 5, 9, 14, 23, 27]
    Output: true (Root = 9 or 14, Left and Right balanced BSTs)

    Constraints:
    1 <= arr.size() <= 10^5
    1 <= arr[i] <= 10^5

    Expected Complexities:
    Time Complexity: O(N), where N is the number of elements in the array. Each element is processed once.
    Space Complexity: O(log N), for the recursion call stack (height of a balanced BST is log N).

    Love Babbar Style Approach:
    Divide & Conquer (Binary Search Approach):
    
    1. INTUITION:
       - Since the given array is already SORTED, the middle element `arr[mid]` is the perfect
         candidate for the ROOT of the current subtree.
       - Why? Choosing the middle element splits the array into two roughly equal halves:
         * Left half  --> elements smaller than root  --> forms LEFT subtree
         * Right half --> elements larger than root   --> forms RIGHT subtree
       - This guarantees that the height difference between left and right subtrees is at most 1!

    2. ALGORITHM (Recursive `solve` function):
       - Base Case: If `start > end`, no elements remain in this range, return NULL.
       - Calculate `mid = start + (end - start) / 2`.
       - Create a new Node with value `arr[mid]`.
       - Recursively build left subtree using left range: `[start, mid - 1]`.
       - Recursively build right subtree using right range: `[mid + 1, end]`.
       - Return the created root node.

    Dry Run:
    arr[] = [1, 5, 9, 14, 23, 27], start = 0, end = 5

    - Call solve(arr, 0, 5):
      mid = (0 + 5) / 2 = 2 -> Node(arr[2]) = Node(9)
      - Left subtree  --> solve(arr, 0, 1):
        mid = (0 + 1) / 2 = 0 -> Node(arr[0]) = Node(1)
        - Left  --> solve(arr, 0, -1) => NULL
        - Right --> solve(arr, 1, 1)  => Node(5)
      - Right subtree --> solve(arr, 3, 5):
        mid = (3 + 5) / 2 = 4 -> Node(arr[4]) = Node(23)
        - Left  --> solve(arr, 3, 3)  => Node(14)
        - Right --> solve(arr, 5, 5)  => Node(27)

    Constructed Balanced BST:
               9
             /   \
            1     23
             \   /  \
              5 14   27

    Height of Left Subtree = 2, Height of Right Subtree = 2 -> Difference = 0 (Height Balanced ✓)
    Inorder Traversal: 1, 5, 9, 14, 23, 27 (Valid BST ✓)
*/

#include <iostream>
#include <vector>

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
    // Helper function to build height-balanced BST recursively
    Node* solve(vector<int>& arr, int start, int end) {
        // Base Case: Invalid range
        if (start > end) {
            return NULL;
        }

        // Pick middle element to ensure balance
        int mid = start + (end - start) / 2;

        // Create root node with middle element
        Node* root = new Node(arr[mid]);

        // Recursively construct left and right subtrees
        root->left = solve(arr, start, mid - 1);
        root->right = solve(arr, mid + 1, end);

        return root;
    }

public:
    // GFG Signature
    Node* sortedArrayToBST(vector<int>& arr) {
        int n = arr.size();
        return solve(arr, 0, n - 1);
    }
};

int main() {
    Solution ob;

    // Example 1:
    // Input: arr[] = [10, 20, 30]
    vector<int> arr1 = {10, 20, 30};
    Node* root1 = ob.sortedArrayToBST(arr1);
    cout << "Example 1 Root: " << (root1 ? root1->data : -1) << "\n";

    // Example 2:
    // Input: arr[] = [1, 5, 9, 14, 23, 27]
    vector<int> arr2 = {1, 5, 9, 14, 23, 27};
    Node* root2 = ob.sortedArrayToBST(arr2);
    cout << "Example 2 Root: " << (root2 ? root2->data : -1) << "\n";

    return 0;
}
