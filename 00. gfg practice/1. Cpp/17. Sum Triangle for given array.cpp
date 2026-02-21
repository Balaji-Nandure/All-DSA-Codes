/*
 * Problem: Sum Triangle for given array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/sum-triangle-for-given-array/0
 * 
 * Given an array, write a program to construct a triangle where the last row contains elements 
 * of the given array, every element of the second last row contains the sum of the below two 
 * elements with modulo 10^9+7, and so on.
 * 
 * Examples:
 * Input: arr[] = [4, 7, 3, 6, 7]
 * Output: [81, 40, 41, 21, 19, 22, 11, 10, 9, 13, 4, 7, 3, 6, 7]
 * Explanation:
 *        81
 *      40  41
 *    21  19  22
 *  11  10   9   13
 * 4   7   3   6    7 
 * 
 * Input: arr[] = [1, 2, 4]
 * Output: [9, 3, 6, 1, 2, 4] 
 * Explanation:
 *    9
 *   3   6
 *  1  2  4
 * 
 * Constraints:
 * 1 <= arr.size() <= 10^3
 * 1 <= arr[i] <= 10^2
 * 
 * Expected Time Complexity: O(n^2)
 * Expected Auxiliary Space: O(n^2)
 * 
 * Approach:
 * - Start with the given array as the last row of the triangle
 * - Build the triangle from bottom to top
 * - For each level above, calculate sum of adjacent elements from the row below
 * - Apply modulo 10^9+7 to each sum
 * - Continue until we reach the top (single element)
 * - Finally, flatten the triangle from top to bottom into a single array
 * 
 * Time: O(n^2) - building triangle of size n + (n-1) + ... + 1 = O(n^2)
 * Space: O(n^2) - storing the entire triangle
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sumTriangle(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        int n = arr.size();
        
        // Build triangle from bottom to top
        vector<vector<int>> triangle;
        triangle.push_back(arr); // Last row
        
        // Build upper rows
        while (triangle.back().size() > 1) {
            vector<int> currentRow = triangle.back();
            vector<int> aboveRow;
            
            // Calculate sums of adjacent elements
            for (int i = 0; i < currentRow.size() - 1; i++) {
                long long sum = (long long)currentRow[i] + currentRow[i + 1];
                sum %= MOD;
                aboveRow.push_back((int)sum);
            }
            
            triangle.push_back(aboveRow);
        }
        
        // Flatten triangle from top to bottom
        vector<int> result;
        for (int i = triangle.size() - 1; i >= 0; i--) {
            for (int num : triangle[i]) {
                result.push_back(num);
            }
        }
        
        return result;
    }
};
