/*
 * Problem: Does array represent Heap
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/does-array-represent-heap/0
 * 
 * Given an array arr of size n, the task is to check if the given array can be 
 * a level order representation of a Max Heap.
 * 
 * Examples:
 * Input:
 * n = 6
 * arr[] = {90, 15, 10, 7, 12, 2}
 * Output: 1
 * Explanation: The given array represents below tree
 *        90
 *      /    \
 *    15      10
 *   /  \     /
 * 7    12  2
 * The tree follows max-heap property as every node is greater than all of its descendants.
 * 
 * Input:  
 * n = 6
 * arr[] = {9, 15, 10, 7, 12, 11}
 * Output: 0
 * Explanation: The given array represents below tree
 *        9
 *      /    \
 *    15      10
 *   /  \     /
 * 7    12  11
 * The tree doesn't follows max-heap property 9 is smaller than 15 and 10, and 10 is smaller than 11.
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Check max-heap property for all non-leaf nodes
 * - For each node i (0 to (n-2)/2), verify it's greater than its children
 * - Left child: 2*i + 1, right child: 2*i + 2
 * - If any child exists and parent is smaller, heap property violated
 * - Only need to check non-leaf nodes as leaves have no children
 * - Return true if all nodes satisfy max-heap property
 * 
 * Time: O(n) - check each non-leaf node and its children
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMaxHeap(int arr[], int n) {
        // Only need to check non-leaf nodes
        for (int i = 0; i <= (n - 2) / 2; i++) {
            
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            
            if (left < n && arr[i] < arr[left])
                return false;
            
            if (right < n && arr[i] < arr[right])
                return false;
        }
        
        return true;
    }
};
