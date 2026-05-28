/*
Problem: Odd Even Problem

Given a string s of lowercase English characters, determine whether the summation of x and y is EVEN or ODD.
where:
x is the count of distinct characters that occupy even positions in the English alphabet and have even frequency.
y is the count of distinct characters that occupy odd positions in the English alphabet and have odd frequency.

Constraints:
1 <= |s| <= 10^5

--------------------------------------------------

Pattern:
Hashing / Frequency Array

--------------------------------------------------

Key Observation:
- We need to find the frequency of each character in the string `s`.
- Since the string only contains lowercase English letters, a simple array of size 26 acts as a highly efficient hash map.
- The 1-based position of a character in the English alphabet can simply be derived via `(char - 'a') + 1`.
- After populating the frequency array, we just analyze the 26 possible alphabet characters to see if their position parity perfectly matches their frequency parity (even-even for x, odd-odd for y).

--------------------------------------------------

Approach:
1. Create a `vector<int> freq` of size 26 initialized to 0.
2. Traverse the string `s` and increment `freq[c - 'a']` for each character `c`.
3. Initialize two counters, `x = 0` and `y = 0`.
4. Loop through the `freq` array from index 0 to 25:
    a. Skip if the frequency is 0 (since the character doesn't exist in the string).
    b. Calculate the 1-based position in the alphabet: `pos = i + 1`.
    c. If `pos` is even and `freq[i]` is even, increment `x`.
    d. If `pos` is odd and `freq[i]` is odd, increment `y`.
5. Return "EVEN" if `(x + y) % 2 == 0`, else return "ODD".

--------------------------------------------------

Time Complexity: O(|s|) to build the frequency map. The subsequent loop runs exactly 26 times, which is O(1).
Space Complexity: O(1) as the frequency array size is strictly fixed at 26 regardless of the input string size.

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/help-nobita0532/1
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string oddEven(string s) {
        vector<int> freq(26, 0);
        
        // Populate frequency map
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        int x = 0;
        int y = 0;
        
        // Analyze frequency and position parities
        for (int i = 0; i < 26; ++i) {
            if (freq[i] > 0) {
                int pos = i + 1; // 1-based alphabet position
                
                if (pos % 2 == 0 && freq[i] % 2 == 0) {
                    x++;
                } else if (pos % 2 != 0 && freq[i] % 2 != 0) {
                    y++;
                }
            }
        }
        
        // Return result
        if ((x + y) % 2 == 0) {
            return "EVEN";
        }
        return "ODD";
    }
};
