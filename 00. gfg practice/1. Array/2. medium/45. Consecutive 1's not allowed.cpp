/*
================================================================================
PROBLEM: Consecutive 1's Not Allowed (GFG)
================================================================================

Given length n, count number of binary strings of length n
such that there are NO CONSECUTIVE 1s.

Example:
n = 3
Valid strings: 000, 001, 010, 100, 101 → Answer = 5

================================================================================
INTUITION:
================================================================================

At each position we can place:
- '0' → always allowed
- '1' → only allowed if previous was NOT 1

So this is DP with RESTRICTION on previous element.

================================================================================
STATE DEFINITION:
================================================================================

dp[i][last]
- i = current position (0 to n)
- last = previous bit value (0 or 1)

RECURRENCE:

If last = 0:
    we can place 0 or 1
    → f(i,0) = f(i+1,0) + f(i+1,1)

If last = 1:
    we can place only 0
    → f(i,1) = f(i+1,0)

BASE CASE:
    If i == n → return 1 (one valid string formed)

================================================================================
IMPORTANT OBSERVATION: FIBONACCI PATTERN
================================================================================

This simplifies to Fibonacci recurrence:

dp[n] = dp[n-1] + dp[n-2]

Because:
- Strings ending in 0 = all valid strings of length n-1
- Strings ending in 1 = all valid strings of length n-2 (with 0 before this 1)

Sequence: 2, 3, 5, 8, 13, 21, 34, 55, ...

================================================================================
APPROACH COMPLEXITY:
================================================================================

Approach       | Time    | Space       | When to use
Recursion      | O(2^N)  | O(N)        | Learning only, n ≤ 20
Memoization    | O(N)    | O(N) stack  | Interview, recursive approach
Tabulation     | O(N)    | O(N)        | Standard DP choice
Space Opt      | O(N)    | O(1)        | BEST ✓ Production code

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;


// ============================================================
// APPROACH 1: RECURSION
// Time: O(2^N), Space: O(N) recursion stack
// ============================================================
/*
HOW IT WORKS:
At position i, based on previous bit (last):
- If last = 0: can place 0 or 1 → explore both
- If last = 1: can only place 0 → explore only 0

Base: i == n → return 1 (one valid string)

WHY THIS WORKS:
- Explores all possibilities
- Ensures no consecutive 1s during building

DATA FLOW:
Position 0 (last=0)
├─ Place 0 → Position 1 (last=0) → continues...
└─ Place 1 → Position 1 (last=1) → can only place 0 next


DRY RUN: n = 2

solveRec(0, 0, 2):
├─ Place 0 → solveRec(1, 0, 2)
│  ├─ Place 0 → solveRec(2, 0, 2) = 1 ✓ "00"
│  └─ Place 1 → solveRec(2, 1, 2) = 1 ✓ "01"
│  → Total = 2
└─ Place 1 → solveRec(1, 1, 2)
   └─ Place 0 → solveRec(2, 0, 2) = 1 ✓ "10"
   → Total = 1

Answer: 2 + 1 = 3 ✓
*/

// ============================================================
// APPROACH 2: MEMOIZATION
// Time: O(N), Space: O(N) + recursion stack
// ============================================================
/*
HOW IT WORKS:
Same as recursion but cache results in 2D DP table.

State: dp[i][last]
- Each (i, last) state computed only ONCE
- Total states: O(N) × 2 = O(N)

WHY THIS WORKS:
- Avoids exponential recomputation
- (i, 0) and (i, 1) each computed once

Cache benefitDRY RUN: n = 2

solveM(0, 0, 2):
├─ (0,0) not in cache
├─ Place 0 → solveM(1, 0, 2):
│  ├─ (1,0) not in cache
│  ├─ solveM(2, 0, 2) = 1
│  ├─ solveM(2, 1, 2) = 1
│  ├─ cache[(1,0)] = 2
├─ Place 1 → solveM(1, 1, 2):
│  ├─ (1,1) not in cache
│  ├─ solveM(2, 0, 2) = 1 (base case, not cached)
│  ├─ cache[(1,1)] = 1
├─ cache[(0,0)] = 3

Answer: 3 ✓
*/

// ============================================================
// APPROACH 3: TABULATION
// Time: O(N), Space: O(N)
// ============================================================
/*
HOW IT WORKS:
Build DP table backward from position n to 0.

dp[i][0] = dp[i+1][0] + dp[i+1][1]  (can place 0 then either bit)
dp[i][1] = dp[i+1][0]               (can place 0 only)

Base: dp[n][0] = dp[n][1] = 1

WHY THIS WORKS:
- Build from known base cases
- Iterative, no recursion overhead

DP Table for n=2:

Position  | last=0 | last=1
----------|--------|--------
n=2       |   1    |   1    (base)
n=1       |   2    |   1    (dp[1][0] = 1+1, dp[1][1] = 1)
n=0       |   3    |   2    (dp[0][0] = 2+1, dp[0][1] = 2)

Answer: dp[0][0] = 3 ✓
*/

// ============================================================
// APPROACH 4: SPACE OPTIMIZED
// Time: O(N), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
Observe FIBONACCI pattern:

dp[n] = dp[n-1] + dp[n-2]

because:
- Valid strings of length n ending with 0
  = all valid strings of length n-1
- Valid strings of length n ending with 1
  = all valid strings of length n-2 (with mandatory 0 before 1)

Use only prev1 and prev2 variables:

dp[1] = 2   → "0", "1"
dp[2] = 3   → "00", "01", "10"
dp[3] = 5   = dp[2] + dp[1] = 3 + 2
dp[4] = 8   = dp[3] + dp[2] = 5 + 3

WHY THIS WORKS:
- Only need last 2 values
- Sliding window approach
- Minimal space

Sequence: 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...
This is Fibonacci with base = 2, 3!
*/


class Solution {
public:
    
    // ============================================================
    // RECURSION
    // ============================================================
    int solveRec(int i, int last, int n) {
        if(i == n) return 1;  // Base case: reached end
        
        if(last == 1) {
            // Previous was 1 → can only place 0
            return solveRec(i + 1, 0, n);
        }
        else {
            // Previous was 0 → can place 0 or 1
            return solveRec(i + 1, 0, n) + solveRec(i + 1, 1, n);
        }
    }
    
    
    // ============================================================
    // MEMOIZATION
    // ============================================================
    int solveMemo(int i, int last, int n, vector<vector<int>>& dp) {
        if(i == n) return 1;
        
        // Check cache
        if(dp[i][last] != -1)
            return dp[i][last];
        
        if(last == 1) {
            return dp[i][last] = solveMemo(i + 1, 0, n, dp);
        }
        else {
            return dp[i][last] = solveMemo(i + 1, 0, n, dp)
                               + solveMemo(i + 1, 1, n, dp);
        }
    }
    
    
    // ============================================================
    // TABULATION
    // ============================================================
    int solveTab(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));
        
        // Base cases
        dp[n][0] = dp[n][1] = 1;
        
        // Fill table backward from n-1 to 0
        for(int i = n - 1; i >= 0; i--) {
            dp[i][1] = dp[i + 1][0];                    // If last=1, can place 0
            dp[i][0] = dp[i + 1][0] + dp[i + 1][1];   // If last=0, can place 0 or 1
        }
        
        return dp[0][0];  // Starting from position 0 with last=0
    }
    
    
    // ============================================================
    // SPACE OPTIMIZED (FIBONACCI)
    // ============================================================
    int solveSpace(int n) {
        if(n == 1) return 2;      // "0", "1"
        if(n == 2) return 3;      // "00", "01", "10"
        
        int prev2 = 2;  // dp[1]
        int prev1 = 3;  // dp[2]
        
        for(int i = 3; i <= n; i++) {
            int curr = prev1 + prev2;
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    
    // ============================================================
    // MAIN FUNCTION - Choose approach
    // ============================================================
    int countStrings(int n) {
        // Recursion (SLOW - only for learning, n ≤ 20)
        // return solveRec(0, 0, n);
        
        // Memoization (Good for interviews, n ≤ 44)
        // vector<vector<int>> dp(n, vector<int>(2, -1));
        // return solveMemo(0, 0, n, dp);
        
        // Tabulation (Standard choice, n ≤ 44)
        // return solveTab(n);
        
        // Space Optimized (BEST - use this)
        return solveSpace(n);
    }
};


/*
================================================================================
DRY RUNS:
================================================================================

n = 1:
All approaches → 2 ✓
Strings: "0", "1"

n = 2:
All approaches → 3 ✓
Strings: "00", "01", "10"

n = 3:
All approaches → 5 ✓
Strings: "000", "001", "010", "100", "101"

n = 4:
Expected: 8 (Fibonacci: 5 + 3)
Strings: 8 valid strings

n = 5:
Expected: 13 (Fibonacci: 8 + 5)

================================================================================
PATTERN RECOGNITION:
================================================================================

This problem exhibits FIBONACCI PATTERN:

Output Sequence: 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...

Formula: dp[n] = dp[n-1] + dp[n-2]

Other problems with same pattern:
✓ Climbing stairs (1 or 2 steps)
✓ House robber (pick non-adjacent)
✓ Max sum without adjacent
✓ Jump game variations

KEY INSIGHT: Recognize Fibonacci patterns in DP!

================================================================================
COMPLEXITY COMPARISON:
================================================================================

Approach 1 (Recursion):
✓ Easy to understand
✗ Exponential time - too slow for n > 20
✗ Recursion depth limit issues


Approach 2 (Memoization):
✓ Top-down thinking
✓ Recursive elegance with caching
✓ Works for n ≤ 44


Approach 3 (Tabulation):
✓ Iterative, no recursion overhead
✓ Clear bottom-up building
✗ O(N) space used


Approach 4 (Space Optimized): ✓ BEST
✓ All advantages of Approach 3
✓ O(1) space - absolutely minimal
✓ Production code choice
✓ Interview follow-up: "Can we optimize space?"

================================================================================
WHY FIBONACCI WORKS:
================================================================================

At position i, consider the LAST bit:

Strings ending with 0:
  - Can append 0 to ANY valid string of length i-1
  - Count = dp[i-1]

Strings ending with 1:
  - Must have 0 before it
  - So comes from valid strings of length i-2, then append "01"
  - Count = dp[i-2]

Total: dp[i] = dp[i-1] + dp[i-2]

================================================================================
INTERVIEW DISCUSSION POINTS:
================================================================================

1. Recognize the Fibonacci recurrence:
   - Problem: "No consecutive X"
   - Solution: Usually leads to Fibonacci

2. Start with recursion, then optimize:
   Recursion → Memoization → Tabulation → Space Optimization

3. Discuss space-time tradeoffs:
   "Can we use less space?" → Yes, O(1) space optimized version

4. Edge cases:
   - n = 1 → 2
   - n = 44 → ~1 billion (use long long to avoid overflow)

5. Alternative formulation:
   - dp[i][0] = number of valid strings of length i ending with 0
   - dp[i][1] = number of valid strings of length i ending with 1
   - Then: dp[n] = dp[n][0] + dp[n][1]

================================================================================
*/
