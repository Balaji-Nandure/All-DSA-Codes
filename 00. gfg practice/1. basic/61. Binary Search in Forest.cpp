/*
 * Problem: Binary Search in Forest
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/binary-search-in-forest/1
 * 
 * There are n trees in a forest. The heights of the trees is stored in array 
 * tree[], where tree[i] denotes the height of the ith tree in the forest. 
 * If the ith tree is cut at a height H, then the wood collected is tree[i] - H, 
 * provided tree[i] > H. If the total woods that needs to be collected is exactly 
 * equal to k, find the height H at which every tree should be cut. If it is not 
 * possible then return -1 else return H.
 * 
 * Examples:
 * Input: n = 5, k = 4, tree[] = {2, 3, 6, 2, 4}
 * Output: 3
 * Explanation: Wood collected by cutting trees at height 3 = 
 * 0 + 0 + (6-3) + 0 + (4-3) = 4
 * 
 * Input: n = 6, k = 8, tree[] = {1, 7, 6, 3, 4, 7}
 * Output: 4
 * Explanation: Wood collected by cutting trees at height 4 = 
 * 0+(7-4)+(6-4)+0+0+(7-4) = 8
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^4
 * 1 ≤ tree[i] ≤ 10^3
 * 1 ≤ k ≤ 10^7
 * 
 * Expected Time Complexity: O(n log h)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use binary search on the cutting height H
 * - For each height H, calculate total wood collected
 * - If wood collected > k, increase H (cut higher)
 * - If wood collected < k, decrease H (cut lower)
 * - If wood collected = k, return H
 * - Search range: low = 0, high = max(tree[])
 * - Helper function to calculate wood at given height
 * 
 * Time: O(n log h) - binary search on height range, O(n) to calculate wood
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    
    // Helper function to calculate total wood collected at height H
    long long calculateWood(vector<int>& tree, int H) {
        long long totalWood = 0;
        
        for(int i = 0; i < tree.size(); i++) {
            if(tree[i] > H) {
                totalWood += (tree[i] - H);
            }
        }
        
        return totalWood;
    }
    
    int find_height(vector<int> tree, int n, int k) {
        
        // Binary search bounds
        int low = 0;
        int high = *max_element(tree.begin(), tree.end());
        
        int result = -1;
        
        while(low <= high) {
            
            int mid = low + (high - low) / 2;
            long long wood = calculateWood(tree, mid);
            
            if(wood == k) {
                result = mid;
                break;
            }
            else if(wood > k) {
                // Too much wood, need to cut higher
                low = mid + 1;
            }
            else {
                // Too little wood, need to cut lower
                high = mid - 1;
            }
        }
        
        return result;
    }
};