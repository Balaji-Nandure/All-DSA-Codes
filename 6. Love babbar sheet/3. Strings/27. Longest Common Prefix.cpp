// Problem: Longest Common Prefix in an Array
// Link (GFG): https://www.geeksforgeeks.org/problems/longest-common-prefix-in-an-array5129/1
// Article: https://www.geeksforgeeks.org/dsa/longest-common-prefix-using-word-by-word-matching/
// Difficulty: Easy
// Topic: String, Character-by-Character Vertical Scanning, Trie

/*
Problem Statement:
Given an array of strings `arr[]` of length n, find the longest common prefix (LCP) 
shared among all strings in the array.
If there is no common prefix, return "-1" (or "" depending on platform convention).

Example 1:
Input: arr = ["geeksforgeeks", "geeks", "geek", "geezer"]
Output: "gee"
Explanation: "gee" is the longest common prefix across all 4 strings.

Example 2:
Input: arr = ["hello", "world"]
Output: "-1"
Explanation: No common prefix exists.

Constraints:
- 1 <= n <= 10^3
- 1 <= arr[i].length <= 10^3
- Strings consist of lowercase English letters.
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Longest Common Subsequence (LCS, Problem 31):
//   * Characters can be non-contiguous and skip around anywhere in the strings.
// - In Longest Common Prefix (LCP):
//   * Characters MUST start at the VERY FIRST character (`index 0`) and be strictly CONTIGUOUS.
//   * The moment any single string has a mismatch at column `j`, NO string can have a prefix 
//     longer than `j`.
//   * This enables VERTICAL SCANNING with early termination!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Approach 1: Horizontal Scanning (Word-by-Word)
//   - Set `prefix = arr[0]`. Compare with `arr[1]` and shrink. Compare with `arr[2]` and shrink.
//   - Why Suboptimal: If the very last string has a mismatch at index 0, we still wasted time 
//     comparing long prefixes across all prior strings.
//
// Approach 2: Vertical Scanning (Column-by-Column) - OPTIMAL & CHOSEN
//   - Take `arr[0]` as reference.
//   - Iterate through column index `col` from 0 to `arr[0].length() - 1`:
//       * Let `targetChar = arr[0][col]`.
//       * For each string `arr[i]` from row 1 to `n - 1`:
//           - If `col >= arr[i].length()` OR `arr[i][col] != targetChar`:
//               Stop immediately! Return prefix up to `col`.
//   - Early exit efficiency: As soon as one string disagrees, the entire algorithm halts.
//   - Complexity: O(N * minLen) worst case, O(1) auxiliary space!
//
// Approach 3: Sort Array and Compare First & Last
//   - Lexicographical sorting puts the two most disparate strings at `arr[0]` and `arr[n-1]`.
//   - Compare `arr[0]` with `arr[n-1]`.
//   - Complexity: O(N * L * log N) due to sorting. Slower than vertical scan.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& arr) {
        if (arr.empty()) return "-1";
        if (arr.size() == 1) return arr[0];

        // Vertical column scan across all strings
        int firstLen = arr[0].length();

        for (int col = 0; col < firstLen; ++col) {
            char ch = arr[0][col];

            // Compare character with all other strings at the same column
            for (size_t row = 1; row < arr.size(); ++row) {
                // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                // Vertical mismatch condition: Either the current string has ended (col == length)
                // or the character at index `col` does not match `arr[0][col]`.
                // In either case, the common prefix CANNOT extend any further!
                if (col >= (int)arr[row].length() || arr[row][col] != ch) {
                    if (col == 0) return "-1"; // No common prefix found
                    return arr[0].substr(0, col);
                }
            }
        }

        // If the entire first string matched across all words
        return arr[0].empty() ? "-1" : arr[0];
    }
};

int main() {
    Solution sol;
    vector<string> arr1 = {"geeksforgeeks", "geeks", "geek", "geezer"};
    cout << "LCP for arr1: " << sol.longestCommonPrefix(arr1) << "\n";

    vector<string> arr2 = {"hello", "world"};
    cout << "LCP for arr2: " << sol.longestCommonPrefix(arr2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * M) where N is number of strings, and M is the length of the shortest string.
  * In the best case (first character mismatch), runs in O(N) comparisons and terminates immediately!
- Space Complexity: O(1) auxiliary space (excluding returned substring).

Key Takeaways:
- Vertical scanning is strictly superior to horizontal scanning because it short-circuits 
  on the first failing column across all words.
*/
