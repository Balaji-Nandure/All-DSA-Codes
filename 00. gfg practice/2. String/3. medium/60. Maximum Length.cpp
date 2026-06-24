/*
    Problem Name: Maximum Length
    Difficulty: Medium
    Platform: GeeksforGeeks

    Problem Statement:
    Given the maximum occurrences of a, b, and c in a string. Your task is to make the string containing only a, b, and c such that no three consecutive characters are the same. If the resultant string equals to a+b+c, return the length (a+b+c) otherwise -1.

    Expected Complexities:
    Time Complexity: O(1). The logic relies on a simple mathematical condition. (Note: Expected is O(a+b+c) which implies we could build it, but math makes it O(1)).
    Space Complexity: O(1). No extra space needed.

    Love Babbar Style Approach:
    1. Mathematical Insight: To prevent three consecutive identical characters, we need to focus on the character with the maximum frequency (let's call its frequency `M`). 
    2. Grouping the Maximum Frequency Character: We can place this most frequent character in groups of at most 2 (e.g., "aa"). 
       - If we have `M` such characters, the minimum number of groups we can form is `ceil(M / 2.0)`.
       - To separate these groups so they don't merge into 3 consecutive characters, we need at least `ceil(M / 2.0) - 1` other characters.
       - Using integer arithmetic, the exact condition translates to ensuring the remaining characters (let's say sum `S`) can separate the groups: `S >= (M - 2) / 2`, which simplifies perfectly to `M <= 2 * S + 2`.
    3. Verification: We find the maximum of `a, b, c` which is `M`. The sum of the other two is `S`. 
       - If `M > 2 * S + 2`, we don't have enough separators to break up the most frequent character. Hence, return `-1`.
       - Otherwise, it is always mathematically possible to arrange them, so we just return the total length `a + b + c`.

    Dry Run:
    Input: a = 11, b = 2, c = 2
    - M (max frequency) = max(11, 2, 2) = 11.
    - S (sum of others) = 2 + 2 = 4.
    - Check condition: M <= 2 * S + 2
      - 11 <= 2 * 4 + 2
      - 11 <= 10 (False)
    - Since it's false, we can't arrange them. Return -1.
    
    Input: a = 3, b = 3, c = 3
    - M = 3
    - S = 3 + 3 = 6
    - Check condition: 3 <= 2 * 6 + 2 -> 3 <= 14 (True)
    - Result: return 3 + 3 + 3 = 9.
*/

#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int solve(int a, int b, int c) {
        int max_freq = max({a, b, c});
        int others_sum = a + b + c - max_freq;
        
        // Mathematical condition: max_freq cannot exceed 2 * (others_sum) + 2
        if (max_freq <= 2 * others_sum + 2) {
            return a + b + c;
        }
        
        return -1;
    }
};

int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            int a, b, c;
            cin >> a >> b >> c;
            Solution ob;
            cout << ob.solve(a, b, c) << "\n";
        }
    }
    return 0;
}
