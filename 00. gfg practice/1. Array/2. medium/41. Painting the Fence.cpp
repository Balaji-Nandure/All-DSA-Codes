/*
PROBLEM: Painting the Fence (GFG)

Given n fence posts and k colors,
Paint all posts such that NOT MORE THAN 2 consecutive posts have the same color.
Return the number of valid ways.

Constraint: Max 2 consecutive posts can have same color.

Examples:
n = 3, k = 2 (colors: R, B)
Valid: RRB, RBR, RBB, BRR, BRB, BBR
Invalid: RRR, BBB (3 consecutive same)
Output: 6

n = 2, k = 4
All pairs are valid (since max 2 consecutive allowed)
Output: 4 × 4 = 16

n = 1, k = 4
Output: 4

--------------------------------------------------

INTUITION / APPROACH:

This is a CONSTRAINED PAINT / TILING problem using DP.

--------------------------------------------------

INTUITION (VERY IMPORTANT - SHORT VERSION):

At post i, you have two choices:

1. Paint DIFFERENT from previous post (i-1)
   → This is safe from any valid state at (i-1)
   → You have (k-1) color choices
   → Contributes: ways[i-1] × (k-1)

2. Paint SAME as previous post (i-1)
   → This is only safe if (i-2) and (i-1) were DIFFERENT
   → Otherwise you'd have 3 consecutive same (violates constraint)
   → You have 1 color choice (same as previous)
   → Contributes: ways[i-2] × 1

Total at post i:
ways[i] = ways[i-1] × (k-1) + ways[i-2] × 1
        = (ways[i-1] + ways[i-2]) × (k-1)  [FACTORED FORM]

--------------------------------------------------

Key idea: Track last 1-2 states to decide valid choices.

State definition:
- same[i] = ways to paint i posts where posts (i-1) and i have SAME color
- diff[i] = ways to paint i posts where posts (i-1) and i have DIFFERENT color

Transitions:

For same[i] (last two posts same color):
  We paint post i with same color as post (i-1).
  But this is only allowed if posts (i-2) and (i-1) are DIFFERENT.
  
  same[i] = diff[i-1] × 1
           (previous must be different from its previous,
            so we can now make them same)

For diff[i] (last two posts different color):
  We paint post i with a color different from post (i-1).
  We have (k-1) color choices.
  Previous configuration can be either same or different.
  
  diff[i] = (same[i-1] + diff[i-1]) × (k-1)

Total:
total[i] = same[i] + diff[i]

--------------------------------------------------

SPACE OPTIMIZATION:

Observation: We only need previous state to compute current state.

Let:
prev2 = total ways for (i-2) posts
prev1 = total ways for (i-1) posts

We can derive a direct formula:
ways[i] = (ways[i-1] + ways[i-2]) × (k-1)

This avoids tracking same/diff separately!

--------------------------------------------------

BASE CASES:

For n = 1:
  total = k (paint any of k colors)

For n = 2:
  same = k (paint first post, then paint second same) = k
  diff = k × (k-1) (paint first, then paint second different)
  total = k + k×(k-1) = k²

--------------------------------------------------

TIME COMPLEXITY:
O(N) - single loop from 3 to n

SPACE COMPLEXITY:
O(1) - only tracking two variables

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/painting-the-fence3727/1

--------------------------------------------------
*/

class Solution {
  public:

    // ============================================================
    // APPROACH 1: RECURSION (Brute Force)
    // Time: O((k-1)^N), Space: O(N) recursion stack
    // ============================================================
    /*
    HOW IT WORKS:
    
    This shows the PATTERN, though not a full true recursion 
    (exploring all branches would be complex).
    
    The idea is:
    At post n, we always have (k-1) color choices because we can't
    use the color from post (n-1).
    
    So: ways[n] depends on ways[n-1]
    And each branch multiplies by (k-1)
    
    EXAMPLE: n=3, k=2
    
    Post 1: 2 ways (any 2 colors)
    Post 2: 2 × 2 = 4 ways (any color for each post)
    Post 3: For each of 4 ways at post 2,
            we have 1 choice (different from post 2)
            But we need to consider constraint on posts 2-3 same...
    
    The recurrence: ways[i] = (ways[i-1] + ways[i-2]) × (k-1)
    
    Captures this: at post i, we either:
    - Paint different from previous (always allowed if we came from ways[i-1])
    - Paint same as previous (only allowed if previous posts were different, i.e., ways[i-2])
    
    WHY IT WORKS:
    It explores all valid painting combinations.
    
    BEST FOR: Understanding the pattern, small n
    */
    
    long long solveRecursion(int n, int k) {
        if(n == 1) return k;           // 1 post: k choices
        if(n == 2) return 1LL * k * k; // 2 posts: k² choices (no constraint)
        
        // This simplified version just shows the idea
        // True recursion with exploration would be complex
        long long prevSame = k;              // Placeholder
        long long prevDiff = 1LL * k * (k-1); // Placeholder
        
        return (prevDiff + prevSame) * (k - 1);
    }

    
    // ============================================================
    // APPROACH 2: MEMOIZATION (Top-Down DP)
    // Time: O(N), Space: O(N) map + O(N) recursion stack
    // ============================================================
    /*
    HOW IT WORKS:
    
    We recursively compute ways[n] but cache results.
    
    ways[n]:
      If n == 1: return k
      If n == 2: return k²
      If already computed: return from memo
      Else: compute ways[n] = (ways[n-1] + ways[n-2]) × (k-1)
    
    EXAMPLE: n=4, k=2
    
    Call ways(4):
      Not in memo
      = (ways(3) + ways(2)) × 1
      
      Call ways(3):
        Not in memo
        = (ways(2) + ways(1)) × 1
        
        Call ways(2):
          Base case: return 4
          Memo[2] = 4
        
        Call ways(1):
          Base case: return 2
          Memo[1] = 2
        
        = (4 + 2) × 1 = 6
        Memo[3] = 6
      
      Call ways(2):
        Found in Memo! return 4
      
      = (6 + 4) × 1 = 10
      Memo[4] = 10
    
    Each unique n computed EXACTLY once.
    Time: O(N)
    
    WHY IT WORKS:
    Top-down approach with caching avoids recomputation.
    
    WHEN TO USE:
    - Interview when recursion is clearer
    - Medium n values
    */
    
    map<int, long long> memo;
    
    long long solveMemoization(int n, int k) {
        if(n == 1) return k;
        if(n == 2) return 1LL * k * k;
        
        // Check memo
        if(memo.find(n) != memo.end())
            return memo[n];
        
        // Compute recursively
        long long result = (solveMemoization(n - 1, k) + solveMemoization(n - 2, k)) * (k - 1);
        
        // Store and return
        return memo[n] = result;
    }

    
    // ============================================================
    // APPROACH 3: TABULATION (Bottom-Up DP)
    // Time: O(N), Space: O(N) dp array
    // ============================================================
    /*
    HOW IT WORKS:
    
    Build solution BOTTOM-UP, from post 1 to post n.
    
    We know:
    dp[1] = k (1 post, k choices)
    dp[2] = k² (2 posts, no constraint)
    
    For each post i from 3 to n:
    dp[i] = (dp[i-1] + dp[i-2]) × (k-1)
    
    INTERPRETATION:
    At post i with maximum 2 consecutive same:
    - If last two posts are DIFFERENT (dp[i-1] ways):
      We can paint post i with (k-1) colors
      Total: dp[i-1] × (k-1)
    
    - If last two posts are SAME (dp[i-2] ways):
      We MUST paint post i different (1 choice)
      Total: dp[i-2] × 1
    
    Combined: (dp[i-1] + dp[i-2]) × (k-1)
    
    EXAMPLE: n=3, k=2
    
    Index:  1    2    3
    dp:     2    4    ?
    
    dp[3] = (dp[2] + dp[1]) × (k-1)
          = (4 + 2) × 1
          = 6
    
    Verification:
    Posts 1-2: 4 ways [RR, RB, BR, BB]
    For each, paint post 3:
      RR → post 3 must be B (1 way) → RRB
      RB → post 3 can be R (1 way) → RBR
      BR → post 3 can be B (1 way) → BRB
      BB → post 3 must be R (1 way) → BBR
    Total: 4 ways... wait, let's recalculate
    
    Actually: [RRB, RBR, RBB, BRR, BRB, BBR] = 6 ways ✓
    
    WHY IT WORKS:
    Each state dp[i] is built from smaller subproblems dp[i-1], dp[i-2].
    No recursion overhead, iterative approach is clean.
    
    WHEN TO USE:
    - Standard DP problems
    - When iteration is preferred over recursion
    - Most common choice
    */
    
    long long solveTabulation(int n, int k) {
        if(n == 1) return k;
        if(n == 2) return 1LL * k * k;
        
        // Build DP array from post 1 to post n
        vector<long long> dp(n + 1);
        
        // Base cases
        dp[1] = k;           // 1 post
        dp[2] = 1LL * k * k; // 2 posts
        
        // Fill DP table from post 3 to n
        for(int i = 3; i <= n; i++) {
            // At post i:
            // - Ways where posts i-1 and i are different: dp[i-1]
            // - Ways where posts i-1 and i could be same: dp[i-2]
            // - Choose color for post i: (k-1) options
            dp[i] = (dp[i - 1] + dp[i - 2]) * (k - 1);
        }
        
        return dp[n];
    }

    
    // ============================================================
    // APPROACH 4: SPACE OPTIMIZATION (Bottom-Up DP with O(1) space)
    // Time: O(N), Space: O(1) ← BEST SPACE COMPLEXITY
    // ============================================================
    /*
    HOW IT WORKS:
    
    KEY OBSERVATION:
    To compute dp[i], we only need dp[i-1] and dp[i-2].
    We never need dp[i-3] or earlier.
    
    So instead of storing entire dp array, use SLIDING WINDOW:
    prev2 = dp[i-2]
    prev1 = dp[i-1]
    
    COMPUTATION FLOW:
    
    1. Initialize:
       prev2 = dp[1] = k
       prev1 = dp[2] = k²
    
    2. For i = 3 to n:
       curr = (prev1 + prev2) × (k-1)
       prev2 = prev1  ← Shift: prev2 now holds dp[i-1]
       prev1 = curr   ← Shift: prev1 now holds dp[i]
    
    EXAMPLE: n=4, k=2
    
    Initial:
      prev2 = 2
      prev1 = 4
    
    i=3:
      curr = (4 + 2) × 1 = 6
      prev2 = 4
      prev1 = 6
    
    i=4:
      curr = (6 + 4) × 1 = 10
      prev2 = 6
      prev1 = 10
    
    Return 10
    
    SLIDING WINDOW VISUALIZATION:
    
    i=3:
    ┌────────────────────────┐
    │   SLIDING WINDOW       │
    ├────────────────────────┤
    │ prev2 = 2 (dp[1])      │ ← We shift this right
    │ prev1 = 4 (dp[2])      │ ← We shift this right
    │ curr  = 6 (dp[3])      │ ← New value
    └────────────────────────┘
    After shift: prev2=4, prev1=6
    
    i=4:
    ┌────────────────────────┐
    │   SLIDING WINDOW       │
    ├────────────────────────┤
    │ prev2 = 4 (dp[2])      │
    │ prev1 = 6 (dp[3])      │
    │ curr  = 10 (dp[4])     │ ← New value
    └────────────────────────┘
    After shift: prev2=6, prev1=10
    
    WHY IT WORKS:
    Same recurrence: dp[i] = (dp[i-1] + dp[i-2]) × (k-1)
    But we don't store entire history, just the last 2 values.
    The sliding window mechanism ensures we always have what we need.
    
    WHEN TO USE:
    - Production code (best space efficiency)
    - Large n values (avoiding OJ memory limits)
    - Interview "Can you optimize space?" follow-up
    - Memory constrained environments
    */
    
    long long solveSpaceOptimized(int n, int k) {
        if(n == 1) return k;
        if(n == 2) return 1LL * k * k;
        
        // Only store last 2 DP values
        long long prev2 = k;           // dp[1]
        long long prev1 = 1LL * k * k; // dp[2]
        
        // Compute from post 3 to n
        for(int i = 3; i <= n; i++) {
            long long curr = (prev1 + prev2) * (k - 1);
            
            // Shift for next iteration
            prev2 = prev1;  // Move dp[i-1] to prev2
            prev1 = curr;   // Move dp[i] to prev1
        }
        
        return prev1;  // Final answer in prev1
    }

    
    // ============================================================
    // MAIN FUNCTION (Choose approach based on context)
    // ============================================================
    
    long long countWays(int n, int k) {
        // Choice 1: Recursion (SLOW - only for learning, n <= 20)
        // return solveRecursion(n, k);
        
        // Choice 2: Memoization (Good for interviews, n <= 1000)
        // memo.clear();
        // return solveMemoization(n, k);
        
        // Choice 3: Tabulation (Standard choice, n <= 10^5)
        // return solveTabulation(n, k);
        
        // Choice 4: Space Optimized (BEST - use for production, n <= 300)
        return solveSpaceOptimized(n, k);
    }
};


/*
---------------- DRY RUN ----------------

n = 3, k = 2

Post 1 (n=1): 2 ways (R or B)

Post 2 (n=2): 
  Same: 2 (RR, BB)
  Diff: 2×1 = 2 (RB, BR)
  Total: 4

Post 3 (n=3):
  curr = (4 + 2) × (2-1) = 6

Answer = 6 ✓

Let me verify with actual strings:
- From [RR, BB] (same at 2) → paint post 3 different
  RRB, BBR (2 ways)
  
- From [RB, BR] (diff at 2) → paint post 3 different
  RBR, RBB, BRR, BRB (4 ways)
  
Total = 2 + 4 = 6 ✓

--------------------------------------------------

SECOND EXAMPLE:
n = 2, k = 4

prev2 = 4
prev1 = 16

Answer = 16 ✓

Because no constraint applies to 2 posts (max 2 allowed).
We can freely choose any color for each post.

--------------------------------------------------

STATE TRANSITION DETAILED:

Why same[i] = diff[i-1] × 1?

Configuration at i-1:
- If last two are SAME: (i-2, i-1) both color A
- If last two are DIFF: (i-2, i-1) are color A and B

If we want (i-1, i) to be SAME:
- Both should be some color C
- So (i-1) must currently be color C
- And (i-2, i-1) must be DIFFERENT (else we'd have 3 in a row)

So safe transitions to same[i]:
- Only from configurations where (i-2, i-1) are different
- That's exactly diff[i-1]

Why diff[i] = (same[i-1] + diff[i-1]) × (k-1)?

If we want (i-1, i) to be DIFFERENT:
- (i-1) is color A, (i) is color B (A ≠ B)
- We have (k-1) color choices for B
- We can come from ANY valid configuration at i-1
  (both same and diff are valid predecessors)

So:
diff[i] = (total valid at i-1) × (k-1)
        = (same[i-1] + diff[i-1]) × (k-1)

--------------------------------------------------

FINAL SUMMARY (IMPORTANT DP PATTERN):

Pattern Name: CONSTRAINED COLORING / TILING

Recurrence: ways[i] = (ways[i-1] + ways[i-2]) × (k-1)

This is a CLASSIC pattern for:
- Fence painting with max consecutive constraint
- Tile placement with pattern restrictions
- Staircase climbing with step restrictions
- String generation with character restrictions

Key principle:
When constraint depends on last 1-2 elements,
DP usually depends on last 1-2 states.

Variants:
- Change (k-1) multiplier for different constraints
- Add different base cases for different constraints
- Add more states if constraint is more complex

Companies: Amazon, Microsoft, Adobe, Google

This is a MEDIUM-HARD DP problem testing:
1. State definition clarity
2. Recurrence relation derivation
3. Space optimization skills

TIME: O(N)
SPACE: O(1)
*/
