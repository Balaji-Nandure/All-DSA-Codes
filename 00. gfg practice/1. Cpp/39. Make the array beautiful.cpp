/*
 * Problem: Make the array beautiful
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/make-the-array-beautiful/1
 * 
 * Given an array of negative and non-negative integers. You have to make the array 
 * beautiful. An array is beautiful if two adjacent integers, arr[i] and arr[i+1] 
 * are either negative or non-negative. And you can do the following operation any 
 * number of times until the array becomes beautiful.
 * 
 * If two adjacent integers are different i.e. one of them is negative and other 
 * is non-negative, remove them.
 * Return the beautiful array after performing the above operation.
 * 
 * Note: An empty array is also a beautiful array. There can be many adjacent integers 
 * which are different as stated above. So remove different adjacent integers as 
 * described above from left to right.
 * 
 * Examples:
 * Input: [4, 2, -2, 1]
 * Output: [4, 1]
 * Explanation: As at indices 1 and 2, 2 and -2 have different sign, they are removed. 
 *              And the final array is: 4 1.
 * 
 * Input: [2, -2, 1, -1]
 * Output: []
 * Explanation: As at indices 0 and 1, 2 and -2 have different sign, so they are removed. 
 *              Now the array is 1 -1. Now 1 and -1 are also removed as they have different sign. 
 *              So the final array is empty.
 * 
 * Constraints:
 * 1 ≤ size of the array ≤ 10^5
 * -10^5 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(N)
 * Expected Space Complexity: O(N)
 * 
 * Approach:
 * - Use stack simulation to handle adjacent pair removal
 * - Traverse array and maintain stack of elements
 * - When current element has opposite sign to stack top, remove both (pop)
 * - Otherwise, push current element to stack
 * - This handles cascading removals correctly
 * - Stack contains final beautiful array
 * 
 * Time: O(N) - each element processed once
 * Space: O(N) - stack may contain all elements in worst case
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> makeBeautiful(vector<int> arr) {
        
        vector<int> st;  // acts like stack
        
        for (int x : arr) {
            
            if (st.empty()) {
                st.push_back(x);
            }
            else {
                int top = st.back();
                
                // different sign condition
                if ((top < 0 && x >= 0) || (top >= 0 && x < 0)) {
                    st.pop_back();  // remove both
                }
                else {
                    st.push_back(x);
                }
            }
        }
        
        return st;
    }
};
