/*
GeeksforGeeks: Largest number in K swaps
Difficulty: Medium

Problem:
Given a number k and string s of digits denoting a positive integer, build the largest number possible by performing swap operations on the digits of s at most k times.

Examples:
Input: s = "1234567", k = 4
Output: 7654321
Explanation: Three swaps can make the input 1234567 to 7654321, swapping 1 with 7, 2 with 6 and finally 3 with 5.

Input: s = "3435335", k = 3
Output: 5543333
Explanation: Three swaps can make the input 3435335 to 5543333, swapping 3 with 5, 4 with 5 and finally 3 with 4.

Input: s = "1034", k = 2
Output: 4301
Explanation: Two swaps can make the input 1034 to 4301, swapping 1 with 4 and finally 0 with 3. 

Constraints:
1 <= s.size() <= 15
1 <= k <= 7

Core Idea:
Since the size of s (<= 15) and k (<= 7) are very small, we can use backtracking (DFS) to explore swap choices.
To optimize/pruning:
- At any index `idx` (from left to right):
  - Find the maximum digit character in `s[idx...n-1]`.
  - If the maximum digit is greater than `s[idx]`, we should swap `s[idx]` with all occurrences of this maximum digit in `s[idx+1...n-1]`.
  - Decrement `k` (since we perform a swap) and recurse for the next index `idx + 1`.
  - Backtrack after the recursive call by swapping the characters back.
  - If the maximum digit is equal to `s[idx]`, it means the current position is already optimal (no larger digit is available to its right to swap with). In this case, we simply move to the next index `idx + 1` without using a swap.

Approach:
1. Define a helper function `findMax(string s, int k, int idx, string& maxStr)`.
2. Inside the helper, if `k == 0` or `idx == s.length() - 1`, return.
3. Find the maximum character `maxChar` in the range `[idx, s.length() - 1]`.
4. If `maxChar == s[idx]`, we cannot improve the digit at `idx`. Recurse to `findMax(s, k, idx + 1, maxStr)`.
5. If `maxChar > s[idx]`, iterate `i` from `idx + 1` to `s.length() - 1`:
   - If `s[i] == maxChar`, swap `s[idx]` and `s[i]`.
   - Update `maxStr = max(maxStr, s)`.
   - Recurse: `findMax(s, k - 1, idx + 1, maxStr)`.
   - Swap back to backtrack.
6. Initialize `maxStr = s` and call `findMax(s, k, 0, maxStr)`.
7. Return `maxStr`.

Time Complexity: O(N^K) in the worst case, but heavily pruned since we only swap with occurrences of the maximum character.
Space Complexity: O(N) auxiliary space due to recursion call stack.

GFG Link: https://www.geeksforgeeks.org/problems/largest-number-in-k-swaps-1587115620/1
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    void findMax(string s, int k, int idx, string& maxStr) {
        // Base case: no swaps left or reached the end of the string
        if (k == 0 || idx == s.length() - 1) {
            return;
        }
        
        // Find the maximum digit in s[idx...n-1]
        char maxChar = s[idx];
        for (int i = idx + 1; i < s.length(); i++) {
            if (s[i] > maxChar) {
                maxChar = s[i];
            }
        }
        
        // If the current digit is already the maximum possible, do not swap.
        // Just move to the next index.
        if (maxChar == s[idx]) {
            findMax(s, k, idx + 1, maxStr);
            return;
        }
        
        // Try swapping the current digit with all occurrences of maxChar to its right
        for (int i = idx + 1; i < s.length(); i++) {
            if (s[i] == maxChar) {
                // Swap
                swap(s[idx], s[i]);
                
                // Keep track of the largest string seen so far
                if (s > maxStr) {
                    maxStr = s;
                }
                
                // Recurse for the next index with k - 1 swaps
                findMax(s, k - 1, idx + 1, maxStr);
                
                // Backtrack
                swap(s[idx], s[i]);
            }
        }
    }

public:
    string findMaximumNum(string s, int k) {
        string maxStr = s;
        findMax(s, k, 0, maxStr);
        return maxStr;
    }
};

/*
Dry Run — Example:
s = "1034", k = 2

Initial: maxStr = "1034"
findMax("1034", k=2, idx=0, maxStr)
  - maxChar in s[0...] is '4'
  - '4' > s[0] ('1')
  - Swap s[0] and s[3] ('4') -> s = "4031"
  - s > maxStr -> maxStr = "4031"
  - Recurse findMax("4031", k=1, idx=1, maxStr)
    - maxChar in s[1...] is '3'
    - '3' > s[1] ('0')
    - Swap s[1] and s[2] ('3') -> s = "4301"
    - s > maxStr -> maxStr = "4301"
    - Recurse findMax("4301", k=0, idx=2, maxStr) -> Base case: k=0, returns.
    - Backtrack s = "4031"
  - Backtrack s = "1034"

Output: "4301"
*/
