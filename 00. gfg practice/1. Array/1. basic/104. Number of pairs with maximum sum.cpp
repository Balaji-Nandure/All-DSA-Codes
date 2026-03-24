/*
Problem: Number of pairs with maximum sum

GFG: https://www.geeksforgeeks.org/problems/number-of-pairs-with-maximum-sum/1

Description: Given an array arr[], return the number of pairs (arr[i], arr[j]) such that arr[i] + arr[j] is maximum and i < j.

Examples:

Input: arr[] = [1, 1, 1, 2, 2, 2]
Output: 3
Explanation: We have an array [1, 1, 1, 2, 2, 2].The maximum possible pair sum where i is less than j is  4, which  is given by 3 pairs, so the answer is 3 .The pairs are (2, 2), (2, 2) and (2, 2).
Input: arr[] = [1, 4, 3, 3, 5, 1]
Output: 1

Constraints:
1 ≤ arr.size()≤ 106
1 ≤ arr[i] ≤ 106

Approach:
1. Find largest (max1) and second largest (max2) elements
2. Count their frequencies (freq1, freq2)
3. If freq1 >= 2: pairs = freq1 choose 2
4. Else: pairs = freq1 * freq2

Why it works:
- Maximum sum is either max1 + max1 or max1 + max2
- If we have at least 2 max1 elements, they form max sum pairs
- Otherwise, max1 pairs with all max2 elements
- Single pass gives O(n) time and O(1) space

Time Complexity: O(n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countPairs(vector<int>& arr) {
        int n = arr.size();

        int max1 = INT_MIN, max2 = INT_MIN;
        int freq1 = 0, freq2 = 0;

        // Find largest and second largest
        for (int x : arr) {
            if (x > max1) {
                max2 = max1;
                freq2 = freq1;

                max1 = x;
                freq1 = 1;
            }
            else if (x == max1) {
                freq1++;
            }
            else if (x > max2) {
                max2 = x;
                freq2 = 1;
            }
            else if (x == max2) {
                freq2++;
            }
        }

        // If largest appears more than once
        if (freq1 >= 2) {
            return (freq1 * (freq1 - 1)) / 2;
        }

        // Otherwise pairs with second largest
        return freq2;
    }
};
