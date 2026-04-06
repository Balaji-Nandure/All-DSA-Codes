/*
PROBLEM: Max Sum without Adjacents (GFG)

Given an array of positive integers, find the maximum sum of a subsequence
such that no two numbers in the subsequence are adjacent in the original array.

Examples:
arr = [5, 5, 10, 100, 10, 5]
Output: 110
→ Pick indices 0, 3, 5 → 5 + 100 + 5 = 110 (non-adjacent)

arr = [3, 2, 7, 10]
Output: 13
→ Pick indices 0, 3 → 3 + 10 = 13 (non-adjacent)

arr = [9, 1, 6, 10]
Output: 19
→ Pick indices 0, 3 → 9 + 10 = 19 (non-adjacent)

--------------------------------------------------

STRIVER DP FLOW (VERY IMPORTANT):
1. Recursion
2. Memoization
3. Tabulation
4. Space Optimization

This problem follows PICK / NOT PICK pattern.

--------------------------------------------------

1. RECURSION APPROACH (Top Down Thinking)

Idea:
At every index i, we have two choices:

Choice 1: PICK arr[i]
  → We take arr[i]
  → We CANNOT pick arr[i-1] (adjacent constraint)
  → So recurse on i-2
  → Total = arr[i] + solve(i-2)

Choice 2: NOT PICK arr[i]
  → We skip arr[i]
  → We can still consider arr[i-1]
  → Recurse on i-1
  → Total = solve(i-1)

Recurrence:
solve(i) = max(
    arr[i] + solve(i-2),    // pick
    solve(i-1)              // not pick
)

Base cases:
solve(-1) = 0 (no elements)
solve(0) = arr[0] (one element, must pick)

Time Complexity: O(2^N) - at each step, 2 choices
Space Complexity: O(N) - recursion call stack

--------------------------------------------------

2. MEMOIZATION (Top Down DP + Caching)

Problem with recursion:
solve(i) calls solve(i-1) and solve(i-2)
solve(i-1) calls solve(i-2) again
→ Same subproblems computed multiple times!

Solution:
Store results in dp[] array.
Before computing solve(i), check if already computed.

dp[i] = answer for index i

Time Complexity: O(N) - each subproblem solved once
Space Complexity: O(N) + O(N) = O(N)
  - dp array + recursion stack

--------------------------------------------------

3. TABULATION (Bottom Up DP)

Instead of solving from n → 0 (top-down),
build solution from 0 → n (bottom-up).

We iteratively compute dp[i] for i = 0 to n.

dp[i] = max(arr[i] + dp[i-2], dp[i-1])

Base:
dp[0] = arr[0]
dp[1] = max(arr[0], arr[1])

Why?
- dp[0] = pick first element
- dp[1] = pick either first or second (better one)

For i >= 2:
dp[i] = max(
    arr[i] + dp[i-2],  // pick current
    dp[i-1]            // skip current
)

Time Complexity: O(N)
Space Complexity: O(N)

--------------------------------------------------

4. SPACE OPTIMIZATION (Best)

Observation: dp[i] only depends on dp[i-1] and dp[i-2]

We don't need entire dp array!
Just store:
prev2 = dp[i-2]
prev1 = dp[i-1]

Then compute curr, and shift:
prev2 = prev1
prev1 = curr

Time Complexity: O(N)
Space Complexity: O(1) ← OPTIMAL!

--------------------------------------------------

TIME & SPACE COMPLEXITY SUMMARY:

Approach          | Time    | Space
Recursion         | O(2^N)  | O(N)
Memoization       | O(N)    | O(N)
Tabulation        | O(N)    | O(N)
Space Optimized   | O(N)    | O(1) ✓ BEST

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/max-sum-without-adjacents2430/1

LeetCode:
https://leetcode.com/problems/house-robber/

--------------------------------------------------
*/

class Solution {
  public:

    // ============================================================
    // APPROACH 1: RECURSION (Brute Force)
    // Time: O(2^N), Space: O(N) recursion stack
    // ============================================================
    /*
    HOW IT WORKS:
    
    At each index i, we make a CHOICE:
    
    Choice A: PICK arr[i]
             ├─ We take arr[i]
             ├─ We CANNOT use index i-1 (adjacent)
             ├─ So we recurse on (i-2)
             └─ Total = arr[i] + solve(i-2)
    
    Choice B: NOT PICK arr[i]
             ├─ We skip arr[i]
             ├─ We can use indices before i-1
             ├─ So we recurse on (i-1)
             └─ Total = solve(i-1)
    
    We return the MAXIMUM of both choices.
    
    WHY IT WORKS:
    By exploring ALL possible choices, we try every subsequence.
    The recursion tree branches out and explores all paths.
    
    EXAMPLE: arr = [3, 2, 7]
    
    solve(2)
    ├─ Pick 7
    │  ├─ solve(0) = 3 → return 7+3 = 10
    │
    └─ Not Pick 7
       └─ solve(1)
          ├─ Pick 2
          │  └─ solve(-1) = 0 → return 2+0 = 2
          │
          └─ Not Pick 2
             └─ solve(0) = 3 → return 3
    
    Max(10, Max(2, 3)) = 10
    
    PROBLEM: Explores same subproblems many times!
    solve(0) is called multiple times.
    This causes exponential time complexity O(2^N).
    
    BEST FOR: Learning, small arrays, understanding the idea
    */
    
    int solveRecursion(int i, vector<int>& arr) {
        // Base case: No elements
        if(i < 0) return 0;
        
        // Base case: One element (must pick it)
        if(i == 0) return arr[0];
        
        // Recursive case: Pick or Not Pick
        int pick = arr[i] + solveRecursion(i - 2, arr);    // Pick current + answer from i-2
        int notPick = solveRecursion(i - 1, arr);          // Skip current, answer from i-1
        
        return max(pick, notPick);
    }

    
    // ============================================================
    // APPROACH 2: MEMOIZATION (Top-Down DP)
    // Time: O(N), Space: O(N) dp array + O(N) recursion stack
    // ============================================================
    /*
    HOW IT WORKS:
    
    PROBLEM with Recursion:
    solve(2) calls solve(0) and solve(1)
    solve(1) also calls solve(0) → DUPLICATE!
    
    SOLUTION:
    Store results in dp[i] array first time we compute them.
    Before computing solve(i), CHECK if already computed.
    If computed, return from dp[]. Otherwise compute and store.
    
    WHY IT WORKS:
    We solve each unique subproblem EXACTLY ONCE.
    Each subproblem is indexed from 0 to n-1.
    So maximum n subproblems.
    Time: O(N)
    
    EXAMPLE: arr = [3, 2, 7]
    
    dp array (initially [-1, -1, -1])
    
    solve(2):
      dp[2] = -1? Not computed
      pick = 7 + solve(0)
      solve(0): dp[0] = -1? Not computed
                dp[0] = 3 → store
                return 3
      → pick = 7 + 3 = 10
      
      notPick = solve(1)
      solve(1): dp[1] = -1? Not computed
                pick = 2 + solve(-1) = 2 + 0 = 2
                notPick = solve(0): dp[0] = 3 → FOUND! return 3
                dp[1] = 3 → store
                return 3
      → notPick = 3
      
      dp[2] = max(10, 3) = 10 → store
      return 10
    
    If we call solve(1) again → dp[1] = 3 → directly return!
    
    WHEN TO USE:
    - Medium sized arrays
    - When recursion thinking is clearer
    - Interview followup: "Can you optimize further?"
    */
    
    int solveMemoization(int i, vector<int>& arr, vector<int>& dp) {
        // Base cases
        if(i < 0) return 0;
        if(i == 0) return arr[0];
        
        // Check memoization table
        if(dp[i] != -1) return dp[i];
        
        // Compute and store
        int pick = arr[i] + solveMemoization(i - 2, arr, dp);
        int notPick = solveMemoization(i - 1, arr, dp);
        
        return dp[i] = max(pick, notPick);  // Store result
    }

    
    // ============================================================
    // APPROACH 3: TABULATION (Bottom-Up DP)
    // Time: O(N), Space: O(N) dp array
    // ============================================================
    /*
    HOW IT WORKS:
    
    Instead of solving TOP-DOWN (n → 0),
    we build solution BOTTOM-UP (0 → n).
    
    We know answers for small subproblems [0, 1]
    and use them to build answers for larger subproblems [2, 3, ..., n].
    
    HOW TO BUILD:
    
    Index:    0    1    2    3
    arr:      3    2    7   10
    
    dp[0] = 3
      → Only 1 element, pick it
    
    dp[1] = max(3, 2) = 3
      → Either pick index 0 or 1 (can't pick both, they're adjacent)
      → Better to pick 3
    
    dp[2] = max(
              7 + dp[0],    ← Pick 7, can't pick index 1, use best from 0
              dp[1]         ← Don't pick 7, use best from 0-1
            )
          = max(7+3, 3) = 10
    
    dp[3] = max(
              10 + dp[1],   ← Pick 10, can't pick index 2, use best from 0-1
              dp[2]         ← Don't pick 10, use best from 0-2
            )
          = max(10+3, 10) = 13
    
    WHY IT WORKS:
    At each index i, we already know:
    - dp[i-1]: best sum without using index i
    - dp[i-2]: best sum we can combine with arr[i]
    
    So we make the choice at i based on these known values.
    No recursion needed, no recomputation needed.
    
    EXAMPLE WALKTHROUGH:
    
    Step 1: dp[0] = arr[0] = 3
    Step 2: dp[1] = max(arr[0], arr[1]) = max(3, 2) = 3
    Step 3: i=2
            pick = 7 + dp[0] = 7 + 3 = 10
            notPick = dp[1] = 3
            dp[2] = 10
    Step 4: i=3
            pick = 10 + dp[1] = 10 + 3 = 13
            notPick = dp[2] = 10
            dp[3] = 13
    
    Answer = dp[3] = 13 ✓
    
    WHEN TO USE:
    - Standard DP approach
    - Avoids recursion overhead
    - Easier to understand for most people
    - Better memory locality (iteration vs recursion)
    */
    
    int solveTabulation(vector<int>& arr) {
        int n = arr.size();
        
        if(n == 1) return arr[0];
        if(n == 2) return max(arr[0], arr[1]);
        
        // Create DP array
        vector<int> dp(n);
        
        // Base cases
        dp[0] = arr[0];              // Only index 0 available
        dp[1] = max(arr[0], arr[1]); // Pick better of first two
        
        // Fill DP table from index 2 to n-1
        for(int i = 2; i < n; i++) {
            int pick = arr[i] + dp[i - 2];   // Pick current + best from i-2
            int notPick = dp[i - 1];         // Skip current, best from i-1
            dp[i] = max(pick, notPick);
        }
        
        return dp[n - 1];  // Answer for all n elements
    }

    
    // ============================================================
    // APPROACH 4: SPACE OPTIMIZATION (Bottom-Up DP with O(1) space)
    // Time: O(N), Space: O(1) ← BEST SPACE COMPLEXITY
    // ============================================================
    /*
    HOW IT WORKS:
    
    KEY OBSERVATION:
    To compute dp[i], we ONLY need dp[i-1] and dp[i-2].
    We don't need dp[i-3], dp[i-4], etc.
    
    So we don't need entire array. Just store:
    prev2 = dp[i-2]
    prev1 = dp[i-1]
    
    COMPUTATION FLOW:
    
    i=2:
      curr = max(arr[2] + prev2, prev1)
      prev2 = prev1
      prev1 = curr
    
    i=3:
      curr = max(arr[3] + prev2, prev1)  ← Now prev2 has old prev1, prev1 has curr from i=2
      prev2 = prev1
      prev1 = curr
    
    EXAMPLE: arr = [3, 2, 7, 10]
    
    Initial:
      prev2 = 3
      prev1 = max(3, 2) = 3
    
    i=2 (arr[2]=7):
      pick = 7 + 3 = 10
      notPick = 3
      curr = 10
      prev2 = 3 (holds old prev1)
      prev1 = 10 (holds new curr)
    
    i=3 (arr[3]=10):
      pick = 10 + 3 = 13  ← prev2 is still 3 from i=2
      notPick = 10        ← prev1 is 10 from i=2
      curr = 13
      prev2 = 10
      prev1 = 13
    
    Return: 13 ✓
    
    WHY IT WORKS:
    We use the same DP recurrence: dp[i] = max(arr[i] + dp[i-2], dp[i-1])
    But instead of storing all dp values, we only keep sliding window of size 2.
    
    VISUALIZATION:
    
    Initial state (i=0,1):
    prev2 = dp[0] = 3
    prev1 = dp[1] = 3
    
    i=2:
    ┌──────────────────┐
    │ SLIDING WINDOW   │
    ├──────────────────┤
    │ prev2 = 3 (old)  │ ← indexes 0
    │ prev1 = 3 (old)  │ ← indexes 1
    │ curr  = 10 (new) │ ← indexes 2
    └──────────────────┘
    → Shift: prev2=3, prev1=10
    
    i=3:
    ┌──────────────────┐
    │ SLIDING WINDOW   │
    ├──────────────────┤
    │ prev2 = 3 (old)  │ ← indexes 1
    │ prev1 = 10 (old) │ ← indexes 2
    │ curr  = 13 (new) │ ← indexes 3
    └──────────────────┘
    → Shift: prev2=10, prev1=13
    
    WHEN TO USE:
    - Production code (best space efficiency)
    - Interview when asked "Can you optimize space?"
    - Large arrays where memory is constraint
    - When time O(N) is already optimal
    */
    
    int solveSpaceOptimized(vector<int>& arr) {
        int n = arr.size();
        
        if(n == 1) return arr[0];
        if(n == 2) return max(arr[0], arr[1]);
        
        // Only store last 2 DP values
        int prev2 = arr[0];                    // dp[i-2]
        int prev1 = max(arr[0], arr[1]);       // dp[i-1]
        
        // Iterate and compute current
        for(int i = 2; i < n; i++) {
            int pick = arr[i] + prev2;   // Current + best from 2 steps back
            int notPick = prev1;         // Best from 1 step back
            int curr = max(pick, notPick);
            
            // Shift for next iteration
            prev2 = prev1;  // Move prev1 to prev2
            prev1 = curr;   // Move curr to prev1
        }
        
        return prev1;  // Final answer stored in prev1
    }

    
    // ============================================================
    // MAIN FUNCTION (Choose approach based on context)
    // ============================================================
    
    int findMaxSum(vector<int>& arr) {
        int n = arr.size();
        
        // Choice 1: Recursion (SLOW - only for learning, n <= 20)
        // return solveRecursion(n - 1, arr);
        
        // Choice 2: Memoization (Good for interviews, n <= 1000)
        // vector<int> dp(n, -1);
        // return solveMemoization(n - 1, arr, dp);
        
        // Choice 3: Tabulation (Standard choice, n <= 10^5)
        // return solveTabulation(arr);
        
        // Choice 4: Space Optimized (BEST - use for production, n <= 10^6)
        return solveSpaceOptimized(arr);
    }
};


/*
---------------- DRY RUN (Space Optimized) ----------------

arr = [3, 2, 7, 10]
n = 4

Base:
prev2 = 3
prev1 = max(3, 2) = 3

i = 2 (arr[2] = 7):
  pick = 7 + 3 = 10
  notPick = 3
  curr = max(10, 3) = 10
  
  prev2 = 3
  prev1 = 10

i = 3 (arr[3] = 10):
  pick = 10 + 3 = 13
  notPick = 10
  curr = max(13, 10) = 13
  
  prev2 = 10
  prev1 = 13

Return: 13 ✓

--------------------------------------------------

SECOND EXAMPLE:
arr = [5, 5, 10, 100, 10, 5]
n = 6

Base:
prev2 = 5
prev1 = max(5, 5) = 5

i = 2 (10):
  curr = max(10+5, 5) = 15
  prev2=5, prev1=15

i = 3 (100):
  curr = max(100+5, 15) = 105
  prev2=15, prev1=105

i = 4 (10):
  curr = max(10+15, 105) = 105
  prev2=105, prev1=105

i = 5 (5):
  curr = max(5+105, 105) = 110
  prev2=105, prev1=110

Return: 110 ✓

Picking: indices 0(5) + 3(100) + 5(5) = 110

--------------------------------------------------

STATE TRANSITIONS:

For each index i:

If we PICK arr[i]:
  → We get arr[i]
  → Plus the best non-adjacent sum up to i-2
  → Total = arr[i] + dp[i-2]

If we DON'T PICK arr[i]:
  → We get the best sum up to i-1
  → Total = dp[i-1]

dp[i] = max(pick, notPick)

--------------------------------------------------

KEY INSIGHT:

This is called HOUSE ROBBER PATTERN because:
- You're a robber visiting houses in a line
- Each house has money (arr[i])
- You can't rob adjacent houses (constraint)
- You want maximum money

Real-world applications:
- Max profit from non-adjacent projects
- Max score from non-overlapping events
- Max value from non-consecutive stocks

--------------------------------------------------

PATTERN RECOGNITION:

If problem says:
- Cannot pick/use adjacent elements
- Maximum sum/profit/score
- Subsequence/non-overlapping
- Linear arrangement
→ Use PICK / NOT PICK DP

Standard formula:
dp[i] = max(
    arr[i] + dp[i-2],
    dp[i-1]
)

This is one of the MOST COMMON DP patterns!

--------------------------------------------------

FINAL SUMMARY:

Pattern Name: HOUSE ROBBER / PICK-NOT PICK

When to use:
- Adjacent constraint with max/min objective
- Subsequence from linear array
- Pick elements with restriction

Key principle:
At each position, decide pick or skip
Combine with previous solutions

Complexity progression:
Recursion (exponential) → Memoization → Tabulation → Space Optimization

This demonstrates the FULL STRIVER DP FLOW!

TIME: O(N)
SPACE: O(1)
*/
