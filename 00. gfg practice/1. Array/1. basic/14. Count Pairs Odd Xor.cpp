/*
 * Problem: Count Pairs Odd Xor
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/count-pairs-odd-xor/0
 * 
 * Given an array arr[] of integers, find the number of pairs whose XOR is odd in the array.
 * 
 * Examples:
 * Input: arr[] = [1, 2, 3]
 * Output: 2
 * Explanation: The XOR of the pairs is as follows: 
 *              1 ^ 2 = 3 (odd), 1 ^ 3 = 2 (even), 2 ^ 3 = 1 (odd), 
 *              There are 2 pairs with odd XOR.
 * 
 * Input: arr[] = [1, 2]
 * Output: 1
 * Explanation: The XOR of the pair is: 1 ^ 2 = 3 (odd), 
 *              There is 1 pair with odd XOR.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^5
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - XOR of two numbers is odd if and only if one number is even and the other is odd
 * - This is because: even ^ odd = odd, odd ^ even = odd, even ^ even = even, odd ^ odd = even
 * - So we just need to count the number of even and odd numbers in the array
 * - Number of pairs with odd XOR = (count of even numbers) * (count of odd numbers)
 * - This gives us all possible pairs where one number is even and the other is odd
 * 
 * Time: O(n) - single pass through array to count even/odd numbers
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countPairs(vector<int>& arr) {
        long long evenCount = 0;
        long long oddCount = 0;
        
        // Count even and odd numbers
        for (int num : arr) {
            if (num % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }
        
        // Number of pairs with odd XOR = evenCount * oddCount
        return evenCount * oddCount;
    }
};

// Main function for testing
int main() {
    Solution sol;
    
    // Test case 1
    vector<int> arr1 = {1, 2, 3};
    cout << "Test 1: " << sol.countPairs(arr1) << endl; // Expected: 2
    
    // Test case 2
    vector<int> arr2 = {1, 2};
    cout << "Test 2: " << sol.countPairs(arr2) << endl; // Expected: 1
    
    // Test case 3: All even numbers
    vector<int> arr3 = {2, 4, 6, 8};
    cout << "Test 3: " << sol.countPairs(arr3) << endl; // Expected: 0
    
    // Test case 4: All odd numbers
    vector<int> arr4 = {1, 3, 5, 7};
    cout << "Test 4: " << sol.countPairs(arr4) << endl; // Expected: 0
    
    // Test case 5: Mixed numbers
    vector<int> arr5 = {1, 2, 4, 5, 7, 8};
    cout << "Test 5: " << sol.countPairs(arr5) << endl; // Expected: 9 (3 even * 3 odd)
    
    // Test case 6: Single element
    vector<int> arr6 = {5};
    cout << "Test 6: " << sol.countPairs(arr6) << endl; // Expected: 0
    
    // Test case 7: Large array
    vector<int> arr7 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "Test 7: " << sol.countPairs(arr7) << endl; // Expected: 25 (5 even * 5 odd)
    
    return 0;
}
