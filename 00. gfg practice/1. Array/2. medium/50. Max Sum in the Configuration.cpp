/*
================================================================================
PROBLEM: Max Sum in the Configuration (GFG - Medium)
================================================================================

Given an integer array arr[]. The only operation allowed is to rotate 
(clockwise or counterclockwise) the array any number of times.

For each rotation, compute: SUM = 0*arr[0] + 1*arr[1] + 2*arr[2] + ... + (n-1)*arr[n-1]

Find the maximum possible value across all rotations.

Examples:
1. arr = [3, 1, 2, 8]
   Output: 29
   Explanation: [3, 1, 2, 8] gives (0*3) + (1*1) + (2*2) + (3*8) = 29 (maximum)

2. arr = [1, 2, 3]
   Output: 8
   Explanation: [1, 2, 3] gives (0*1) + (1*2) + (2*3) = 8 (maximum)

3. arr = [4, 13]
   Output: 13
   Explanation: [13, 4] gives (0*13) + (1*4) = 4, [4, 13] gives (0*4) + (1*13) = 13

Constraints:
- 1 ≤ arr.size() ≤ 10^4
- 1 ≤ arr[i] ≤ 20

Companies: Amazon

================================================================================
APPROACH 2: ROTATION FORMULA (OPTIMAL)
Time: O(n) | Space: O(1)
================================================================================

HOW IT WORKS:

KEY INSIGHT: Use a mathematical formula to compute next rotation sum!

Let sum = total sum of all elements
Let Rk = result after rotation k

Formula:
Rk = R(k-1) + sum - n * arr[n-k]

WHY THIS WORKS:

When we rotate the array clockwise by 1:
- Last element moves to front (index 0)
- All other elements shift right (index increases by 1)
- Indices: arr[n-1] → indices now: 0, 1, 2, ..., n-1

Change in sum:
+ Each element gets 1 more in its multiplier → +sum total
- Last element was at (n-1), now at 0 → subtract (n-1) * arr[n-1], add 0 * arr[n-1]
  Net effect: -(n-1) * arr[n-1] - 0 = -(n-1) * arr[n-1]

Actually, more precisely:
- Last element moves from (n-1) to 0 → change is -(n-1)*val + 0*val = -(n-1)*val
- But all other elements increase by 1 index → +sum
- Net: Rk = R(k-1) + sum - n*arr[n-k]

VISUAL UNDERSTANDING:

Initial: [A, B, C, D] at indices [0, 1, 2, 3]
        R0 = 0*A + 1*B + 2*C + 3*D

After 1 rotation: [D, A, B, C] at indices [0, 1, 2, 3]
                 R1 = 0*D + 1*A + 2*B + 3*C

Changes:
- A: index 0→1 (gain 1*A = +A)
- B: index 1→2 (gain 1*B = +B)
- C: index 2→3 (gain 1*C = +C)
- D: index 3→0 (loss 3*D = -3*D)

Net = +A + +B + +C - 3*D = +(A+B+C+D) - 4*D = +sum - n*D

So: R1 = R0 + sum - n*arr[n-1]

This pattern repeats for all k!

ALGORITHM:
1. Compute initial sum and R0
2. For each rotation k from 1 to n-1:
   - Rk = R(k-1) + sum - n * arr[n-k]
   - Track maximum


DRY RUN: arr = [3, 1, 2, 8]

Step 1: Precompute
sum = 3 + 1 + 2 + 8 = 14

R0 = 0*3 + 1*1 + 2*2 + 3*8
   = 0 + 1 + 4 + 24 = 29

Step 2: Compute rotations using formula
R1 = R0 + sum - n*arr[n-1]
   = 29 + 14 - 4*8
   = 29 + 14 - 32 = 11

R2 = R1 + sum - n*arr[n-2]
   = 11 + 14 - 4*2
   = 11 + 14 - 8 = 17

R3 = R2 + sum - n*arr[n-3]
   = 17 + 14 - 4*1
   = 17 + 14 - 4 = 27

Maximum = max(29, 11, 17, 27) = 29 ✓

VERIFICATION: What does rotation look like?
R0: [3, 1, 2, 8] → indices [0, 1, 2, 3] → 0*3 + 1*1 + 2*2 + 3*8 = 29 ✓
R1: [8, 3, 1, 2] → indices [0, 1, 2, 3] → 0*8 + 1*3 + 2*1 + 3*2 = 11 ✓
R2: [2, 8, 3, 1] → indices [0, 1, 2, 3] → 0*2 + 1*8 + 2*3 + 3*1 = 17 ✓
R3: [1, 2, 8, 3] → indices [0, 1, 2, 3] → 0*1 + 1*2 + 2*8 + 3*3 = 27 ✓

All match! Formula is correct.

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution2 {
  public:
    /*
    APPROACH 2: ROTATION FORMULA (OPTIMAL)
    
    WHY THIS WORKS:
    - Uses mathematical relationship between rotations
    - Each element participates in sum exactly once per rotation
    - Can compute next rotation in O(1) after preprocessing
    
    FORMULA:
    Rk = R(k-1) + sum - n * arr[n-k]
    
    Intuition:
    - sum: each element's index increases by 1
    - -n*arr[n-k]: element moving from end to front
    */
    
    long long optimalFormula(vector<int>& arr) {
        int n = arr.size();
        long long sum = 0;
        long long r0 = 0;
        
        // Step 1: Calculate total sum and initial configuration sum
        for (int i = 0; i < n; i++) {
            sum += arr[i];
            r0 += (long long)i * arr[i];
        }
        
        // Step 2: Apply rotation formula
        long long maxSum = r0;
        long long currentSum = r0;
        
        for (int k = 1; k < n; k++) {
            // Rotate: last element moves to front
            // Current element leaving the end: arr[n-k]
            currentSum = currentSum + sum - (long long)n * arr[n - k];
            maxSum = max(maxSum, currentSum);
        }
        
        return maxSum;
    }
};


/*
================================================================================
DRY RUN - DETAILED (Optimal Formula):
================================================================================

Example 1: arr = [3, 1, 2, 8]

Step 1: Precompute
sum = 3 + 1 + 2 + 8 = 14

Initial rotation (k=0):
[3, 1, 2, 8] at indices [0, 1, 2, 3]
r0 = 0*3 + 1*1 + 2*2 + 3*8
   = 0 + 1 + 4 + 24 = 29

Step 2: Apply formula
Before loop: maxSum = 29, currentSum = 29

k=1 (rotate right, arr[n-1]=8 moves to front):
After rotation: [8, 3, 1, 2]
currentSum = 29 + 14 - 4*8 = 29 + 14 - 32 = 11
maxSum = 29

k=2 (arr[n-2]=2 was the element to move):
After rotation: [2, 8, 3, 1]
currentSum = 11 + 14 - 4*2 = 11 + 14 - 8 = 17
maxSum = 29

k=3 (arr[n-3]=1 was element to move):
After rotation: [1, 2, 8, 3]
currentSum = 17 + 14 - 4*1 = 17 + 14 - 4 = 27
maxSum = 29

Final output: 29 ✓

================================================================================

Example 2: arr = [1, 2, 3]

sum = 1 + 2 + 3 = 6

r0 = 0*1 + 1*2 + 2*3 = 0 + 2 + 6 = 8

k=1:
currentSum = 8 + 6 - 3*3 = 8 + 6 - 9 = 5
maxSum = 8

k=2:
currentSum = 5 + 6 - 3*2 = 5 + 6 - 6 = 5
maxSum = 8

Final output: 8 ✓

================================================================================

Example 3: arr = [4, 13]

sum = 4 + 13 = 17

r0 = 0*4 + 1*13 = 0 + 13 = 13

k=1:
currentSum = 13 + 17 - 2*4 = 13 + 17 - 8 = 22
maxSum = 22

Wait, that doesn't match expected output of 13...
Let me reconsider. The problem says output is 13.

Let me manually check:
[4, 13] → 0*4 + 1*13 = 13
[13, 4] → 0*13 + 1*4 = 4

So max is 13, not 22.

Let me check my formula again...
Actually wait, for arr = [4, 13]:
sum = 17
r0 = 0*4 + 1*13 = 13

After 1 rotation (moving 13 to front? or 4 to front?):
If we rotate right once (last element moves to front):
arr[n-1] = 13 moves to front
New array: [13, 4]
New sum = 0*13 + 1*4 = 4

Using formula: currentSum = 13 + 17 - 2*13 = 30 - 26 = 4 ✓

So max(13, 4) = 13 ✓

The formula is correct!

================================================================================
EDGE CASES:
================================================================================

1. Single element:
   arr = [5]
   r0 = 0*5 = 0
   No rotations possible beyond R0
   Output: 0 ✓

2. Two elements:
   arr = [3, 7]
   r0 = 0*3 + 1*7 = 7
   r1 = 7 + 10 - 2*3 = 12
   Output: 12 ✓
   Verify: [7, 3] → 0*7 + 1*3 = 3... wait that's wrong
   
   Actually, let me reindex. If arr = [3, 7]:
   Original: [3, 7] → 0*3 + 1*7 = 7
   Rotated:  [7, 3] → 0*7 + 1*3 = 3
   
   Using formula for k=1:
   currentSum = 7 + 10 - 2*7 = 17 - 14 = 3 ✓
   
   So max is 7 ✓

3. All same elements:
   arr = [5, 5, 5]
   r0 = 0*5 + 1*5 + 2*5 = 0 + 5 + 10 = 15
   r1 = 15 + 15 - 3*5 = 15
   r2 = 15 + 15 - 3*5 = 15
   Output: 15 (all rotations give same result) ✓

4. Increasing array:
   arr = [1, 2, 3, 4]
   r0 = 0 + 2 + 6 + 12 = 20 ← best (largest elements at end)
   r1 = 20 + 10 - 4*4 = 6
   r2 = 6 + 10 - 4*3 = 8
   r3 = 8 + 10 - 4*2 = 14
   Output: 20 (original is best) ✓

5. Decreasing array:
   arr = [4, 3, 2, 1]
   r0 = 0 + 3 + 4 + 3 = 10
   r1 = 10 + 10 - 4*1 = 16
   r2 = 16 + 10 - 4*2 = 18
   r3 = 18 + 10 - 4*3 = 20 ← best (smallest element at end of rotation)
   Output: 20 ✓

6. Large numbers:
   arr = [20, 20, 20] (max values)
   r0 = 0 + 20 + 40 = 60
   All rotations same = 60
   Output: 60 ✓

================================================================================
TEST CASES:
================================================================================

Test 1: arr = [3, 1, 2, 8]
Expected: 29
Trace: r0=29, r1=11, r2=17, r3=27
Result: max = 29 ✓

Test 2: arr = [1, 2, 3]
Expected: 8
Trace: r0=8, r1=5, r2=5
Result: max = 8 ✓

Test 3: arr = [4, 13]
Expected: 13
Trace: r0=13, r1=4
Result: max = 13 ✓

Test 4: arr = [5, 5, 5]
Expected: 15
Trace: All rotations give 15
Result: max = 15 ✓

Test 5: arr = [1, 10, 100]
Expected: ?
r0 = 0 + 10 + 200 = 210
r1 = 210 + 111 - 3*100 = 321 - 300 = 21
r2 = 21 + 111 - 3*1 = 129
Result: max = 210 ✓

Test 6: arr = [10, 1, 2, 3, 4]
Expected: ?
sum = 20, r0 = 0 + 1 + 4 + 9 + 40 = 54
r1 = 54 + 20 - 5*4 = 54
r2 = 54 + 20 - 5*3 = 59
r3 = 59 + 20 - 5*2 = 69
r4 = 69 + 20 - 5*1 = 84
Result: max = 84 ✓

================================================================================
COMPLEXITY COMPARISON:
================================================================================

Approach 1 (Brute Force): ✗ Not efficient
✗ O(n²) time - compute sum for each of n rotations
✗ O(n) space - need to track rotated array (or indices)
✗ Only for understanding problem

Approach 2 (Rotation Formula): ✓✓ OPTIMAL
✓ O(n) time - single pass for all rotations
✓ O(1) space - only track current/max sum
✓ Production-grade solution

Performance improvement:
- n=1000: Brute = 1M operations, Formula = 1K operations (1000x faster!)
- n=10000: Brute = 100M ops, Formula = 10K ops (10,000x faster!)

Why formula is so much better:
- Brute force: n independent computations
- Formula: Chain computations, each builds on previous

This is the KEY INSIGHT amazon looks for!

================================================================================
SPACE & TIME BREAKDOWN:
================================================================================

Brute Force:
- Time: O(n) per rotation * n rotations = O(n²)
- Space: O(n) for rotated array or O(1) with index manipulation
- Hidden cost: CPU cache misses due to non-sequential access

Rotation Formula:
- Time: O(n) precompute + O(n) for n iterations = O(n)
- Space: O(1) - only few variables
- CPU efficient: Sequential memory access

Key operations:
- Brute: n * n * const ≈ n² multiplications, n² additions
- Formula: n multiplications, 2n additions total
- Ratio: n² / 3n ≈ n/3 times faster (polynomial improvement!)

================================================================================
PATTERN RECOGNITION & INTERVIEW INSIGHTS:
================================================================================

Key patterns this problem tests:
1. Rotation problems often have mathematical formulas
2. Matrix operations are rarely O(n²) in interviews
3. Look for relationships between adjacent configurations

Related problems:
1. "Minimize Heights" - also uses rotation optimization
2. "Maximum sum subarray" - uses similar DP thinking
3. "Next Greater Element" - uses similar iteration pattern

Interviewer expectations:
- Recognize O(n²) brute force immediately
- Think about relationship between rotations
- Derive the formula from first principles
- Know why formula works (not just memorize)

Red flags in coding:
- Generating actual rotated arrays (not needed!)
- Using modulo excessively (just use index arithmetic)
- Not considering integer overflow (use long long!)

Follow-up questions:
Q: What if elements can be negative?
A: Same solution works! Formula doesn't depend on positive values.

Q: What if we can only rotate clockwise?
A: Formula would be different but approach same.

Q: What if n is very large?
A: O(n) is already optimal since we need to read input.

Q: How to find which rotation gives max?
A: Track index along with maxSum.

================================================================================
INTEGER OVERFLOW PROTECTION:
================================================================================

Why use long long:
- arr[i] can be up to 20
- n can be up to 10^4
- Max element contribution: (n-1) * 20 = 199,980
- Max sum: 10^4 * 20 = 200,000
- Max R value: 200,000 * 10,000 ≈ 2*10^9

This fits in int (2^31 - 1 ≈ 2.1*10^9), but:
- Intermediate calculations might overflow
- Safe practice: use long long for accumulations
- Formula: sum * n can be large

Actually, with n=10^4 and each arr[i]=20:
- sum = 2*10^5
- n * max_element = 10^4 * 20 = 2*10^5
- worst R value ≈ 2*10^9

Should be safe but better to use long long for safety.

================================================================================
VARIATIONS:
================================================================================

1. Find which rotation gives maximum:
   Track index k along with maxSum.

2. Counterclockwise rotation instead:
   Formula becomes: Rk = R(k-1) + sum - n * arr[k-1]
   (Different element leaves the front)

3. Allow both clockwise and counterclockwise:
   Run formula in both directions, find max.

4. Minimize instead of maximize:
   Same algorithm, find min instead of max.

5. With negative weights (not i but some other weight w[i]):
   Similar formula but different weight system.

6. Circular array (already is one):
   Problem inherently handles this.

================================================================================
INTERVIEW STRATEGY:
================================================================================

Step 1: Ask clarifying questions
- "Can rotation be in place or do we need intermediate array?"
- "What if n=1?" (Edge case)
- "Can we modify the original array?"

Step 2: Explain brute force
- "We can try all n rotations, compute sum each time: O(n²)"
- "This works but inefficient"

Step 3: Identify pattern
- "Let's see relationship between consecutive rotations"
- "When we rotate, what changes?"
- "Every element's index increases by 1 except last moves to 0"

Step 4: Derive formula
- "So new_sum = old_sum + (increase from index change) - (decrease from last element)"
- "Increase = one extra for each element = sum of all"
- "Decrease = (n-1) - 0 multiplied by last element = n * last_element"

Step 5: Code it
- Write clean code with comments
- Use long long to prevent overflow
- Test with examples

Step 6: Complexity analysis
- "Time: O(n), Space: O(1)"
- "Why better than brute: Formula leverages relationships"

Step 7: Test cases
- Normal cases, edge cases (n=1), duplicate elements

Step 8: Discuss optimizations
- Already O(n) optimal
- Could parallelize but unnecessary
- Could use matrix exponentiation for even more rotations (not needed)

================================================================================
*/
