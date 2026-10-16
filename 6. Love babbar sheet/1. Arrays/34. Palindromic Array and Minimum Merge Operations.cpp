// Problem: Minimum Operations to Make an Array Palindrome (and Palindromic Array Check)
// Link (Article): https://www.geeksforgeeks.org/find-minimum-number-of-merge-operations-to-make-an-array-palindrome/
// Link (GFG Practice): https://www.geeksforgeeks.org/problems/palindromic-array-1587115620/1
// Difficulty: Easy / Medium
// Topic: Array, Two Pointers, Greedy, Math

/*
Problem Statement:
Problem 1 (Love Babbar Core: Minimum Merge Operations to Make Array Palindrome):
Given an array of positive integers `arr[]`. We can perform only one operation: merge two adjacent 
elements by replacing them with their sum.
Find the minimum number of merge operations needed to make the entire array a palindrome.

Problem 2 (GFG Practice: Palindromic Array):
Given an array of positive integers `arr[]`. Check if ALL elements in the array are palindromes 
individually (e.g. 111, 222, 333). Return 1 if true, else 0.

Example 1 (Merge Operations):
Input: arr = [15, 4, 15]
Output: 0
Explanation: Array is already a palindrome.

Example 2 (Merge Operations):
Input: arr = [1, 4, 5, 1]
Output: 1
Explanation: Merge 4 and 5 -> array becomes [1, 9, 1], which is a palindrome. Operations = 1.

Example 3 (Merge Operations):
Input: arr = [11, 14, 15, 99]
Output: 3
Explanation: Merge 11+14=25, 25+15=40, 40+99=139 -> single element [139] is a palindrome.

Constraints:
- 1 <= arr.size() <= 10^5
- 1 <= arr[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 1: We reversed the array by swapping opposite elements.
// - In Problem 34:
//   * We do not swap; we MERGE adjacent elements (`arr[i] + arr[i+1]`).
//   * Merging is an irreversible, strictly additive operation.
//   * Using two pointers from both ends, whenever the two boundary values differ, the SMALLER
//     value MUST be merged with its adjacent neighbor to match the larger boundary value!

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Greedy Two-Pointer Convergence (OPTIMAL & CHOSEN)
//   - Pointers `i = 0` (left) and `j = n - 1` (right).
//   - While `i <= j`:
//     * Case 1: `arr[i] == arr[j]`
//       Both boundaries match symmetrically. Advance both: `i++`, `j--`.
//     * Case 2: `arr[i] < arr[j]`
//       The left side is too small to match `arr[j]`. Since numbers are strictly positive,
//       the ONLY way to increase the left boundary is to merge `arr[i]` with `arr[i + 1]`!
//       `arr[i + 1] += arr[i]`, `i++`, `ops++`.
//     * Case 3: `arr[i] > arr[j]`
//       The right side is too small. Merge `arr[j]` with `arr[j - 1]`:
//       `arr[j - 1] += arr[j]`, `j--`, `ops++`.
//   - Complexity: Exactly O(N) time in a single pass, O(1) space!

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Function 1: Minimum Merge Operations to Make Array Palindrome
    // -------------------------------------------------------------------------
    int findMinOpsToMakePalindrome(vector<int>& arr) {
        int n = arr.size();
        int i = 0, j = n - 1;
        int operations = 0;

        while (i <= j) {
            // Symmetrical elements already match
            if (arr[i] == arr[j]) {
                i++;
                j--;
            }
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If left boundary is smaller than right boundary, it CANNOT match arr[j] as-is.
            // Because elements are positive, the ONLY way to make the left value bigger
            // is to greedily merge it with its immediate adjacent neighbor arr[i + 1]!
            else if (arr[i] < arr[j]) {
                arr[i + 1] += arr[i];
                i++;
                operations++;
            }
            // If right boundary is smaller, merge it with its left neighbor arr[j - 1]
            else {
                arr[j - 1] += arr[j];
                j--;
                operations++;
            }
        }

        return operations;
    }

    // -------------------------------------------------------------------------
    // Function 2: Check If All Numbers in Array Are Palindromic (GFG Practice)
    // -------------------------------------------------------------------------
    bool isSingleNumberPalindrome(int num) {
        int original = num;
        int reversed = 0;
        while (num > 0) {
            reversed = reversed * 10 + (num % 10);
            num /= 10;
        }
        return original == reversed;
    }

    bool palinArray(vector<int>& arr) {
        for (int x : arr) {
            if (!isSingleNumberPalindrome(x)) {
                return false;
            }
        }
        return true;
    }
};

/*
Time Complexity: O(N)
- In every iteration of the merge operations loop, either `i` advances or `j` recedes.
- Loop terminates in at most N steps: strictly O(N).
- Palindromic array check visits N numbers, each with at most log10(x) digits: O(N * log10(max_val)).

Space Complexity: O(1) Auxiliary Space
- Pure two-pointer scalar tracking.

Key Insights:
1. Why Greedily Merging the Smaller Element is Always Optimal:
   - Since all elements are positive (`arr[i] > 0`), merging always INCREASES the value.
   - If `arr[i] < arr[j]`, merging `arr[j]` with another element would only make the right side
     even larger, widening the gap!
   - Thus, the only possible step that can restore balance is to merge the smaller side (`arr[i]`).
*/
