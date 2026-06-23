#include <bits/stdc++.h>
using namespace std;

/*
 * @brief   Substrings of length k with k-1 distinct elements (GeeksforGeeks)
 * @link    https://practice.geeksforgeeks.org/problems/substrings-of-length-k-with-k-1-distinct-elements/1
 *
 * Problem Statement:
 *   Given a string S consisting of lowercase alphabets and an integer K. Find the count of all
 *   substrings of length K which have exactly K-1 distinct characters.
 *
 * Core Intuition / Idea:
 *   - We need to look at substrings of size K.
 *   - Instead of checking distinct characters for each substring from scratch (which would take O(N * K)),
 *     we can use a Sliding Window of size K.
 *   - By maintaining a frequency map of size 26 and a `distinct_count` variable representing the number of
 *     distinct characters inside the current window, we can slide the window in O(1) time per step.
 *   - When sliding the window to the right, we:
 *     1. Add the incoming character to our frequency map. If its count changes from 0 to 1, we increment `distinct_count`.
 *     2. Remove the outgoing character from our frequency map. If its count changes from 1 to 0, we decrement `distinct_count`.
 *     3. Check if `distinct_count == K - 1`. If yes, increment the valid substring count.
 *
 * Approach (Love Babbar Style - 3 Golden Steps):
 *   1️⃣ **Initialize First Window:** Populate the frequency map for the first K characters (indices 0 to K-1).
 *       Increment `distinct_count` whenever a character's frequency becomes 1.
 *   2️⃣ **First Window Check:** If the `distinct_count` is equal to `K - 1`, increment our answer count.
 *   3️⃣ **Slide the Window:** For indices `i` from `K` to `N - 1`:
 *       - Outgoing character `S[i - K]`: decrement its frequency. If it becomes 0, decrement `distinct_count`.
 *       - Incoming character `S[i]`: increment its frequency. If it becomes 1, increment `distinct_count`.
 *       - If `distinct_count == K - 1`, increment the answer count.
 *
 * Complexity Analysis:
 *   - Time Complexity (TC): O(N) where N is the length of string `S`. We iterate through the string once.
 *   - Space Complexity (SC): O(1) auxiliary space, as the frequency array size is constant (26 lowercase English letters).
 *
 * Dry Run:
 *   S = "aabab", K = 3
 *   - Step 1: Initialize first window of size 3 ("aab" at indices 0..2)
 *             - S[0]='a' -> freq['a']=1 (distinct=1)
 *             - S[1]='a' -> freq['a']=2 (distinct=1)
 *             - S[2]='b' -> freq['b']=1 (distinct=2)
 *             - distinct_count = 2
 *   - Step 2: Check first window -> is distinct_count (2) == K - 1 (2)? Yes! ans = 1.
 *   - Step 3: Slide the window:
 *             - i = 3: Incoming S[3] ('a') -> freq['a'] = 3 (distinct remains 2)
 *                      Outgoing S[0] ('a') -> freq['a'] = 2 (distinct remains 2)
 *                      Window: "aba". distinct_count = 2.
 *                      Check: 2 == 2? Yes! ans = 2.
 *             - i = 4: Incoming S[4] ('b') -> freq['b'] = 2 (distinct remains 2)
 *                      Outgoing S[1] ('a') -> freq['a'] = 1 (distinct remains 2)
 *                      Window: "bab". distinct_count = 2.
 *                      Check: 2 == 2? Yes! ans = 3.
 *   - Return ans = 3.
 */

class Solution {
public:
    int countOfSubstrings(string S, int K) {
        int n = S.length();
        if (K > n) return 0;
        
        int freq[26] = {0};
        int distinct_count = 0;
        int ans = 0;
        
        // Step 1: Initialize first window of size K
        for (int i = 0; i < K; i++) {
            if (freq[S[i] - 'a'] == 0) {
                distinct_count++;
            }
            freq[S[i] - 'a']++;
        }
        
        // Step 2: Check first window
        if (distinct_count == K - 1) {
            ans++;
        }
        
        // Step 3: Slide the window from index K to n-1
        for (int i = K; i < n; i++) {
            // Outgoing character
            char outgoing = S[i - K];
            freq[outgoing - 'a']--;
            if (freq[outgoing - 'a'] == 0) {
                distinct_count--;
            }
            
            // Incoming character
            char incoming = S[i];
            if (freq[incoming - 'a'] == 0) {
                distinct_count++;
            }
            freq[incoming - 'a']++;
            
            // Check condition for the current window
            if (distinct_count == K - 1) {
                ans++;
            }
        }
        
        return ans;
    }
};

// Driver code (optional, for local testing)
int main() {
    Solution sol;
    cout << "Test 1 (abcc, k=2): " << sol.countOfSubstrings("abcc", 2) << " (Expected: 1)" << endl;
    cout << "Test 2 (aabab, k=3): " << sol.countOfSubstrings("aabab", 3) << " (Expected: 3)" << endl;
    return 0;
}
