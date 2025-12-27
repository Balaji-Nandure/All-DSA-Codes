/*
 * Problem: Leaders in an Array
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/leaders-in-an-array/
 * GeeksforGeeks Practice: https://practice.geeksforgeeks.org/problems/leaders-in-an-array-1587115620/1
 * 
 * Given an array A of positive integers. Your task is to find the leaders in the array.
 * An element of array is leader if it is greater than or equal to all the elements to its right side.
 * The rightmost element is always a leader.
 * 
 * Example 1:
 * Input: n = 6, A[] = {16,17,4,3,5,2}
 * Output: 17 5 2
 * Explanation: The first leader is 17 as it is greater than all the elements to its right.
 *              The second leader is 5. The third leader is 2.
 *              Note: The last element is always a leader.
 * 
 * Example 2:
 * Input: n = 5, A[] = {1,2,3,4,0}
 * Output: 4 0
 * 
 * Constraints:
 * - 1 <= n <= 10^7
 * - 0 <= A[i] <= 10^7
 * 
 * Approach:
 * - Traverse the array from right to left
 * - Keep track of the maximum element seen so far from the right
 * - If current element is greater than or equal to max, it's a leader
 * - Store leaders in a vector (or print in reverse order)
 * 
 * Time: O(n) - single pass from right to left
 * Space: O(1) - excluding output array
 */

#include <bits/stdc++.h>
using namespace std;

// APPROACH 1: Traverse from right to left (Optimal)
vector<int> leaders(int a[], int n) {
    vector<int> result;
    
    // Rightmost element is always a leader
    int maxFromRight = a[n - 1];
    result.push_back(maxFromRight);
    
    // Traverse from right to left
    for (int i = n - 2; i >= 0; i--) {
        // If current element is greater than or equal to max from right
        if (a[i] >= maxFromRight) {
            result.push_back(a[i]);
            maxFromRight = a[i];
        }
    }
    
    // Reverse to get leaders in original order
    reverse(result.begin(), result.end());
    
    return result;
}

// APPROACH 2: Brute Force (O(n^2)) - for each element, check all elements to its right
vector<int> leadersBruteForce(int a[], int n) {
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        bool isLeader = true;
        
        // Check all elements to the right
        for (int j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {
                isLeader = false;
                break;
            }
        }
        
        if (isLeader) {
            result.push_back(a[i]);
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> ans = leaders(a, n);
    
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    
    return 0;
}

