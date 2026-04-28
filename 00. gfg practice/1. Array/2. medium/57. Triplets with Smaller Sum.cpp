/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Triplets with Smaller Sum (GFG)

Given an array arr[] of distinct integers of size n and a value sum, find the
count of triplets (i, j, k) with i<j<k where arr[i] + arr[j] + arr[k] < sum.

Note: Order of indices must be maintained (i<j<k in terms of indices, not values).

Example 1:
Input: n = 4, sum = 2, arr[] = {-2, 0, 1, 3}
Output: 2
Explanation: Triplets with sum < 2:
  - (-2, 0, 1) = -1 < 2 ✓
  - (-2, 0, 3) = 1 < 2 ✓

Example 2:
Input: n = 5, sum = 12, arr[] = {5, 1, 3, 4, 7}
Output: 4
Explanation: Triplets with sum < 12:
  - (1, 3, 4) = 8 < 12 ✓
  - (5, 1, 3) = 9 < 12 ✓
  - (1, 3, 7) = 11 < 12 ✓
  - (5, 1, 4) = 10 < 12 ✓

Constraints:
3 ≤ N ≤ 10^3
-10^3 ≤ arr[i] ≤ 10^3

GFG: https://www.geeksforgeeks.org/problems/triplets-with-smaller-sum/1
================================================================================
*/


// ============================================================
// APPROACH 1: BRUTE FORCE (All Triplets)
// Time: O(n³), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
1. Use three nested loops to generate all triplets
2. For each triplet (i, j, k) where i<j<k
3. Calculate sum and compare with target sum
4. Count triplets where sum < target

WHY THIS WORKS:
- Direct approach: check every possible triplet
- Simple but inefficient for large arrays

EXAMPLE / DRY RUN:
arr[] = {-2, 0, 1, 3}, sum = 2

Triplets with i<j<k (indices):
(0,1,2): arr[0]+arr[1]+arr[2] = -2+0+1 = -1 < 2 ✓ count=1
(0,1,3): arr[0]+arr[1]+arr[3] = -2+0+3 = 1 < 2 ✓ count=2
(0,2,3): arr[0]+arr[2]+arr[3] = -2+1+3 = 2 < 2 ✗
(1,2,3): arr[1]+arr[2]+arr[3] = 0+1+3 = 4 < 2 ✗

Total: 2 ✓

Issues:
- O(n³) too slow for n up to 10^3
- n=1000 → 10^9 operations (TLE)
*/
class Solution1 {
public:
    long long countTriplets(int n, long long sum, long long arr[]) {
        
        long long count = 0;
        
        // Generate all triplets with i < j < k (indices)
        for(int i = 0; i < n - 2; i++) {
            for(int j = i + 1; j < n - 1; j++) {
                for(int k = j + 1; k < n; k++) {
                    
                    // Check if triplet sum < target sum
                    if(arr[i] + arr[j] + arr[k] < sum) {
                        count++;
                    }
                }
            }
        }
        
        return count;
    }
};


// ============================================================
// APPROACH 2: SORTING + TWO POINTER ⭐ OPTIMAL
// Time: O(n²), Space: O(1)
// ============================================================
/*
HOW IT WORKS:

KEY INSIGHT:
If we sort the array, once we fix first element arr[i]:
- We can use two pointers (left, right) for remaining elements
- If arr[i] + arr[left] + arr[right] < sum:
  → ALL triplets (i, left, left+1), (i, left, left+2), ..., (i, left, right)
     will have sum < sum (because all elements between left+1 and right
     are ≥ arr[left+1] when sorted)
  → Count += (right - left)
  → Move left pointer forward
- Else (sum too large):
  → Move right pointer backward

IMPORTANT NOTE:
The problem statement says find triplets with i<j<k (indices should be
in order), BUT after sorting we lose the original indices. 
Looking at the examples:
- (1, 3, 4) doesn't mean indices 1,3,4 - it means the SORTED values
- The constraint is satisfied because when we sort, the relative ordering
  of elements changes but we're counting valid triplet combinations

After sorting, we can focus on VALUES not indices.

WHY THIS WORKS:
- Sorting enables two-pointer technique
- Once arr[i] + arr[left] + arr[right] < sum:
  - We know arr[i] + arr[left] + arr[right-1] < sum
  - We know arr[i] + arr[left] + arr[right-2] < sum
  - And so on...
  - So we can count (right - left) triplets at once
- Avoids nested loop for the third pointer

EXAMPLE / DRY RUN:
arr[] = {5, 1, 3, 4, 7}, sum = 12

Step 1: Sort array
arr[] = {1, 3, 4, 5, 7}

Step 2: Two pointer approach
i = 0, arr[i] = 1:
  left = 1 (arr[1]=3), right = 4 (arr[4]=7)
  
  sum_triplet = 1+3+7 = 11 < 12 ✓
  Count all triplets: (1,3,7), (1,3,5), (1,3,4)
  count += (4-1) = 3 → count = 3
  Move left++, left = 2
  
  sum_triplet = 1+4+7 = 12 < 12 ✗
  Move right--, right = 3
  
  sum_triplet = 1+4+5 = 10 < 12 ✓
  Count: (1,4,5)
  count += (3-2) = 1 → count = 4
  Move left++, left = 3
  
  sum_triplet = 1+5+5 ✗ (left = right, stop)
  
i = 1, arr[i] = 3:
  left = 2 (arr[2]=4), right = 4 (arr[4]=7)
  
  sum_triplet = 3+4+7 = 14 < 12 ✗
  Move right--, right = 3
  
  sum_triplet = 3+4+5 = 12 < 12 ✗
  Move right--, right = 2
  
  left = right, stop

i = 2, arr[i] = 4:
  left = 3 (arr[3]=5), right = 4 (arr[4]=7)
  
  sum_triplet = 4+5+7 = 16 < 12 ✗
  Move right--, right = 3
  
  left = right, stop

Final count = 4 ✓

Verification with original values:
- (1,3,7): values {1,3,7} or from original indices doesn't matter
- (1,3,5): values {1,3,5}
- (1,4,5): values {1,4,5}
- (1,3,4): values {1,3,4}

All 4 distinct triplets ✓
*/
class Solution {  // Main Solution - Use this one
public:
    long long countTriplets(int n, long long sum, long long arr[]) {
        
        // Step 1: Sort the array
        sort(arr, arr + n);
        
        long long count = 0;
        
        // Step 2: Fix first element and use two pointers for remaining
        for(int i = 0; i < n - 2; i++) {
            
            int left = i + 1;
            int right = n - 1;
            
            // Step 3: Two pointer approach
            while(left < right) {
                
                long long tripletSum = arr[i] + arr[left] + arr[right];
                
                if(tripletSum < sum) {
                    // All triplets from (i, left, left+1...right) are valid
                    count += (right - left);
                    
                    // Move left pointer to explore larger numbers
                    left++;
                }
                else {
                    // Sum too large, move right pointer backward
                    right--;
                }
            }
        }
        
        return count;
    }
};


/*
================================================================================
SUMMARY & COMPARISON
================================================================================

APPROACH 1 - Brute Force:
✗ O(n³) too slow for n up to 10^3 (TLE)
✗ For n=1000, generates ~166 million triplets
✓ Easy to understand and implement

APPROACH 2 - Sorting + Two Pointer: ⭐ OPTIMAL
✓ O(n²) - quadratic time
✓ For n=1000, ~500K operations (fast)
✓ Space: O(1) if we ignore sorting (depends on sort algorithm)
✓ Smart counting: when one triplet works, count multiple at once
✓ Scales well for constraint n ≤ 10^3

WHY SORTING HELPS:
1. Enables monotonic two-pointer movement
2. When (i, left, right) satisfies: all (i, left, left+1...right) satisfy too
3. Avoids explicit enumeration of all triplets

KEY INSIGHT - Counting All Valid Triplets at Once:
When arr[i] + arr[left] + arr[right] < sum:
  - arr[i] + arr[left] + arr[right] < sum     ✓
  - arr[i] + arr[left] + arr[right-1] < sum   ✓ (because arr[right-1] < arr[right])
  - arr[i] + arr[left] + arr[right-2] < sum   ✓
  - ...
  - arr[i] + arr[left] + arr[left+1] < sum    ✓
  Total = (right - left) triplets ✓

PROBLEM CLARIFICATION:
The problem asks for i<j<k but looking at examples, it means:
- We're counting distinct triplet VALUES, not index positions
- After sorting to optimize, we focus on the sorted values
- The two-pointer approach validates this interpretation

SIMILAR PROBLEMS:
- 3Sum (find triplets with sum == target)
- 3Sum Closest (find triplets with sum closest to target)
- Count Triplets with Given Sum (LeetCode variation)
- 4Sum (extend to 4 elements)

WHEN TO USE EACH:
- Brute Force: Teaching or n ≤ 100
- Optimal: Production code or competitive programming

================================================================================
*/
