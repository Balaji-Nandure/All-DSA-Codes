/*
 * Problem: Perfect Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/perfect-array/0
 * 
 * Given an array arr[] of non-negative integers, determine whether the array is perfect.
 * An array is considered perfect if it first strictly increases, then remains constant, 
 * and finally strictly decreases. Any of these three parts can be empty.
 * 
 * Examples:
 * Input: arr[] = [1, 8, 8, 8, 3, 2]
 * Output: true
 * Explanation: The array [1, 8, 8, 8, 3, 2] first increases in the range [0, 1], 
 *              stays constant in the range [1, 3], and then decreases in the range [3, 4]. 
 *              Thus, the array is perfect.
 * 
 * Input: arr[] = [1, 1, 2, 2, 1]
 * Output: false
 * Explanation: The array does not follow the required pattern of strictly increasing, 
 *              constant, and then strictly decreasing.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^8
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Traverse the array in three phases:
 *   1. First strictly increasing phase (arr[i] > arr[i-1])
 *   2. Then constant phase (arr[i] == arr[i-1])
 *   3. Finally strictly decreasing phase (arr[i] < arr[i-1])
 * - If we reach the end of array after these three phases, it's perfect
 * - Any of these phases can be empty (no elements in that phase)
 * 
 * Time: O(n) - single pass through the array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPerfect(vector<int>& arr) {
        // code here
        int n = arr.size();
        if(n <= 1) return true;
        
        int i = 1;
        
        // Phase 1: Strictly increasing
        while(i < n && arr[i] > arr[i - 1]) i++;
        
        // Phase 2: Constant
        while(i < n && arr[i] == arr[i - 1]) i++;
        
        // Phase 3: Strictly decreasing
        while(i < n && arr[i] < arr[i - 1]) i++;
        
        // If we've traversed the entire array, it's perfect
        return i == n;
    }
};

// Main function for testing
int main() {
    Solution sol;
    
    // Test case 1: Perfect array
    vector<int> arr1 = {1, 8, 8, 8, 3, 2};
    cout << "Test 1: " << (sol.isPerfect(arr1) ? "true" : "false") << endl;
    
    // Test case 2: Not perfect array
    vector<int> arr2 = {1, 1, 2, 2, 1};
    cout << "Test 2: " << (sol.isPerfect(arr2) ? "true" : "false") << endl;
    
    // Test case 3: Only increasing
    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "Test 3: " << (sol.isPerfect(arr3) ? "true" : "false") << endl;
    
    // Test case 4: Only decreasing
    vector<int> arr4 = {5, 4, 3, 2, 1};
    cout << "Test 4: " << (sol.isPerfect(arr4) ? "true" : "false") << endl;
    
    // Test case 5: Only constant
    vector<int> arr5 = {3, 3, 3, 3};
    cout << "Test 5: " << (sol.isPerfect(arr5) ? "true" : "false") << endl;
    
    // Test case 6: Single element
    vector<int> arr6 = {42};
    cout << "Test 6: " << (sol.isPerfect(arr6) ? "true" : "false") << endl;
    
    return 0;
}
