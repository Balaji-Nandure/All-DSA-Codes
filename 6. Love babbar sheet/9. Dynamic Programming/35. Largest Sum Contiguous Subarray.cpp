#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Problem: Largest Sum Contiguous Subarray (Kadane's Algorithm)
 * 
 * Given an array of integers, find the contiguous subarray (containing at least one number) 
 * which has the maximum sum, and return its sum as well as the subarray itself.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "19. Maximum Sum Increasing Subsequence", elements did NOT need to be adjacent (subsequence).
 * - Here, elements MUST be CONTIGUOUS (subarray).
 * - This contiguity enforces an immediate local choice at each element:
 *   "Do we EXTEND the existing contiguous subarray, or do we START A FRESH subarray from this element?"
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Kadane's Dynamic Programming (O(N) Time, O(1) Space):
 *   Let dp[i] be the maximum sum of a contiguous subarray ending EXACTLY at index i.
 *   
 *   Recurrence:
 *     dp[i] = max(arr[i], dp[i - 1] + arr[i])
 *   
 *   Global Maximum:
 *     max_so_far = max_{0 <= i < N} dp[i]
 *   
 *   Subarray Reconstruction:
 *     Track `start`, `end`, and `current_start`:
 *     - If dp[i - 1] + arr[i] < arr[i], starting a fresh subarray at i is superior,
 *       so update current_start = i.
 *     - Whenever dp[i] exceeds max_so_far, record start = current_start and end = i.
 *   
 *   Corner Case Handling:
 *     Works correctly even when ALL numbers are negative by initializing max_so_far = arr[0].
 */

class Solution {
public:
    long long maxSubarraySum(vector<int>& arr) {
        int n = arr.size();
        long long max_so_far = arr[0];
        long long current_sum = arr[0];

        int start = 0, end = 0, temp_start = 0;

        for (int i = 1; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Kadane's decision: Either extend previous subarray, or start fresh at index i
            if (current_sum + arr[i] < arr[i]) {
                current_sum = arr[i];
                temp_start = i;
            } else {
                current_sum += arr[i];
            }

            // *** CRUCIAL LINE: Update global best and track bounds for reconstruction ***
            if (current_sum > max_so_far) {
                max_so_far = current_sum;
                start = temp_start;
                end = i;
            }
        }

        cout << "Maximum Subarray: [ ";
        for (int i = start; i <= end; i++) {
            cout << arr[i] << " ";
        }
        cout << "]\n";

        return max_so_far;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 2, 3, -2, 5};
    cout << "Max Sum 1: " << sol.maxSubarraySum(arr1) << "\n";
    // Subarray [1, 2, 3, -2, 5] sum = 9. Expected: 9.

    vector<int> arr2 = {-1, -2, -3, -4};
    cout << "Max Sum 2: " << sol.maxSubarraySum(arr2) << "\n";
    // All negative: max single element is -1. Expected: -1.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear scan over the array.
 * - Space Complexity: O(1) auxiliary space (tracks only rolling sums and boundary indices).
 */
