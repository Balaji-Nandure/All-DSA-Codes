#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Transform String (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/transform-string5648/1
 *
 * Problem Statement:
 *   Given two strings A and B. Find the minimum number of steps required to transform
 *   string A into string B. The only allowed operation for the transformation is selecting
 *   a character from string A and inserting it in the beginning of string A.
 *   If transformation is not possible, return -1.
 *
 * Core Intuition / Idea:
 *   - The allowed operation is moving a character to the front. This means characters that
 *     remain in their relative positions from the end (right-to-left) do not need to be moved.
 *   - Our goal is to find the longest suffix of B that appears as a subsequence in A. These
 *     characters can remain untouched.
 *   - Any character in A that is not part of this matching subsequence must be moved to the front.
 *   - Thus, by scanning both strings from right to left:
 *     - If A[i] matches B[j], it stays in place. We move both pointers.
 *     - If A[i] doesn't match B[j], A[i] must be moved to the front. We increment our operation count,
 *       decrement `i`, and keep `j` at the same character of B to find the next match.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Length & Anagram Check:** If A.length() != B.length(), transformation is impossible, return -1.
 *       Use a frequency count array of size 256. Increment counts for characters in A, decrement for B.
 *       If any character count is not 0, they are not anagrams, so return -1.
 *   2️⃣ **Two-Pointer Scan From Right to Left:** Start index `i` at the end of A (`A.length() - 1`)
 *       and `j` at the end of B (`B.length() - 1`).
 *   3️⃣ **Count Operations:**
 *       - If A[i] == B[j], the character is in the correct relative position. Decrement both `i` and `j`.
 *       - If A[i] != B[j], we must eventually move A[i] to the front. Increment operation count (`ans++`) and decrement `i`.
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N) where N = A.length(). We scan the strings at most twice (once for frequencies, once with pointers).
 *   - Space Complexity (SC): O(1) auxiliary space as we use a fixed-size frequency array of 256.
 *
 * Dry Run:
 *   A = "abd", B = "bad"
 *   - Step 1: Anagram check passes since both strings have count['a']=1, count['b']=1, count['d']=1.
 *   - Step 2: Initialize i = 2 (points to 'd' in A), j = 2 (points to 'd' in B), ans = 0.
 *   - Loop 1: A[2] ('d') == B[2] ('d')
 *             -> Match found! Decrement both: i = 1, j = 1.
 *   - Loop 2: A[1] ('b') != B[1] ('a')
 *             -> Mismatch. We must move A[1] ('b') to front.
 *             -> Increment ans = 1, decrement i = 0. (j remains 1).
 *   - Loop 3: A[0] ('a') == B[1] ('a')
 *             -> Match found! Decrement both: i = -1, j = 0.
 *   - Loop terminates since i < 0.
 *   - Return ans = 1.
 */


class Solution {
public:
    int transform (string A, string B) {
        if (A.length() != B.length()) return -1;
        
        // Step 1: Anagram check
        int count[256] = {0};
        for (char c : A) count[(unsigned char)c]++;
        for (char c : B) count[(unsigned char)c]--;
        for (int i = 0; i < 256; i++) {
            if (count[i] != 0) return -1;
        }
        
        // Step 2 & 3: Two-pointer check from right to left
        int i = A.length() - 1;
        int j = B.length() - 1;
        int ans = 0;
        
        while (i >= 0) {
            if (A[i] == B[j]) {
                i--;
                j--;
            } else {
                ans++;
                i--;
            }
        }
        
        return ans;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    cout << "Test 1 (abd -> bad): " << sol.transform("abd", "bad") << " (Expected: 1)" << endl;
    cout << "Test 2 (GeeksForGeeks -> ForGeeksGeeks): " << sol.transform("GeeksForGeeks", "ForGeeksGeeks") << " (Expected: 3)" << endl;
    return 0;
}
