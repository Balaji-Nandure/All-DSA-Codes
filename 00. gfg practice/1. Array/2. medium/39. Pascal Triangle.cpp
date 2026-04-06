/*
PROBLEM: Pascal Triangle — Nth Row (GFG)

Given a positive integer n, return the nth row of Pascal's Triangle.

Pascal Triangle structure:
Row 1: 1
Row 2: 1 1
Row 3: 1 2 1
Row 4: 1 3 3 1
Row 5: 1 4 6 4 1

Each element = sum of two elements above it from previous row.

Examples:
n = 4 → Output: [1, 3, 3, 1]
n = 5 → Output: [1, 4, 6, 4, 1]
n = 1 → Output: [1]

--------------------------------------------------

INTUITION / APPROACH:

Key Insight: Pascal Triangle rows are BINOMIAL COEFFICIENTS

The nth row contains: (n-1)C0, (n-1)C1, (n-1)C2, ... (n-1)C(n-1)

where nCr = n! / (r! * (n-r)!)

Naive approach: Calculate each nCr using factorial → O(n) per element = O(n²)
Optimized approach: Use recurrence formula

--------------------------------------------------

FORMULA DERIVATION:

We want: nCr = nC(r-1) × (n-r+1) / r

Starting from definition:
  nCr = n! / (r! × (n-r)!)
  nC(r-1) = n! / ((r-1)! × (n-r+1)!)

Divide nCr by nC(r-1):
  nCr / nC(r-1) = [n! / (r! × (n-r)!)] / [n! / ((r-1)! × (n-r+1)!)]
                = [(r-1)! × (n-r+1)!] / [r! × (n-r)!]

Expand factorials:
  r! = r × (r-1)!
  (n-r+1)! = (n-r+1) × (n-r)!

Substitute:
  = [(r-1)! × (n-r+1) × (n-r)!] / [r × (r-1)! × (n-r)!]

Cancel common terms (r-1)! and (n-r)!:
  = (n-r+1) / r

Therefore:
  nCr = nC(r-1) × (n-r+1) / r  ✓

This formula allows us to compute each element from the previous one
without computing factorials!

--------------------------------------------------

ALGORITHM:

Step 1: Start with value = 1 (which is nC0)
Step 2: For each position r from 1 to n-1:
        value = value * (n - r) / r
        This gives us nCr
Step 3: Add each computed value to result

--------------------------------------------------

TIME COMPLEXITY:
O(N) - single loop to compute all elements

SPACE COMPLEXITY:
O(1) - excluding output array

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/pascal-triangle0652/1

LeetCode:
https://leetcode.com/problems/pascals-triangle-ii/

--------------------------------------------------
*/

class Solution {
  public:
  
    vector<int> nthRowOfPascalTriangle(int n) {
        
        vector<int> ans;
        
        long long value = 1;
        ans.push_back(1);  // First element is always 1
        
        int row = n - 1;   // Convert to 0-indexed
        
        // Compute remaining elements using nCr formula
        for(int col = 1; col < n; col++) {
            
            // value = value * (row - col + 1) / col
            value = value * (row - col + 1) / col;
            ans.push_back(value);
        }
        
        return ans;
    }
};


/*
---------------- DRY RUN ----------------

n = 5 → row = 4 → Elements: 4C0, 4C1, 4C2, 4C3, 4C4

Step 1: ans = [1] (4C0 = 1)

col = 1: value = 1 * (4 - 1 + 1) / 1 = 1 * 4 / 1 = 4
  → 4C1 = 4, ans = [1, 4]

col = 2: value = 4 * (4 - 2 + 1) / 2 = 4 * 3 / 2 = 6
  → 4C2 = 6, ans = [1, 4, 6]

col = 3: value = 6 * (4 - 3 + 1) / 3 = 6 * 2 / 3 = 4
  → 4C3 = 4, ans = [1, 4, 6, 4]

col = 4: value = 4 * (4 - 4 + 1) / 4 = 4 * 1 / 4 = 1
  → 4C4 = 1, ans = [1, 4, 6, 4, 1]

Answer = [1, 4, 6, 4, 1] ✓

--------------------------------------------------

SECOND EXAMPLE:
n = 4 → row = 3 → Elements: 3C0, 3C1, 3C2, 3C3

Step 1: ans = [1]

col = 1: value = 1 * 3 / 1 = 3
  → 3C1 = 3, ans = [1, 3]

col = 2: value = 3 * 2 / 2 = 3
  → 3C2 = 3, ans = [1, 3, 3]

col = 3: value = 3 * 1 / 3 = 1
  → 3C3 = 1, ans = [1, 3, 3, 1]

Answer = [1, 3, 3, 1] ✓

--------------------------------------------------

KEY MATH INSIGHT:

Pascal Triangle element at position (row, col):
= (row)! / (col! * (row-col)!)
= row choose col
= rowCcol

Formula to compute all elements in row:
rowC0 = 1
rowCcol = rowC(col-1) * (row - col + 1) / col

This avoids computing factorials and works in O(n) time!

--------------------------------------------------

IMPORTANT PATTERNS:

Pascal Triangle Problems:

Type 1: Entire Triangle → 2D DP (O(n²) time, O(n²) space)
  For each row, compute using previous row

Type 2: Nth Row Only (This problem) → nCr formula (O(n) time, O(1) space)
  Use binomial coefficient recurrence

Type 3: Single Element at (row, col) → Direct nCr (O(n) time)
  Compute using factorial or nCr formula

Companies: Amazon, Microsoft, Adobe, Apple

This nCr formula is a STANDARD INTERVIEW TECHNIQUE for math/combinatorics!

TIME: O(N)
SPACE: O(1) excluding output
*/
