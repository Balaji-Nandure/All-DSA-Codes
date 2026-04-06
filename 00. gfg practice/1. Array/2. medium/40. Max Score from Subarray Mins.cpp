/*
PROBLEM: Max Score from Subarray Mins (GFG)

For every subarray of size >= 2, find:
score = smallest element + second smallest element

Return the maximum score among all subarrays.

Examples:
arr = [4, 3, 5, 1]

All subarrays:
[4,3] → 3+4 = 7
[4,3,5] → 3+4 = 7
[4,3,5,1] → 1+3 = 4
[3,5] → 3+5 = 8  ← maximum
[3,5,1] → 1+3 = 4
[5,1] → 1+5 = 6

Answer = 8

arr = [1, 2, 3]
[1,2] → 1+2 = 3
[1,2,3] → 1+2 = 3
[2,3] → 2+3 = 5  ← maximum

Answer = 5

--------------------------------------------------

INTUITION / APPROACH (CRITICAL INSIGHT):

Key Observation:
The answer will ALWAYS come from a subarray of size 2 (adjacent pair).

Why?
When we extend a subarray, the smallest and second smallest will:
- Either stay the same
- Or become smaller (or equal)
→ Either case, sum ≤ previous sum

Example: [3, 5, 1]
- Smallest = 1, Second smallest = 3 → sum = 4
- Compare with adjacent pair [3, 5] → sum = 8
- The pair sum is better!

Formal proof idea:
If a subarray has:
  smallest_element = a
  second_smallest = b
  sum = a + b

There must exist at least two adjacent elements in that range
that are ≥ a and ≥ b respectively.
Their sum will be ≥ a + b.

Therefore, we need only check adjacent pairs!

--------------------------------------------------

ALGORITHM:

Brute Force (without optimization):
O(N²) - for each subarray, find min and 2nd min

Optimized:
1. For each adjacent pair (arr[i], arr[i+1])
2. The sum arr[i] + arr[i+1] is a candidate answer
3. Return maximum sum

Time: O(N), Space: O(1)

--------------------------------------------------

TIME COMPLEXITY:
O(N) - single pass through array

SPACE COMPLEXITY:
O(1) - only tracking max sum

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/max-sum-in-sub-arrays0824/1

--------------------------------------------------
*/

class Solution {
  public:
  
    int maxSum(vector<int> &arr) {
        
        int n = arr.size();
        int maxScore = 0;
        
        // Check all adjacent pairs
        for(int i = 0; i < n - 1; i++) {
            maxScore = max(maxScore, arr[i] + arr[i + 1]);
        }
        
        return maxScore;
    }
};


/*
---------------- DRY RUN ----------------

arr = [4, 3, 5, 1]

Adjacent pairs:
i=0: 4 + 3 = 7 → maxScore = 7
i=1: 3 + 5 = 8 → maxScore = 8
i=2: 5 + 1 = 6 → maxScore = 8 (no update)

Answer = 8 ✓

--------------------------------------------------

SECOND EXAMPLE:
arr = [1, 2, 3]

Adjacent pairs:
i=0: 1 + 2 = 3 → maxScore = 3
i=1: 2 + 3 = 5 → maxScore = 5

Answer = 5 ✓

--------------------------------------------------

WHY ADJACENT PAIRS WORK:

Consider any subarray S = [a, b, c, d, ...] with size > 2
Suppose min = x and second_min = y

For this subarray:
- x and y must exist in S
- They might not be adjacent in S

But since they're elements of S, there must be at least
two consecutive elements in S that are ≥ x and ≥ y.

Let's call those consecutive elements p and q.
Then: p + q ≥ x + y

Therefore, checking only adjacent pairs guarantees we find
the maximum possible sum.

KEY INSIGHT: The two smallest elements in a subarray
can always be replaced by an adjacent pair with sum ≥ original sum.

--------------------------------------------------

INTERVIEW TIP:

This is a TRICK PROBLEM commonly asked in:
- Amazon, Microsoft, Google
- Companies testing optimization skills

Normal approach: O(N²) or O(N² log N)
Optimized approach: O(N)

Interviewers often look for candidates who recognize the pattern
and avoid unnecessary computation.

Recognition pattern:
"Min + SecondMin across subarrays" → Check adjacent pairs only!

--------------------------------------------------

FINAL SUMMARY:

Pattern Name: OPTIMIZATION BY OBSERVATION

When to use:
- Problem seems to require checking all subarrays
- But there's a mathematical property that limits valid answers
→ Observe and exploit the pattern!

Key Idea:
The answer always appears at boundaries or smallest scopes
(e.g., size 2 here, single element in other problems)

Common variants:
- Max product from subarrays → Often found in size 2 or 3
- Min sum in subarrays → Check boundaries first
- Optimal grouping → Often found in adjacent pairs

This requires DEEP THINKING and is highly valued in interviews!

TIME: O(N)
SPACE: O(1)
*/
