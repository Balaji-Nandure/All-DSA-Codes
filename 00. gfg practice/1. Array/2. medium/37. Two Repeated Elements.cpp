/*
PROBLEM: Two Repeated Elements (GFG)

Array size = n + 2
Elements are from 1 to n
All elements appear once except TWO elements which appear TWICE.
Return the two repeating numbers in the order of their SECOND appearance.

Example:
Input: n = 4, arr = [1,2,1,3,4,3]
Output: [1,3]

Input: n = 2, arr = [1,2,2,1]
Output: [2,1]
→ 2's second appearance (index 2) comes before 1's second appearance (index 3)

--------------------------------------------------

INTUITION / APPROACH:

Since numbers are from 1 to n, we can use INDEX MAPPING / SIGN MARKING.

Key Idea:
Use the array indices themselves as a "visited marker" by making values negative.

When we visit a number x:
- Go to index (abs(x) - 1)  [since values are 1 to n, not 0 to n-1]
- If arr[index] is already negative → x is repeating (2nd appearance)
- If positive → mark it negative (1st appearance)

Why it works:
- We only need to track which numbers we've seen
- Array indices give us O(1) space for this tracking
- When we see a number twice, its index will be marked negative

--------------------------------------------------

ALGORITHM:

For each element in array:
    index = abs(element) - 1
    
    if arr[index] < 0:
        element is repeating → add to answer
    else:
        mark arr[index] negative

Return in order of detection (which is order of 2nd appearance)

--------------------------------------------------

TIME COMPLEXITY:
O(N) - single pass

SPACE COMPLEXITY:
O(1) - only answer vector, array modified in-place

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/two-repeated-elements/1

LeetCode similar:
https://leetcode.com/problems/find-all-duplicates-in-an-array/

--------------------------------------------------
*/

class Solution {
  public:
  
    vector<int> twoRepeated(int arr[], int n) {
        
        vector<int> ans;
        
        for(int i = 0; i < n + 2; i++) {
            
            int index = abs(arr[i]) - 1;
            
            // If already negative → repeating (2nd appearance)
            if(arr[index] < 0) {
                ans.push_back(abs(arr[i]));
            }
            else {
                // Mark negative on 1st appearance
                arr[index] = -arr[index];
            }
        }
        
        return ans;
    }
};


/*
---------------- DRY RUN ----------------

arr = [1, 2, 1, 3, 4, 3]
n = 4, size = 6

i=0, arr[0]=1
  index = |1|-1 = 0
  arr[0] = 1 > 0 → mark negative
  arr becomes [−1, 2, 1, 3, 4, 3]

i=1, arr[1]=2
  index = |2|-1 = 1
  arr[1] = 2 > 0 → mark negative
  arr becomes [−1, −2, 1, 3, 4, 3]

i=2, arr[2]=1
  index = |1|-1 = 0
  arr[0] = −1 < 0 → 1 is repeating!
  ans = [1]

i=3, arr[3]=3
  index = |3|-1 = 2
  arr[2] = 1 > 0 → mark negative
  arr becomes [−1, −2, −1, 3, 4, 3]

i=4, arr[4]=4
  index = |4|-1 = 3
  arr[3] = 3 > 0 → mark negative
  arr becomes [−1, −2, −1, −3, 4, 3]

i=5, arr[5]=3
  index = |3|-1 = 2
  arr[2] = −1 < 0 → 3 is repeating!
  ans = [1, 3]

Result: [1, 3] ✓

--------------------------------------------------

SECOND EXAMPLE:
arr = [1, 2, 2, 1]
n = 2, size = 4

i=0, arr[0]=1
  index = 0
  arr[0] > 0 → mark negative [−1, 2, 2, 1]

i=1, arr[1]=2
  index = 1
  arr[1] > 0 → mark negative [−1, −2, 2, 1]

i=2, arr[2]=2
  index = 1
  arr[1] = −2 < 0 → 2 is repeating!
  ans = [2]

i=3, arr[3]=1
  index = 0
  arr[0] = −1 < 0 → 1 is repeating!
  ans = [2, 1]

Result: [2, 1] ✓

--------------------------------------------------

FINAL SUMMARY (VERY IMPORTANT PATTERN):

Pattern Name: INDEX MAPPING / SIGN MARKING

When to use:
- Array elements from range [1, n]
- Need to find missing/repeating/duplicates
- Space constraint O(1)
→ Use the indices as a visited tracker!

Key advantages:
1. O(1) space (no extra data structure needed)
2. In-place marking using sign
3. Works with any constraints that give bounded elements

Variants:
- Find single duplicate → XOR all and compare
- Find multiple duplicates → Sign marking
- Find missing number → Math (sum difference) or cyclic sort

Companies: Amazon, Microsoft, Google (very common)

This is a STANDARD INTERVIEW PATTERN that appears in many variants!

TIME: O(N)
SPACE: O(1)
*/
