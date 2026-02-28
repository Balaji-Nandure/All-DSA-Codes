/*
 * Problem: Sort by Set Bit Count
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/sort-by-set-bit-count1153/1
 * 
 * Sort array in descending order of number of set bits. If two elements have 
 * same set bit count, maintain original order (stable sort required).
 * 
 * Example:
 * Input: arr[] = [5, 2, 3, 9, 4, 6, 7, 15, 32]
 * Output: [15, 7, 5, 6, 3, 9, 4, 2, 32]
 * Explanation: 15 has 4 set bits, 7 has 3, 5 has 2, etc.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Use stable_sort with a static comparator function
 * - Comparator uses __builtin_popcount for efficient bit counting
 * - stable_sort maintains relative order for equal bit counts
 * - __builtin_popcount is a GCC built-in function for counting set bits
 * - Comparator returns countA > countB for descending order
 * - Separate countSetBits function shown but not used in final solution
 * 
 * Time: O(n log n) - sorting with O(n) comparisons
 * Space: O(1) - in-place sorting
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    
    static int countSetBits(int n) {
        int count = 0;
        
        while (n > 0) {
            n = n & (n - 1);
            count++;
        }
        
        return count;
    }

    static bool comp(int a, int b) {
        int countA = countSetBits(a);
        int countB = countSetBits(b);
        
        return countA > countB;
    }
    
    void sortBySetBitCount(int arr[], int n) {
        stable_sort(arr, arr + n, comp);
    }
};
