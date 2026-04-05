/*
PROBLEM: Maximum Subarray (Non-Negative Only) — GFG

Find the contiguous subarray with the maximum sum that contains only NON-NEGATIVE numbers.
If multiple subarrays have same sum:
    1. Choose the one with longest length
    2. If still tie → choose the one with smallest starting index
If all numbers are negative → return {-1}

Example:
Input: [1, 2, 5, -7, 2, 6]
Output: [1, 2, 5]

--------------------------------------------------

INTUITION / APPROACH:

This is NOT Kadane exactly.
This is a SEGMENT / WINDOW SCAN problem.

Observation:
Since subarray must contain only NON-NEGATIVE numbers,
negative number acts as a BREAK → like resetting the window.

So we scan the array and build segments of non-negative numbers.

For each segment:
- Calculate sum
- Track length
- Track starting index
- Update best answer based on:
    1. Higher sum
    2. If same sum → longer length
    3. If same length → smaller starting index
y
--------------------------------------------------

ALGORITHM:

currentSum = 0
start = 0

Loop through array:
    If arr[i] >= 0:
        add to currentSum
        evaluate this updated segment
    Else:
        reset currentSum
        move start

After loop → we have answer

KEY: We evaluate ON THE FLY as we add elements, guaranteeing longest chain

--------------------------------------------------

TIME COMPLEXITY:
O(N)

SPACE COMPLEXITY:
O(1)

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/maximum-sub-array5443/1

--------------------------------------------------
*/

class Solution {
  public:
  
    vector<int> findSubarray(vector<int> &arr) {
        
        long long maxSum = -1;
        long long currSum = 0;
        
        int start = 0;
        int bestStart = -1;
        int bestEnd = -1;
        
        for(int i = 0; i < arr.size(); i++) {
            
            if(arr[i] >= 0) {
                currSum += arr[i];
                
                // Check if this segment is better
                // Longer length beats higher sum (automatically, since we check on the fly)
                if(currSum > maxSum ||
                  (currSum == maxSum && (i - start > bestEnd - bestStart))) {
                    
                    maxSum = currSum;
                    bestStart = start;
                    bestEnd = i;
                }
            }
            else {
                // Reset when negative encountered
                currSum = 0;
                start = i + 1;
            }
        }
        
        // If no non-negative subarray found
        if(bestStart == -1)
            return {-1};
        
        vector<int> result;
        for(int i = bestStart; i <= bestEnd; i++)
            result.push_back(arr[i]);
        
        return result;
    }
};


/*
---------------- DRY RUN ----------------

arr = [1, 2, 5, -7, 2, 6]

i=0, arr[0]=1 (≥0)
  currSum += 1 = 1
  Check: 1 > -1? YES
  → maxSum=1, bestStart=0, bestEnd=0

i=1, arr[1]=2 (≥0)
  currSum += 2 = 3
  Check: 3 > 1? YES
  → maxSum=3, bestStart=0, bestEnd=1

i=2, arr[2]=5 (≥0)
  currSum += 5 = 8
  Check: 8 > 3? YES
  → maxSum=8, bestStart=0, bestEnd=2

i=3, arr[3]=-7 (<0)
  Reset: currSum=0, start=4

i=4, arr[4]=2 (≥0)
  currSum += 2 = 2
  Check: 2 > 8? NO
         2 == 8? NO
  → Keep previous best

i=5, arr[5]=6 (≥0)
  currSum += 6 = 8
  Check: 8 > 8? NO
         8 == 8 AND (5-4 > 2-0)? (1 > 2)? NO
  → Keep previous best (0-2)

Result: arr[0..2] = [1, 2, 5] ✓

--------------------------------------------------

SECOND EXAMPLE:
arr = [-1, 2]

i=0, arr[0]=-1 (<0)
  Reset: currSum=0, start=1

i=1, arr[1]=2 (≥0)
  currSum += 2 = 2
  Check: 2 > -1? YES
  → maxSum=2, bestStart=1, bestEnd=1

Result: arr[1..1] = [2] ✓

--------------------------------------------------

FINAL SUMMARY:

Pattern:
If problem says:
- Only positive / non-negative subarray
- Maximum sum
- Return longest if same sum
→ Treat negative as divider
→ Scan segments and evaluate on the fly

This is a VERY COMMON Amazon / Microsoft problem.

Key Idea:
1. Negative number = break the subarray
2. Evaluate updated segment immediately when adding element
3. This ensures we find longest match for ties

KEY INSIGHT:
By checking on every positive addition, we automatically prefer longer
subarrays over earlier-starting ones because we keep extending greedily.
If sum ties, we only update if NEW length > OLD length.

TIME: O(N)
SPACE: O(1)
*/
