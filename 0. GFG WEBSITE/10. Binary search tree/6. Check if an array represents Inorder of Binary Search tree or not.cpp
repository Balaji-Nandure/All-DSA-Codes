/*
Problem:
Check if an Array Represents Inorder Traversal of a Binary Search Tree

Given an array arr[] of size N, check whether it can represent
the inorder traversal of a Binary Search Tree (BST).

Rules:
- BST property: left < root < right
- Inorder traversal of BST always produces a sorted sequence.
- Duplicate values are NOT allowed.

Example 1:
Input:
arr = [2, 4, 5, 8, 10]

Output:
true

Example 2:
Input:
arr = [7, 4, 6, 5]

Output:
false

Approach (Optimized):
- Inorder traversal of a BST must be in strictly increasing order.
- Traverse the array and check if it is strictly sorted.
- If any adjacent element violates increasing order, return false.

GeeksforGeeks:
https://www.geeksforgeeks.org/check-if-an-array-represents-inorder-traversal-of-a-bst/

LeetCode:
No direct equivalent problem.

Time Complexity:
O(N)

Space Complexity:
O(1)
*/

class Solution {
    public:
        bool isInorderBST(vector<int>& arr) {
    
            for (int i = 1; i < arr.size(); i++) {
                if (arr[i] <= arr[i - 1]) {
                    return false;
                }
            }
    
            return true;
        }
    };
    