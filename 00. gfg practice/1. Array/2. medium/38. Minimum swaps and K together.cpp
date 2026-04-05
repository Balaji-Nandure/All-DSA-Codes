/*
PROBLEM: Minimum Swaps and K Together (GFG)

Given an array arr[] and a number k,
find the minimum number of swaps required to bring all elements <= k together
(i.e., make them a contiguous subarray).

Examples:
arr = [2, 1, 5, 6, 3], k = 3
Output: 1
Explanation: Elements ≤ 3 are [2,1,3]. Swap 5 with 3 → [2,1,3,6,5]

arr = [2, 7, 9, 5, 8, 7, 4], k = 6
Output: 2
Explanation: Elements ≤ 6 are [2,5,4]. Need 2 swaps to group them.

arr = [2, 4, 5, 3, 6, 1, 8], k = 6
Output: 0
Explanation: Elements ≤ 6 are [2,4,3,6,1]. Already contiguous (indices 0-4).

--------------------------------------------------

INTUITION / APPROACH:

This is a SLIDING WINDOW problem.

Key Idea:
We don't need to actually perform swaps.
We just find the window that minimizes the number of "bad elements" inside.

Definitions:
- Good elements = elements ≤ k
- Bad elements = elements > k

Strategy:
1. Count total good elements → this is our target window size
2. Slide a window of this size across the array
3. For each window, count bad elements inside
4. Minimum bad elements = minimum swaps needed

Why it works:
- All good elements must end up together
- Any bad element inside the final window must be swapped out
- So we want to find the window with fewest bad elements

--------------------------------------------------

ALGORITHM:

Step 1: Count total good elements (≤k) → windowSize
Step 2: Count bad elements in first window of size windowSize
Step 3: Slide the window, updating bad count as we go
Step 4: Track minimum bad elements seen

--------------------------------------------------

TIME COMPLEXITY:
O(N) - two passes through array

SPACE COMPLEXITY:
O(1) - only counters used

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/minimum-swaps-and-k-together/1

--------------------------------------------------
*/

class Solution {
  public:
  
    int minSwap(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        // Step 1: Count good elements (≤ k)
        int goodCount = 0;
        for(int i = 0; i < n; i++) {
            if(arr[i] <= k)
                goodCount++;
        }
        
        // Step 2: Count bad elements in first window
        int badCount = 0;
        for(int i = 0; i < goodCount; i++) {
            if(arr[i] > k)
                badCount++;
        }
        
        int minBad = badCount;
        
        // Step 3: Slide window of size goodCount
        for(int i = goodCount; i < n; i++) {
            
            // Remove leftmost element from previous window
            if(arr[i - goodCount] > k)
                badCount--;
            
            // Add new rightmost element
            if(arr[i] > k)
                badCount++;
            
            // Update answer
            minBad = min(minBad, badCount);
        }
        
        return minBad;
    }
};


/*
---------------- DRY RUN ----------------

arr = [2, 1, 5, 6, 3], k = 3

Step 1: Count good elements
2≤3? YES, 1≤3? YES, 5≤3? NO, 6≤3? NO, 3≤3? YES
goodCount = 3

Step 2: First window [2, 1, 5]
2>3? NO, 1>3? NO, 5>3? YES
badCount = 1, minBad = 1

Step 3: Sliding window

i=3: Window [1, 5, 6]
  Remove arr[0]=2: 2>3? NO → badCount stays 1
  Add arr[3]=6: 6>3? YES → badCount = 2
  minBad = min(1, 2) = 1

i=4: Window [5, 6, 3]
  Remove arr[1]=1: 1>3? NO → badCount stays 2
  Add arr[4]=3: 3>3? NO → badCount stays 2
  minBad = min(1, 2) = 1

Answer = 1 ✓

--------------------------------------------------

SECOND EXAMPLE:
arr = [2, 7, 9, 5, 8, 7, 4], k = 6

Step 1: Count good elements
2≤6? YES, 7≤6? NO, 9≤6? NO, 5≤6? YES, 8≤6? NO, 7≤6? NO, 4≤6? YES
goodCount = 3

Step 2: First window [2, 7, 9]
2>6? NO, 7>6? YES, 9>6? YES
badCount = 2, minBad = 2

Step 3: Sliding

i=3: Window [7, 9, 5]
  Remove arr[0]=2: 2>6? NO
  Add arr[3]=5: 5>6? NO → badCount = 2
  minBad = 2

i=4: Window [9, 5, 8]
  Remove arr[1]=7: 7>6? YES → badCount = 1
  Add arr[4]=8: 8>6? YES → badCount = 2
  minBad = 2

i=5: Window [5, 8, 7]
  Remove arr[2]=9: 9>6? YES → badCount = 1
  Add arr[5]=7: 7>6? YES → badCount = 2
  minBad = 2

i=6: Window [8, 7, 4]
  Remove arr[3]=5: 5>6? NO → badCount = 2
  Add arr[6]=4: 4>6? NO → badCount = 2
  minBad = 2

Answer = 2 ✓

--------------------------------------------------

THIRD EXAMPLE (Already grouped):
arr = [2, 4, 5, 3, 6, 1, 8], k = 6

Step 1: Count good elements
2, 4, 5, 3, 6, 1 all ≤ 6, 8 > 6
goodCount = 6

Step 2: First window [2, 4, 5, 3, 6, 1]
All ≤ 6? YES (no badCount)
badCount = 0, minBad = 0

Answer = 0 ✓ (Already contiguous!)

--------------------------------------------------

FINAL SUMMARY:

Pattern Name: SLIDING WINDOW FOR GROUPING

When to use:
- Need to group certain elements together
- Minimize swaps/operations
- Elements have specific constraint (≤k, even/odd, etc.)
→ Use sliding window!

Key insight:
- Window size = count of elements satisfying constraint
- Answer = minimize "wrong elements" in window
- This is a very common optimization technique

Variants:
- Minimum operations to group any type of elements
- Can adapt to different constraints

Companies: Amazon, Microsoft, Google

TIME: O(N)
SPACE: O(1)
*/
