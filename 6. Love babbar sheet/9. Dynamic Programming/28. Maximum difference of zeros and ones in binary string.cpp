#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/**
 * Problem: Maximum difference of zeros and ones in binary string
 * 
 * Given a binary string S of 0s and 1s, find the maximum difference between 
 * the count of 0s and count of 1s (count(0) - count(1)) across all non-empty substrings.
 * If all characters in the string are '1', return -1.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This string problem beautifully maps to the classic MAXIMUM SUBARRAY SUM (Kadane's Algorithm)!
 * - Instead of maintaining separate counts of 0s and 1s across all O(N^2) substrings,
 *   we map each character to a numerical delta.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Reduction to Kadane's Algorithm in O(N) Time and O(1) Space:
 *   Let every '0' contribute +1 (increases the lead of zeros).
 *   Let every '1' contribute -1 (decreases the lead of zeros).
 *   
 *   Now the net difference of any substring is simply the SUM of elements in that subarray:
 *     Difference = sum_{k=i}^j delta[k]
 *   
 *   Maximizing (count(0) - count(1)) over all substrings is IDENTICAL to finding 
 *   the Maximum Subarray Sum!
 *   
 *   Kadane's Algorithm:
 *     curr_sum = max(val, curr_sum + val)
 *     max_diff = max(max_diff, curr_sum)
 *   
 *   Edge Case:
 *     If the string has only '1's, every single delta is -1.
 *     The maximum subarray sum would be -1, correctly returning -1 as required.
 */

class Solution {
public:
    int maxSubstring(string S) {
        int max_diff = -1;
        int current_sum = 0;

        for (char c : S) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // Map '0' to +1 (gain) and '1' to -1 (penalty)
            int val = (c == '0') ? 1 : -1;

            // Standard Kadane's recurrence
            current_sum += val;

            if (current_sum > max_diff) {
                max_diff = current_sum;
            }

            // *** CRUCIAL LINE: If running sum drops below 0, reset to 0 to start fresh candidate substring ***
            if (current_sum < 0) {
                current_sum = 0;
            }
        }

        return max_diff;
    }
};

int main() {
    Solution sol;
    string s1 = "11000010001";
    cout << "Max diff 1: " << sol.maxSubstring(s1) << "\n";
    // Substring "00001000" has 7 zeros and 1 one -> diff = 6. Expected: 6.

    string s2 = "1111";
    cout << "Max diff 2: " << sol.maxSubstring(s2) << "\n";
    // All 1s -> Expected: -1.

    string s3 = "0000";
    cout << "Max diff 3: " << sol.maxSubstring(s3) << "\n";
    // All 0s -> Expected: 4.

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N) single pass over the string characters.
 * - Space Complexity: O(1) auxiliary space.
 */
