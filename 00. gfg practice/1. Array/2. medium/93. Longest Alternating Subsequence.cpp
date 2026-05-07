/*
Problem: Longest Alternating Subsequence

GFG: https://www.geeksforgeeks.org/problems/longest-alternating-subsequence5251/1

Description:
You are given an array arr. Your task is to find the longest length of a good sequence. A good sequence {x1, x2, .. xn} is an alternating sequence if its elements satisfy one of the following relations :

1.  x1 < x2 > x3 < x4 > x5. . . . . and so on.
2.  x1 >x2 < x3 > x4 < x5. . . . . and so on.

Note: A subsequence is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.

Examples:

Input: arr[] = [1, 5, 4]
Output: 3
Explanation: The entire sequenece is a good sequence.

Input: arr[] = [1, 17, 5, 10, 13, 15, 10, 5, 16, 8]
Output: 7
Explanation: There are several subsequences that achieve this length. 
One maximum length good subsequences is [1, 17, 10, 13, 10, 16, 8].

Constraints:
1 ≤ arr.size() ≤ 10^5 
1 ≤ arr[i] ≤ 10^4 

Approach (Greedy):
Use two variables to track best alternating sequences ending at previous position.

Algorithm:
1. Initialize up = down = 1
2. For each element:
   - If current > previous: up = down + 1
   - If current < previous: down = up + 1
   - If equal: no change
3. Answer = max(up, down)

Time Complexity: O(n)
Space Complexity: O(1)

Why Greedy Works:
- We only need the best sequence ending at previous position
- Any element that can extend the up sequence will create a longer up sequence
- Any element that can extend the down sequence will create a longer down sequence
- No need to track all previous elements, just the optimal ones
- This maintains optimal subsequence lengths at each step

Pattern: Wiggle Subsequence Greedy
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int alternatingMaxLength(vector<int>& arr) {
        
        int n = arr.size();
        
        if (n == 1) {
            return 1;
        }
        
        int up = 1;
        int down = 1;
        
        for (int i = 1; i < n; i++) {
            
            if (arr[i] > arr[i - 1]) {
                up = down + 1;
            }
            else if (arr[i] < arr[i - 1]) {
                down = up + 1;
            }
        }
        
        return max(up, down);
    }
};



/*
=====================================================
FINAL GFG CLASS
=====================================================

Return MOST OPTIMIZED solution.
*/

class Solution {
public:

    int alternatingMaxLength(vector<int>& arr) {
        
        SpaceOptimizationSolution obj;
        
        return obj.alternatingMaxLength(arr);
    }
};


/*
-----------------------------------------------------

🧠 STRIVER DP FLOW

Recursion
    ↓
Memoization
    ↓
Tabulation
    ↓
Space Optimization

-----------------------------------------------------

🔥 IMPORTANT INTERVIEW INSIGHT

This problem has:
    O(n²) DP solution

BUT ALSO:
    Greedy O(n) optimization

Very famous optimization from O(n²) to O(n).

-----------------------------------------------------

PATTERN:
Wiggle Subsequence DP

LEETCODE:
Wiggle Subsequence

-----------------------------------------------------

🎯 KEY TAKEAWAYS

1. State definition matters: up[] and down[] arrays
2. Greedy optimization possible for alternating patterns
3. Sometimes O(n²) DP can be optimized to O(n)
4. Understanding when to use greedy vs DP

-----------------------------------------------------
*/
