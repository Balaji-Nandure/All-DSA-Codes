/*
 * Problem: A guy with a mental problem
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/a-guy-with-a-mental-problem/0
 * 
 * A person needs to reach home by train but compulsively switches trains at every station.
 * If they start with train arr1 at the first station, they will switch to train arr2 at the next station,
 * and then switch back to train arr1 at the following station, and so on. Similarly, if they start with 
 * train arr2, they will switch to train arr1 at the next station, and continue alternating.
 * 
 * Given two arrays, arr1 and arr2, where:
 * arr1[i] represents the time taken by train arr1 at station i.
 * arr2[i] represents the time taken by train arr2 at station i.
 * Determine the minimum total time required to reach home starting from either train arr1 or train arr2,
 * with the switching pattern maintained.
 * 
 * Examples:
 * Input: arr1 = [2, 1, 2], arr2 = [3, 2, 1]
 * Output: 5
 * Explanation: Starting with train arr2 yields the minimum total time of 5.
 * 
 * Input: arr1 = [1, 3, 1, 2], arr2 = [2, 2, 3, 1]
 * Output: 5
 * Explanation: Starting with train arr1 yields the minimum total time of 5.
 * 
 * Constraints:
 * 1 ≤ arr1.size(), arr2.size() ≤ 10^6
 * 1 ≤ arr1[i], arr2[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Calculate total time if starting with arr1: sum of arr1[0] + arr2[1] + arr1[2] + arr2[3] + ...
 * - Calculate total time if starting with arr2: sum of arr2[0] + arr1[1] + arr2[2] + arr1[3] + ...
 * - Return the minimum of both totals
 * - Use parity (even/odd index) to determine which train to pick at each station
 * 
 * Time: O(n) - single pass through arrays
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minTime(vector<int>& arr1, vector<int>& arr2) {
        int startA = 0;
        int startB = 0;
        int n = arr1.size();
        
        for(int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                startA += arr1[i];
                startB += arr2[i];
            } else {
                startA += arr2[i];
                startB += arr1[i];
            }
        }
        
        return min(startA, startB);
    }
};

// Main function for testing
int main() {
    Solution sol;
    
    // Test case 1
    vector<int> arr1_1 = {2, 1, 2};
    vector<int> arr2_1 = {3, 2, 1};
    cout << "Test 1: " << sol.minTime(arr1_1, arr2_1) << endl; // Expected: 5
    
    // Test case 2
    vector<int> arr1_2 = {1, 3, 1, 2};
    vector<int> arr2_2 = {2, 2, 3, 1};
    cout << "Test 2: " << sol.minTime(arr1_2, arr2_2) << endl; // Expected: 5
    
    // Test case 3: Single station
    vector<int> arr1_3 = {5};
    vector<int> arr2_3 = {3};
    cout << "Test 3: " << sol.minTime(arr1_3, arr2_3) << endl; // Expected: 3
    
    // Test case 4: Two stations
    vector<int> arr1_4 = {1, 2};
    vector<int> arr2_4 = {3, 1};
    cout << "Test 4: " << sol.minTime(arr1_4, arr2_4) << endl; // Expected: 2
    
    // Test case 5: All same values
    vector<int> arr1_5 = {2, 2, 2, 2};
    vector<int> arr2_5 = {2, 2, 2, 2};
    cout << "Test 5: " << sol.minTime(arr1_5, arr2_5) << endl; // Expected: 4
    
    return 0;
}
