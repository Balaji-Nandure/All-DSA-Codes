/*
Problem: Union of Two Sorted Arrays (Distinct Elements)

GFG: https://www.geeksforgeeks.org/union-of-two-sorted-arrays/

Description: Given two sorted arrays a[] and b[], where each array may contain duplicate elements, the task is to return the elements in the union of the two arrays in sorted order.

Union of two arrays can be defined as a set containing distinct common elements that are present in either of the arrays.

Examples:

Input: a[] = [1, 2, 3, 4, 5], b[] = [1, 2, 3, 6, 7]
Output: [1, 2, 3, 4, 5, 6, 7]
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5 6 7.
Input: a[] = [2, 2, 3, 4, 5], b[] = [1, 1, 2, 3, 4]
Output: [1, 2, 3, 4, 5]
Explanation: Distinct elements including both the arrays are: 1 2 3 4 5.
Input: a[] = [1, 1, 1, 1], b[] = [2, 2, 2, 2]
Output: [1, 2]
Explanation: Distinct elements including both the arrays are: 1 2.

Constraints:
1 ≤ a.size(), b.size() ≤ 105
-109 ≤ a[i], b[i] ≤ 109

Approach:
Two-Pointer Technique (similar to merge in merge sort):
Since arrays are sorted, use two pointers.
Compare elements and insert smaller element.
If equal, insert once and move both pointers.
Skip duplicates while inserting.

Why it works:
Sorted arrays allow merging like merge step of merge sort.
Duplicate skipping ensures distinct elements only.

Algorithm:
1. Initialize i = 0, j = 0
2. While i < n && j < m:
   - Skip duplicates in a[]: if i > 0 && a[i] == a[i-1]: i++
   - Skip duplicates in b[]: if j > 0 && b[j] == b[j-1]: j++
   - If a[i] < b[j]: push a[i], i++
   - Else if a[i] > b[j]: push b[j], j++
   - Else: push a[i], i++, j++
3. Add remaining elements from both arrays
4. Return result

Time Complexity: O(n + m)
Space Complexity: O(n + m)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findUnion(int a[], int b[], int n, int m) {
        int i = 0;
        int j = 0;

        vector<int> result;

        while (i < n && j < m) {
            // Skip duplicates in a[]
            if (i > 0 && a[i] == a[i - 1]) {
                i++;
                continue;
            }

            // Skip duplicates in b[]
            if (j > 0 && b[j] == b[j - 1]) {
                j++;
                continue;
            }

            if (a[i] < b[j]) {
                result.push_back(a[i]);
                i++;
            }
            else if (a[i] > b[j]) {
                result.push_back(b[j]);
                j++;
            }
            else {
                // If both equal, push once
                result.push_back(a[i]);
                i++;
                j++;
            }
        }

        // Remaining elements of a[]
        while (i < n) {
            if (i == 0 || a[i] != a[i - 1]) {
                result.push_back(a[i]);
            }
            i++;
        }

        // Remaining elements of b[]
        while (j < m) {
            if (j == 0 || b[j] != b[j - 1]) {
                result.push_back(b[j]);
            }
            j++;
        }

        return result;
    }
};
