#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Longest alternating subsequence (Wiggle Subsequence)
 * 
 * A sequence of numbers is called alternating (or wiggle) if the differences 
 * between successive numbers strictly alternate between positive and negative:
 *   x1 < x2 > x3 < x4 > x5 ... OR x1 > x2 < x3 > x4 < x5 ...
 * Find the length of the longest alternating subsequence.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "16. LIS", the monotonic direction was uniform throughout (strictly increasing).
 * - Here, the direction MUST alternate sign on every step: + then - then + then - ...
 * - While standard O(N^2) DP maintains up[i] and down[i], the peak-valley property 
 *   enables an elegant O(N) time and O(1) space state-machine algorithm!
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Peak-Valley Dual State Dynamic Programming:
 *   Maintain two rolling variables:
 *   - `up`: length of the longest alternating subsequence ending with a positive slope (arr[i] > arr[i-1]).
 *   - `down`: length of the longest alternating subsequence ending with a negative slope (arr[i] < arr[i-1]).
 *   
 *   Base Case:
 *     up = 1, down = 1 (a single element forms an alternating sequence of length 1).
 *   
 *   Transitions for each element from index 1 to N - 1:
 *     1. If arr[i] > arr[i - 1] (Upward step):
 *        An upward step can only follow a previous DOWNWARD step:
 *        up = down + 1.
 *     
 *     2. If arr[i] < arr[i - 1] (Downward step):
 *        A downward step can only follow a previous UPWARD step:
 *        down = up + 1.
 *     
 *     3. If arr[i] == arr[i - 1] (Flat step):
 *        No alternating transition occurs; up and down remain unchanged.
 *   
 *   Result:
 *     max(up, down)
 */

class Solution {
public:
    int alternatingMaxLength(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return n;

        int up = 1;
        int down = 1;

        for (int i = 1; i < n; i++) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            if (arr[i] > arr[i - 1]) {
                // An upward transition strictly builds upon the best preceding downward subsequence
                up = down + 1;
            } else if (arr[i] < arr[i - 1]) {
                // A downward transition strictly builds upon the best preceding upward subsequence
                down = up + 1;
            }
            // If arr[i] == arr[i - 1], neither up nor down changes
        }

        // *** CRUCIAL LINE: Maximum between ending on an up-step or down-step ***
        return max(up, down);
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {1, 5, 4};
    cout << "Longest Alternating 1: " << sol.alternatingMaxLength(arr1) << "\n";
    // 1 < 5 > 4 (length 3). Expected: 3.

    vector<int> arr2 = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
    cout << "Longest Alternating 2: " << sol.alternatingMaxLength(arr2) << "\n";
    // Alternating: [1, 17, 5, 15, 5, 16, 8] (length 7). Expected: 7.

    vector<int> arr3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Longest Alternating 3: " << sol.alternatingMaxLength(arr3) << "\n";
    // Monotonic increasing: any pair [1, 9] gives length 2. Expected: 2.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single linear scan over the array.
 * - Space Complexity: O(1) auxiliary space (using only two integer counters).
 */
