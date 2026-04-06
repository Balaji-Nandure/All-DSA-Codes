/*
================================================================================
PROBLEM: Minimize the Heights I (GFG - Medium)
================================================================================

Given array arr[] and integer k.
Each element can be increased OR decreased by k exactly once.
Find minimum possible difference between max and min heights after modification.

Example:
arr = [1, 5, 8, 10], k = 2
Answer = 5
Explanation: Modified → [3, 3, 6, 8], diff = 8-3 = 5

Constraints:
- 1 ≤ k ≤ 10^4
- 1 ≤ arr.size() ≤ 10^5
- 0 ≤ arr[i] ≤ 10^5

================================================================================
INTUITION: BREAKING POINT STRATEGY
================================================================================

Key Idea:
After sorting, divide array into TWO parts:
- Left side (0...i): increase by k
- Right side (i+1...n-1): decrease by k

Why?
Small elements should increase → push them up
Large elements should decrease → pull them down
This minimizes max-min difference

For each partition:
- New minimum: min(arr[0]+k, arr[i+1]-k)
- New maximum: max(arr[i]+k, arr[n-1]-k)
- Calculate diff = max - min

Try ALL breaking points, return minimum!

================================================================================
APPROACH: GREEDY WITH SORTING
Time: O(N log N) | Space: O(1)
================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


// ============================================================
// SOLUTION: Greedy with Sorting
// ============================================================

class Solution {
  public:
  
    /*
    HOW IT WORKS:
    1. Sort array
    2. Try each breaking point i (0 to n-2)
       - Elements [0...i]: increase by k
       - Elements [i+1...n-1]: decrease by k
    3. For each partition calculate:
       minHeight = min(arr[0]+k, arr[i+1]-k)
       maxHeight = max(arr[i]+k, arr[n-1]-k)
    4. Return minimum difference found
    
    WHY IT WORKS:
    - After sorting, optimal solution always has a breaking point
    - Left (small) elements increase, right (large) elements decrease
    - Trying all breaking points explores entire solution space
    
    TIME: O(N log N) - sorting + O(N) iteration
    SPACE: O(1)
    */
    
    int getMinDiff(vector<int> &arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        
        int ans = arr[n-1] - arr[0]; // Initial difference (no modification)
        
        // Try each breaking point
        for(int i = 0; i < n-1; i++) {
            // Left [0...i] increase by k, Right [i+1...n-1] decrease by k
            
            int minHeight = min(arr[0] + k, arr[i+1] - k);
            int maxHeight = max(arr[i] + k, arr[n-1] - k);
            
            ans = min(ans, maxHeight - minHeight);
        }
        
        return ans;
    }
};


/*
================================================================================
DRY RUN: arr = [1, 5, 8, 10], k = 2
================================================================================

Sorted: [1, 5, 8, 10]
Initial diff = 10 - 1 = 9

Breaking point i=0:
Left [0...0]: 1+2=3
Right [1...3]: 5-2=3, 8-2=6, 10-2=8
minHeight = min(1+2, 5-2) = min(3, 3) = 3
maxHeight = max(1+2, 10-2) = max(3, 8) = 8
diff = 8 - 3 = 5

Breaking point i=1:
Left [0...1]: 1+2=3, 5+2=7
Right [2...3]: 8-2=6, 10-2=8
minHeight = min(1+2, 8-2) = min(3, 6) = 3
maxHeight = max(5+2, 10-2) = max(7, 8) = 8
diff = 8 - 3 = 5

Breaking point i=2:
Left [0...2]: 1+2=3, 5+2=7, 8+2=10
Right [3...3]: 10-2=8
minHeight = min(1+2, 10-2) = min(3, 8) = 3
maxHeight = max(8+2, 10-2) = max(10, 8) = 10
diff = 10 - 3 = 7

Answer = min(9, 5, 5, 7) = 5 ✓

================================================================================
EDGE CASES:
================================================================================

1. Single element: arr = [5], k = 2
   No iteration, ans = 5 - 5 = 0 ✓
   (Single element has no difference)

2. All same: arr = [5, 5, 5], k = 2
   Can become [3, 3, 3] or [7, 7, 7]
   ans = 0 ✓

3. Large k: arr = [1, 100], k = 50
   1-50=-49, fully negative possible
   Still works!

================================================================================
PATTERN RECOGNITION:
================================================================================

This is a CLASSIC pattern in DSA:
- Problem asks to increase/decrease by fixed amount
- Find min difference or min max or similar
→ Use SORTING + BREAKING POINT technique

Very important for interviews!

================================================================================
TEST CASES:
================================================================================

Test 1: arr = [1, 5, 8, 10], k = 2
Expected: 5
Result: ✓

Test 2: arr = [3, 9, 12, 16, 20], k = 3
After sort: [3, 9, 12, 16, 20]
i=0: min=min(6,6)=6, max=max(6,17)=17, diff=11
i=1: min=min(6,9)=6, max=max(12,17)=17, diff=11
i=2: min=min(6,13)=6, max=max(15,17)=17, diff=11
i=3: min=min(6,17)=6, max=max(19,17)=19, diff=13
Result: 11 ✓

Test 3: arr = [5], k = 2
Result: 0 ✓

================================================================================
INTERVIEW QUESTIONS:
================================================================================

Q: Why sorting helps?
A: Reduces search space from 2^N to O(N) by recognizing optimal solution
   has a clear breaking point in sorted order.

Q: Why do we check: min(arr[0]+k, arr[i+1]-k)?
A: After partition, leftmost could be arr[0]+k, and rightmost of left part
   converted to right becomes arr[i+1]-k. The minimum is the smaller one.

Q: Can heights go negative?
A: YES! arr[i]-k can be negative. Solution still works.

Q: Why is this greedy?
A: We greedily assume small elements should increase and large should decrease.
   We try all breaking points to find optimal partition.

================================================================================
*/
