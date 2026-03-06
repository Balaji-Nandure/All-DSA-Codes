/*
 * Problem: Array Operations
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/array-operations/1
 * 
 * You are given an array arr of n integers. You must return the minimum number 
 * of operations required to make this array 0. For this you can do an operation: 
 * Choose a sub-array of non-zero elements & replace all with 0 (0 must be present 
 * in arr, if not you can not replace it).
 * 
 * Examples:
 * Input: n = 4, arr = {3,0,4,5}
 * Output: 2
 * Explanation: First, we can choose 3 replace with 0 (which is on 1st Index) and 
 * in the second operation, we can choose 4 & 5 -> replace with 0 (1st Index).
 * 
 * Input: n = 8, arr = {10,4,9,6,10,10,4,4}
 * Output: -1
 * Explanation: If we do operations here, we can not make the entire 0 because no 
 * 0 is present in the array, hence -1.
 * 
 * Constraints:
 * 1 ≤ n ≤ 10^5
 * 0 ≤ arr[i] ≤ 10^9
 * 
 * Expected Time Complexity: O(N)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - If no 0 is present, impossible to perform operations, return -1
 * - Count the number of contiguous segments of non-zero elements
 * - Each segment requires one operation to replace with 0
 * - Iterate through the array, tracking when a new non-zero segment starts
 * - A new segment starts when current is non-zero and previous is 0 or i==0
 * 
 * Time: O(N) - single pass
 * Space: O(1) - constant space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int arrayOperations(int n, vector<long long>& arr) {

        int operations = 0;
        bool hasZero = false;

        for(int i = 0; i < n; i++) {

            if(arr[i] == 0) {
                hasZero = true;
            }
            else if(i == 0 || arr[i - 1] == 0) {
                // start of a new non-zero segment
                operations++;
            }
        }

        if(!hasZero) return -1;

        return operations;
    }
};
