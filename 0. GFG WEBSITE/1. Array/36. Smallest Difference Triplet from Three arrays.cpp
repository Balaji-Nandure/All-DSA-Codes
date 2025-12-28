/*
 * Problem: Smallest Difference Triplet from Three arrays
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/smallest-difference-triplet-from-three-arrays/
 * Practice: https://practice.geeksforgeeks.org/problems/smallest-difference-triplet/0
 * 
 * Given three sorted arrays A, B, C of not necessarily same sizes.
 * Calculate the minimum absolute difference of the maximum and minimum number 
 * from the three elements taken one from each array.
 * 
 * We need to find three elements a, b, c such that:
 * - a is from array A
 * - b is from array B
 * - c is from array C
 * - abs(max(a, b, c) - min(a, b, c)) is minimized
 * 
 * Example 1:
 * Input: A = [1, 4, 5, 8, 10], B = [6, 9, 15], C = [2, 3, 6, 6]
 * Output: 1
 * Explanation: Triplet (5, 6, 6) gives difference = max(5,6,6) - min(5,6,6) = 6 - 5 = 1
 * 
 * Example 2:
 * Input: A = [5, 8, 10, 15], B = [6, 9, 15, 78, 89], C = [2, 3, 6, 6, 8, 8, 10]
 * Output: 1
 * Explanation: Triplet (10, 9, 10) gives difference = 10 - 9 = 1
 * 
 * Example 3:
 * Input: A = [1, 2, 3], B = [4, 5, 6], C = [7, 8, 9]
 * Output: 6
 * Explanation: Triplet (3, 4, 7) gives difference = 7 - 3 = 4
 *              But (3, 6, 7) gives difference = 7 - 3 = 4
 *              Actually, (3, 4, 7) gives 7 - 3 = 4, but let's check (3, 6, 7) = 4
 *              Best is (3, 4, 7) with diff = 4
 * 
 * Constraints:
 * - 1 <= |A|, |B|, |C| <= 10^5
 * - -10^9 <= A[i], B[i], C[i] <= 10^9
 * - Arrays are sorted
 * 
 * Approach:
 * - Method 1: Three Pointers (Optimal) - O(n + m + p) time, O(1) space
 *   Sort all three arrays, use three pointers
 *   Calculate diff = max(a, b, c) - min(a, b, c)
 *   Move pointer pointing to smallest element to reduce difference
 * 
 * - Method 2: Brute Force - O(n*m*p) time, O(1) space
 *   Try all combinations
 * 
 * - Method 3: Binary Search - O(n*m*log(p)) time, O(1) space
 *   For each pair from A and B, binary search in C
 * 
 * Time: O(n + m + p) - three pointers (optimal method)
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // APPROACH 2: Return the triplet itself
    vector<int> smallestDifferenceTripletValues(vector<int>& A, vector<int>& B, vector<int>& C) {
        int n = A.size(), m = B.size(), p = C.size();
        
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        sort(C.begin(), C.end());
        
        int i = 0, j = 0, k = 0;
        int minDiff = INT_MAX;
        vector<int> result(3);
        
        while (i < n && j < m && k < p) {
            int a = A[i], b = B[j], c = C[k];
            int maxVal = max({a, b, c});
            int minVal = min({a, b, c});
            int diff = maxVal - minVal;
            
            if (diff < minDiff) {
                minDiff = diff;
                result[0] = a;
                result[1] = b;
                result[2] = c;
            }
            
            if (minVal == a) {
                i++;
            } else if (minVal == b) {
                j++;
            } else {
                k++;
            }
        }
        
        return result;
    }
    
};
