/*
    Problem Name: Longest Repeating Character Replacement
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given a string s of length n consisting of uppercase English letters and an integer k, you are allowed to perform at most k operations. In each operation, you can change any character of the string to any other uppercase English letter.
    Determine the length of the longest substring that can be transformed into a string with all identical characters after performing at most k such operations.

    Expected Complexities:
    Time Complexity: O(N) where N is the length of string s.
    Space Complexity: O(1) as we only use a hash array of size 26.

    Love Babbar Style Approach:
    1. Sliding Window: We use a sliding window approach with two pointers, `left` and `right`. Both start at 0.
    2. Frequency Array: We maintain an array `hash` of size 26 to keep track of the frequency of each character in the current window `[left, right]`.
    3. Traversal: We iterate `right` from 0 to n-1. 
       - Add the current character `s[right]` to the frequency array and update `max_freq`, which stores the maximum frequency of any single character in the current window.
       - The number of characters to replace is given by `(window_length - max_freq)`.
       - If this number exceeds `k`, it means the current window is invalid. We must shrink the window by moving the `left` pointer to the right. We decrement the frequency of `s[left]` and increment `left`. (Note: we don't necessarily need to reduce `max_freq` because we are only looking for a longer window, and it naturally bounds the window size until a higher max_freq is found).
       - After ensuring the window is valid, we update the `max_len` with the current window length.
    4. Result: Return `max_len`.

    Dry Run:
    Input: s = "ADBD", k = 1
    Initialization: left = 0, right = 0, max_freq = 0, max_len = 0, hash[26] = {0}
    Iteration:
    - right = 0 (s[0]='A'): hash['A']=1, max_freq=1. Window len=1. Replace needed = 1-1 = 0 <= k. max_len=1.
    - right = 1 (s[1]='D'): hash['D']=1, max_freq=1. Window len=2. Replace needed = 2-1 = 1 <= k. max_len=2.
    - right = 2 (s[2]='B'): hash['B']=1, max_freq=1. Window len=3. Replace needed = 3-1 = 2 > k.
      - Invalid! Shrink window: hash['A']--, left=1. Window len=2.
    - right = 3 (s[3]='D'): hash['D']=2, max_freq=2. Window len=3 (left=1). Replace needed = 3-2 = 1 <= k. max_len=3.
    End of loop.
    Result: max_len = 3.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int characterReplacement(string s, int k) {
        int hash[26] = {0};
        int left = 0;
        int max_freq = 0;
        int max_len = 0;
        
        for (int right = 0; right < s.length(); right++) {
            hash[s[right] - 'A']++;
            max_freq = max(max_freq, hash[s[right] - 'A']);
            
            // Current window size is right - left + 1
            // If the number of characters to replace is greater than k, shrink the window
            if ((right - left + 1) - max_freq > k) {
                hash[s[left] - 'A']--;
                left++;
            }
            
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            string s;
            int k;
            cin >> s >> k;
            Solution ob;
            cout << ob.characterReplacement(s, k) << "\n";
        }
    }
    return 0;
}
