/*
 * Problem: Distinct Adjacent Element
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/distinct-adjacent-element/0
 * 
 * Given an array arr[] of integers, the task is to check whether obtaining an array with 
 * distinct adjacent elements is possible by swapping two neighboring array elements.
 * 
 * Examples:
 * Input: arr[] = [1, 1, 2]
 * Output: true
 * Explanation: Swapping last 2 elements can result in [1, 2, 1].
 * 
 * Input: arr[] = [7, 7, 7, 7]
 * Output: false
 * Explanation: We can't swap to obtain distinct elements in neighbor.
 * 
 * Constraints:
 * 2 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - The key insight is that we can only swap neighboring elements
 * - For an array to have distinct adjacent elements after swaps, no element should 
 *   appear more than ceil(n/2) times
 * - If an element appears more than ceil(n/2) times, it's impossible to separate 
 *   all its occurrences with other elements
 * - We can count frequency of each element using a hash map
 * - If any frequency > ceil(n/2), return false, otherwise true
 * 
 * Time: O(n) - single pass to count frequencies
 * Space: O(n) - hash map to store frequencies
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool distinctAdjacent(vector<int>& arr) {
        int n = arr.size();
        
        // If array has only 2 elements, they must be different
        if (n == 2) {
            return arr[0] != arr[1];
        }
        
        // Count frequency of each element
        unordered_map<int, int> freq;
        for (int num : arr) {
            freq[num]++;
        }
        
        // Find the maximum frequency
        int maxFreq = 0;
        for (auto& pair : freq) {
            maxFreq = max(maxFreq, pair.second);
        }
        
        // If any element appears more than ceil(n/2) times, it's impossible
        int allowedMax = (n + 1) / 2; // This is ceil(n/2)
        
        return maxFreq <= allowedMax;
    }
};

// Main function for testing
int main() {
    Solution sol;
    
    // Test case 1: Example from problem
    vector<int> arr1 = {1, 1, 2};
    cout << "Test 1: " << (sol.distinctAdjacent(arr1) ? "true" : "false") << endl; // Expected: true
    
    // Test case 2: Example from problem
    vector<int> arr2 = {7, 7, 7, 7};
    cout << "Test 2: " << (sol.distinctAdjacent(arr2) ? "true" : "false") << endl; // Expected: false
    
    // Test case 3: Already distinct
    vector<int> arr3 = {1, 2, 3, 4};
    cout << "Test 3: " << (sol.distinctAdjacent(arr3) ? "true" : "false") << endl; // Expected: true
    
    // Test case 4: Exactly at limit
    vector<int> arr4 = {1, 1, 1, 2, 3};
    cout << "Test 4: " << (sol.distinctAdjacent(arr4) ? "true" : "false") << endl; // Expected: true (1 appears 3 times, ceil(5/2)=3)
    
    // Test case 5: Over the limit
    vector<int> arr5 = {1, 1, 1, 1, 2};
    cout << "Test 5: " << (sol.distinctAdjacent(arr5) ? "true" : "false") << endl; // Expected: false (1 appears 4 times, ceil(5/2)=3)
    
    // Test case 6: Two different elements
    vector<int> arr6 = {1, 2};
    cout << "Test 6: " << (sol.distinctAdjacent(arr6) ? "true" : "false") << endl; // Expected: true
    
    // Test case 7: Two same elements
    vector<int> arr7 = {1, 1};
    cout << "Test 7: " << (sol.distinctAdjacent(arr7) ? "true" : "false") << endl; // Expected: false
    
    // Test case 8: Large array with balanced distribution
    vector<int> arr8 = {1, 1, 2, 2, 3, 3};
    cout << "Test 8: " << (sol.distinctAdjacent(arr8) ? "true" : "false") << endl; // Expected: true
    
    return 0;
}
