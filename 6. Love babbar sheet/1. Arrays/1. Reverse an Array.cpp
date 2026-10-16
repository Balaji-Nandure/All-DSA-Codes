// Problem: Reverse an Array / String
// Link (LeetCode 344): https://leetcode.com/problems/reverse-string/
// Link (GFG): https://www.geeksforgeeks.org/problems/reverse-a-string/1
// Difficulty: Basic / Easy
// Topic: Array, String, Two Pointers

/*
Problem Statement:
You are given an array (or a string `s`) of characters / integers. 
You are tasked to reverse the array / string in-place without allocating extra space for another array.

Example 1:
Input: s = ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]

Example 2:
Input: s = ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]

Example 3 (Array of Integers):
Input: arr = [1, 2, 3, 4, 5, 6]
Output: [6, 5, 4, 3, 2, 1]

Constraints:
- 1 <= s.length <= 10^5
- s[i] is a printable ascii character / integer
*/

// Approach: Two Pointers (Optimal In-Place Swap)
// 1. Core Intuition:
//    - Reversing an array means swapping the 1st element with the last, 
//      the 2nd element with the 2nd last, and so forth until pointers meet in the middle.
// 2. Algorithm Steps:
//    Step 1: Initialize two pointers:
//            - `left = 0` (pointing to the first index)
//            - `right = n - 1` (pointing to the last index)
//    Step 2: While `left < right`:
//            - Swap `arr[left]` with `arr[right]`
//            - Increment `left` by 1 (`left++`)
//            - Decrement `right` by 1 (`right--`)
//    Step 3: When `left >= right`, all pairs have been swapped in-place.
//
// 3. Alternative Approaches:
//    - Approach 2: Recursive (Swap ends, recurse for sub-array `[left + 1, right - 1]`) -> O(N) space due to recursion stack.
//    - Approach 3: STL `std::reverse(arr.begin(), arr.end())` -> Highly optimized internal implementation of Two Pointers.

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Function 1: Reverse Character Vector / String (LeetCode 344 Style)
    // -------------------------------------------------------------------------
    void reverseString(vector<char>& s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
    }

    // -------------------------------------------------------------------------
    // Function 2: Reverse String in-place (GFG Style)
    // -------------------------------------------------------------------------
    string reverseString(string& s) {
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            swap(s[left], s[right]);
            left++;
            right--;
        }
        return s;
    }

    // -------------------------------------------------------------------------
    // Function 3: Reverse Integer Array (General Array Style)
    // -------------------------------------------------------------------------
    void reverseArray(vector<int>& arr) {
        int left = 0;
        int right = arr.size() - 1;

        while (left < right) {
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // -------------------------------------------------------------------------
    // Alternative: Recursive Implementation
    // -------------------------------------------------------------------------
    void reverseArrayRecursive(vector<int>& arr, int left, int right) {
        // Base case: pointers cross or meet
        if (left >= right) return;

        // Swap boundary elements
        swap(arr[left], arr[right]);

        // Recurse for the inner subarray
        reverseArrayRecursive(arr, left + 1, right - 1);
    }
};

/*
Time Complexity: O(N)
- Exactly N / 2 swap operations are performed, where N is the length of the array/string.
- Linear time complexity: O(N).

Space Complexity: O(1) Auxiliary Space
- Iterative Two-Pointer method uses only two integer pointers (`left` and `right`).
- Performs in-place mutation without allocating additional arrays.
- (Note: Recursive version takes O(N / 2) = O(N) auxiliary stack space).

Key Insights:
1. In-place Swapping:
   - Direct swap avoids $O(N)$ extra memory allocation, keeping space $O(1)$.
2. Termination Condition:
   - `left < right` correctly handles both even and odd length inputs:
     * Odd length (e.g., 5 elements): `left == right` at index 2 (middle element remains in place).
     * Even length (e.g., 4 elements): pointers cross when `left == 2` and `right == 1`.
3. Standard Library:
   - In competitive programming or production C++, `std::reverse(arr.begin(), arr.end())` from `<algorithm>`
     implements this exact two-pointer logic with compiler-level loop unrolling.
*/
