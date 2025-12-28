/*
 * Problem: Find common elements in three sorted arrays
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/find-common-elements-three-sorted-arrays/
 * Practice: https://practice.geeksforgeeks.org/problems/common-elements1132/1
 * 
 * Given three arrays sorted in increasing order. Find the elements that are common 
 * in all three arrays.
 * 
 * Example 1:
 * Input: ar1[] = {1, 5, 10, 20, 40, 80}
 *        ar2[] = {6, 7, 20, 80, 100}
 *        ar3[] = {3, 4, 15, 20, 30, 70, 80, 120}
 * Output: 20, 80
 * Explanation: 20 and 80 are the only common elements in all three arrays
 * 
 * Example 2:
 * Input: ar1[] = {1, 5, 5}
 *        ar2[] = {3, 4, 5, 5, 10}
 *        ar3[] = {5, 5, 10, 20}
 * Output: 5, 5
 * Explanation: 5 appears twice in all three arrays
 * 
 * Constraints:
 * - 1 <= n1, n2, n3 <= 10^5
 * - 1 <= ar1[i], ar2[i], ar3[i] <= 10^6
 * - Arrays are sorted in non-decreasing order
 * 
 * Approach:
 * - Method 1: Three Pointers (Optimal for sorted arrays) - O(n1 + n2 + n3) time, O(1) space
 *   Use three pointers, one for each array
 *   If all three elements are equal, add to result and move all pointers
 *   Otherwise, move pointer pointing to smallest element
 * 
 * - Method 2: Hash Map - O(n1 + n2 + n3) time, O(n1 + n2 + n3) space
 *   Count frequency in first two arrays, check third array
 * 
 * - Method 3: Set Intersection - O(n1 + n2 + n3) time, O(n1 + n2 + n3) space
 *   Use set intersection to find common elements
 * 
 * - Method 4: Binary Search - O(n1 * (log n2 + log n3)) time, O(1) space
 *   For each element in first array, binary search in other two
 * 
 * Time: O(n1 + n2 + n3) - three pointers (optimal method)
 * Space: O(1) - constant extra space (excluding result array)
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> commonElements(vector<int>& A, vector<int>& B, vector<int>& C) {
    int i = 0, j = 0, k = 0;
    vector<int> result;

    while (i < A.size() && j < B.size() && k < C.size()) {

        // If all three elements are equal
        if (A[i] == B[j] && B[j] == C[k]) {
            result.push_back(A[i]);

            int val = A[i];

            // Skip duplicates in all arrays
            while (i < A.size() && A[i] == val) i++;
            while (j < B.size() && B[j] == val) j++;
            while (k < C.size() && C[k] == val) k++;
        }
        else {
            // Move pointer having smallest value
            int mini = min({A[i], B[j], C[k]});

            if (A[i] == mini) i++;
            else if (B[j] == mini) j++;
            else k++;
        }
    }

    return result;
}
