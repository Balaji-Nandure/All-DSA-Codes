/*
================================================================================
PROBLEM: Consecutive 1's not allowed (GFG - Medium - DP)
================================================================================

PROBLEM STATEMENT:
Given a positive integer n, count all possible distinct binary strings of 
length n such that there are NO CONSECUTIVE 1's in any string.

Examples:
1. n = 1
   Output: 2
   Strings: "0", "1"

2. n = 2
   Output: 3
   Strings: "00", "01", "10" (NOT "11" because it has consecutive 1's)

3. n = 3
   Output: 5
   Strings: "000", "001", "010", "100", "101"
   (NOT: "011", "110", "111" - all have consecutive 1's)

Constraints:
- 1 ≤ n ≤ 44

================================================================================
MATHEMATICAL INSIGHT:
================================================================================

At position i, we have 2 choices:
1. Place 0 → previous position can be anything
   → Count = all valid strings of length (i-1)
   
2. Place 1 → previous position MUST be 0
   → Count = all valid strings of length (i-2) (to ensure 0 before this 1)

Therefore:
dp[i] = dp[i-1] + dp[i-2]

This is FIBONACCI-LIKE recurrence!

Base Cases:
- n=1: "0" or "1" → 2 strings (both valid)
- n=2: "00", "01", "10" → 3 strings

Verification:
- dp[1] = 2 (base case)
- dp[2] = 3 (base case)
- dp[3] = dp[2] + dp[1] = 3 + 2 = 5 ✓
- dp[4] = dp[3] + dp[2] = 5 + 3 = 8 ✓

================================================================================
COMPARISON OF APPROACHES:
================================================================================

Approach     | Time      | Space         | When to use
Recursion    | O(2^N)    | O(N)          | Learning only
Memoization  | O(N)      | O(N) + stack  | Interview
Tabulation   | O(N)      | O(N)          | Standard choice
Space Opt    | O(N)      | O(1)          | BEST ✓

================================================================================
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;


// ============================================================
// APPROACH 1: RECURSION (Brute Force)
// Time: O(2^N), Space: O(N) recursion stack
// ============================================================
/*
HOW IT WORKS:
At each position i (starting from 0):
- Option 1: Place '0' → recurse to position i+1 (no restriction)
- Option 2: Place '1' → recurse to position i+1, but mark last as '1'
           (next position CANNOT be '1' to avoid consecutive 1's)

Base case: When i == n, we've formed a valid string → count = 1

WHY THIS WORKS:
- Explores all possible binary strings
- Ensures no consecutive 1's during construction
- Every string that reaches length n is valid

COMPLEXITY:
- Time: O(2^N) - at each position, up to 2 choices (but less due to constraint)
- Space: O(N) - recursion call stack depth

WHEN TO USE:
- Understanding the pattern
- Very small n (n ≤ 20)
- Interview: explain intuition


DRY RUN: n = 3

solveRec(0, false):  [at position 0, last was not 1]
├─ Place '0' → solveRec(1, false)
│  ├─ Place '0' → solveRec(2, false)
│  │  ├─ Place '0' → solveRec(3, false) → return 1 ✓ "000"
│  │  └─ Place '1' → solveRec(3, true) → return 1 ✓ "001"
│  └─ Place '1' → solveRec(2, true)
│     └─ Only '0' allowed → solveRec(3, false) → return 1 ✓ "010"
└─ Place '1' → solveRec(1, true)
   └─ Only '0' allowed → solveRec(2, false)
      ├─ Place '0' → solveRec(3, false) → return 1 ✓ "100"
      └─ Place '1' → solveRec(3, true) → return 1 ✓ "101"

Total: 1 + 1 + 1 + 1 + 1 = 5 ✓
*/

class Solution1 {
private:
    long long solveRec(int pos, bool lastIs1, int n) {
        // Base case: reached the end of string
        if(pos == n)
            return 1;  // One valid string formed
        
        long long count = 0;
        
        // Option 1: Always can place 0
        count += solveRec(pos + 1, false, n);
        
        // Option 2: Can place 1 only if last position was NOT 1
        if(!lastIs1) {
            count += solveRec(pos + 1, true, n);
        }
        
        return count;
    }
    
public:
    long long countStrings(int n) {
        return solveRec(0, false, n);
    }
};


// ============================================================
// APPROACH 2: MEMOIZATION (Top-Down DP)
// Time: O(N), Space: O(N) + recursion stack
// ============================================================
/*
HOW IT WORKS:
Same as recursion, but cache results using a map.

State: (pos, lastIs1)
- pos: current position (0 to n)
- lastIs1: whether last character was 1 (true/false)

With memoization:
- Each (pos, lastIs1) pair computed only ONCE
- Subsequent calls return cached result immediately

WHY THIS WORKS:
- Eliminates exponential recomputation
- (pos, lastIs1) has only O(N) × 2 = O(N) possible states
- Each state computed once in O(1) → Total O(N)

COMPLEXITY:
- Time: O(N) - each state computed once
- Space: O(N) - memo storage + recursion stack

WHEN TO USE:
- When recursion is natural to express
- Interviews: show caching technique
- Constraint: recursive depth (here fine for n ≤ 44)


DRY RUN: n = 3

solveM(0, false):
├─ memo[(0,false)] doesn't exist
├─ Place '0' → solveM(1, false)
│  ├─ solveM(1, false):
│  │  ├─ Place '0' → solveM(2, false)
│  │  │  ├─ Place '0' → solveM(3, false) = 1 (base case)
│  │  │  └─ Place '1' → solveM(3, true) = 1 (base case)
│  │  │  → memo[(2,false)] = 2
│  │  └─ Place '1' → solveM(2, true)
│  │     └─ Place '0' → solveM(3, false) = 1
│  │     → memo[(2,true)] = 1
│  │  → memo[(1,false)] = 3
└─ Place '1' → solveM(1, true)
   └─ solveM(1, true):
      └─ Place '0' → solveM(2, false)
         → memo[(2,false)] = 2 (already cached!)
      → memo[(1,true)] = 2

memo[(0,false)] = 3 + 2 = 5 ✓

Notice: memo[(2,false)] was accessed twice but computed only ONCE!
*/

class Solution2 {
private:
    map<pair<int,bool>, long long> memo;
    
    long long solveMemo(int pos, bool lastIs1, int n) {
        // Base case
        if(pos == n)
            return 1;
        
        // Check if already computed
        pair<int,bool> state = {pos, lastIs1};
        if(memo.find(state) != memo.end())
            return memo[state];
        
        long long count = 0;
        
        // Option 1: Place 0
        count += solveMemo(pos + 1, false, n);
        
        // Option 2: Place 1 only if last was not 1
        if(!lastIs1) {
            count += solveMemo(pos + 1, true, n);
        }
        
        // Cache and return
        return memo[state] = count;
    }
    
public:
    long long countStrings(int n) {
        memo.clear();
        return solveMemo(0, false, n);
    }
};


// ============================================================
// APPROACH 3: TABULATION (Bottom-Up DP)
// Time: O(N), Space: O(N)
// ============================================================
/*
HOW IT WORKS:
Build DP table bottom-up using simple Fibonacci observation:

Define:
- dp[i] = count of valid strings of length i

Recurrence:
- dp[i] = dp[i-1] + dp[i-2]

Why?
- Strings of length i can end with 0 or 1
- If end with 0: any valid string of length i-1 works → dp[i-1]
- If end with 1: previous must be 0, so i-1 must end with validated
  string where position i-2 can be 0 or 1 → dp[i-2]

COMPLEXITY:
- Time: O(N) - single loop from 1 to n
- Space: O(N) - DP array of size n+1

WHEN TO USE:
- Standard DP choice
- No recursion overhead
- Clear iterative logic


DRY RUN: n = 3

Initialization:
dp[1] = 2  (base: "0", "1")
dp[2] = 3  (base: "00", "01", "10")

Fill table:
dp[3] = dp[2] + dp[1] = 3 + 2 = 5

Table visualization:
Position  1    2    3
Count     2    3    5
Meaning:  2    3    5 valid strings


For n = 5:
dp[1] = 2
dp[2] = 3
dp[3] = dp[2] + dp[1] = 3 + 2 = 5
dp[4] = dp[3] + dp[2] = 5 + 3 = 8
dp[5] = dp[4] + dp[3] = 8 + 5 = 13 ✓
*/

class Solution3 {
public:
    long long countStrings(int n) {
        // Base cases
        if(n == 1) return 2;
        if(n == 2) return 3;
        
        // DP array: dp[i] = count of valid strings of length i
        vector<long long> dp(n + 1);
        
        // Base cases
        dp[1] = 2;  // "0", "1"
        dp[2] = 3;  // "00", "01", "10"
        
        // Fill the table
        for(int i = 3; i <= n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[n];
    }
};


// ============================================================
// APPROACH 4: SPACE OPTIMIZED (Best Solution)
// Time: O(N), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
Use the Fibonacci recurrence but only track last 2 values:
dp[i] = dp[i-1] + dp[i-2]

Instead of storing entire array, use:
- prev2 = dp[i-2]
- prev1 = dp[i-1]
- current = dp[i] = prev1 + prev2

After each iteration:
- prev2 = prev1
- prev1 = current

WHY THIS WORKS:
- We only need the last two values to compute the next
- No need for entire DP array
- Sliding window approach

COMPLEXITY:
- Time: O(N) - single loop
- Space: O(1) - only 2 variables


DRY RUN: n = 5

Initial:
prev2 = 2 (dp[1])
prev1 = 3 (dp[2])

i = 3:
current = prev1 + prev2 = 3 + 2 = 5
prev2 = 3, prev1 = 5

i = 4:
current = prev1 + prev2 = 5 + 3 = 8
prev2 = 5, prev1 = 8

i = 5:
current = prev1 + prev2 = 8 + 5 = 13
prev2 = 8, prev1 = 13

Return: 13 ✓

Memory saved: O(N) → O(1)
*/

class Solution {
public:
    long long countStrings(int n) {
        // Base cases
        if(n == 1) return 2;
        if(n == 2) return 3;
        
        // Space optimized: only track last 2 values
        long long prev2 = 2;   // dp[1]
        long long prev1 = 3;   // dp[2]
        
        // Compute from position 3 to n
        for(int i = 3; i <= n; i++) {
            long long current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }
        
        return prev1;
    }
};


/*
================================================================================
EDGE CASES:
================================================================================

1. n = 1:
   Output: 2
   Strings: "0", "1"
   Both valid (no consecutive 1's in single character)

2. n = 2:
   Output: 3
   Valid: "00", "01", "10"
   Invalid: "11" (consecutive 1's)

3. n = 44:
   Output: 1134903170
   Large n, need long long to avoid overflow

================================================================================
TEST CASES:
================================================================================

Test 1: n = 1
All approaches: 2 ✓

Test 2: n = 2
All approaches: 3 ✓

Test 3: n = 3
All approaches: 5 ✓

Test 4: n = 4
Expected: 8 (Fibonacci: 5 + 3)
All approaches: 8 ✓

Test 5: n = 5
Expected: 13 (Fibonacci: 8 + 5)
All approaches: 13 ✓

================================================================================
PATTERN RECOGNITION:
================================================================================

This problem exhibits FIBONACCI PATTERN:

Output sequence: 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, ...

Notice:
- Each term = sum of previous 2 terms
- F(n) = F(n-1) + F(n-2)
- Classic DP recurrence

Other problems with same pattern:
- Climb stairs (1 or 2 steps)
- House robber (pick non-adjacent)
- Max sum non-adjacent
- Jump game variations

KEY INSIGHT: Recognize Fibonacci-like patterns in DP!

================================================================================
APPROACH COMPARISON:
================================================================================

Approach 1 (Recursion):
✓ Easy to understand
✗ Exponential time - too slow for n > 20
✗ Recursion depth limit

Approach 2 (Memoization):
✓ Top-down thinking
✓ Recursive elegance with caching
✗ Recursion depth (okay for n ≤ 44)
✗ Slightly more complex

Approach 3 (Tabulation):
✓ Standard iterative DP
✓ No recursion overhead
✓ Clear bottom-up building
✗ O(N) space used

Approach 4 (Space Optimized): ✓ BEST
✓ All advantages of Approach 3
✓ O(1) space - absolutely minimal
✓ Production code choice
✓ Interview follow-up: "Can we optimize space?"

RECOMMENDATION: Use Solution4 (Space Optimized) for final answer
                But know all 4 for complete understanding!

================================================================================
SPECIAL NOTES:
================================================================================

1. Why long long?
   - n can be up to 44
   - F(44) ≈ 1.13 × 10^9 > INT_MAX (2.14 × 10^9)
   - Safe to use long long to avoid overflow

2. Why Fibonacci works here?
   - At each position, only care about constraint from previous
   - Either place 0 (any previous state) or 1 (only if prev was 0)
   - Leads to: dp[i] = dp[i-1] + dp[i-2]

3. Interview discussion points:
   - Recognize the Fibonacci recurrence
   - Start with recursion, then optimize
   - Discuss space-time tradeoffs
   - Mention overflow for large n

================================================================================
*/
