/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Rearrange an array with O(1) extra space (GFG)

Given array arr[] of size n where 0 ≤ arr[i] < n
Transform array so that:
    arr[i] = arr[arr[i]]

Must do it IN-PLACE with O(1) extra space.

Examples:

Input: arr[] = [1,0]
Output: [0, 1]
Explanation: arr[arr[0]] = arr[1] = 0, arr[arr[1]] = arr[0] = 1
So, arrT becomes [0, 1]

Input: arr[] = [4,0,2,1,3]
Output: [3, 4, 2, 0, 1]
Explanation: arr[arr[0]] = arr[4] = 3, arr[arr[1]] = arr[0] = 4, 
arr[arr[2]] = arr[2] = 2, arr[arr[3]] = arr[1] = 0, 
arr[arr[4]] = arr[3] = 1
So, arrT becomes [3, 4, 2, 0, 1]

Constraints:
1 ≤ n ≤ 10^5
0 ≤ arr[i] < n

================================================================================
*/


// ============================================================
// APPROACH: MODULO ENCODING TRICK
// Time: O(N), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
The key insight is that we need to store TWO values at each index:
1. The original/old value (needed for Step 1 computation)
2. The new value (final answer after transformation)

We do this using MODULO ENCODING:
arr[i] = oldValue + newValue * n

This works because all values are < n, so multiplying by n shifts
the new value to a higher place value.

Step 1: Encode both values
    For each index i:
    arr[i] = arr[i] + (arr[arr[i]] % n) * n
    
    This stores:
    - oldValue = arr[i] (will be lost, but we compute new value first)
    - newValue = arr[arr[i]] (using old arr[i] to index)

Step 2: Extract new values
    For each index i:
    arr[i] = arr[i] / n
    
    This extracts the new value that was stored


WHY THIS WORKS:
- All original values are < n
- When we compute arr[i] % n, we get the old value
- When we compute arr[i] / n, we get the new value (stored in higher place)
- We process all indices in order, and by the time we need arr[j],
  we've already computed and stored its new value in encoded form

Example with n=5:
old = 2, new = 3
Store: arr[i] = 2 + 3*5 = 17
Later:
  old = 17 % 5 = 2
  new = 17 / 5 = 3


DRY RUN:

arr = [4,0,2,1,3]
n = 5

We want: arr[i] = arr[arr[i]]

STEP 1: Encode both values
─────────────────────────────

i=0:
    arr[arr[0]] = arr[4] = 3 (new value)
    arr[0] = 4 + (3)*5 = 4 + 15 = 19

i=1:
    arr[arr[1]] = arr[0] = 4 (but wait, arr[0] was changed!)
    Actually, we use arr[0] % 5 = 19 % 5 = 4 ✓
    arr[1] = 0 + (4)*5 = 0 + 20 = 20

i=2:
    arr[arr[2]] = arr[2] = 2
    arr[2] = 2 + (2 % 5)*5 = 2 + 2*5 = 2 + 10 = 12

i=3:
    arr[arr[3]] = arr[1] = 0
    arr[1] % 5 = 20 % 5 = 0 ✓
    arr[3] = 1 + (0)*5 = 1 + 0 = 1

i=4:
    arr[arr[4]] = arr[3] = 1
    arr[3] % 5 = 1 % 5 = 1 ✓
    arr[4] = 3 + (1)*5 = 3 + 5 = 8

After Step 1: arr = [19, 20, 12, 1, 8]

STEP 2: Extract new values (divide by n)
─────────────────────────────────────────

arr[0] = 19 / 5 = 3 ✓
arr[1] = 20 / 5 = 4 ✓
arr[2] = 12 / 5 = 2 ✓
arr[3] = 1 / 5 = 0 ✓
arr[4] = 8 / 5 = 1 ✓

Final: [3, 4, 2, 0, 1] ✓

Result: ✓ Matches expected output
*/

class Solution {
  public:
  
    void arrange(vector<int>& arr) {
        
        int n = arr.size();
        
        // Step 1: Store both old and new value in encoded form
        // arr[i] = oldValue + newValue * n
        for(int i = 0; i < n; i++) {
            arr[i] = arr[i] + (arr[arr[i]] % n) * n;
        }
        
        // Step 2: Extract new value by dividing by n
        for(int i = 0; i < n; i++) {
            arr[i] = arr[i] / n;
        }
    }
};


/*
================================================================================
KEY INSIGHTS & PATTERN RECOGNITION
================================================================================

PATTERN:
If a problem says:
- O(1) space constraint
- Transform: arr[i] = arr[arr[i]]
- Values guaranteed to be 0 to n-1

→ Use MODULO ENCODING trick

This is a CLASSIC Amazon interview trick problem!

WHY MODULO ENCODING WORKS:
- Since all values are < n, we have place value separation
- Lower place: oldValue = encoded % n
- Higher place: newValue = encoded / n
- This allows storing 2 pieces of info in 1 number

SIMILAR PROBLEMS:
- First Missing Positive (needs modulo marking too)
- Any problem requiring O(1) rearrangement with values 0 to n-1

================================================================================
*/
