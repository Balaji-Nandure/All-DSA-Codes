/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Subarrays Product Less Than K (GFG)

Given an array of positive integers, count the number of contiguous subarrays
such that the product of elements is less than k.

Example 1:
Input: arr = [1,2,3,4], k = 10
Output: 7
Explanation: {1}, {2}, {3}, {4}, {1,2}, {1,2,3}, {2,3} all have product < 10

Example 2:
Input: arr = [1,9,2,8,6,4,3], k = 100
Output: 16
Explanation: Count of all subarrays with product < 100

Constraints:
1 ≤ n ≤ 10^6
1 ≤ k ≤ 10^15
1 ≤ a[i] ≤ 10^5

GFG: https://www.geeksforgeeks.org/problems/subarrays-product-less-than-k/1
================================================================================
*/


// ============================================================
// APPROACH 1: BRUTE FORCE (All Subarrays Check)
// Time: O(n²), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
- Generate all possible contiguous subarrays
- For each subarray, calculate the product
- Count subarrays where product < k

WHY THIS WORKS:
- Direct approach: examine every subarray
- No optimization, but straightforward logic

EXAMPLE / DRY RUN:
arr = [1, 2, 3, 4], k = 10

Subarrays generated:
[1]          → product = 1 < 10 ✓ count=1
[1,2]        → product = 2 < 10 ✓ count=2
[1,2,3]      → product = 6 < 10 ✓ count=3
[1,2,3,4]    → product = 24 >= 10 ✗
[2]          → product = 2 < 10 ✓ count=4
[2,3]        → product = 6 < 10 ✓ count=5
[2,3,4]      → product = 24 >= 10 ✗
[3]          → product = 3 < 10 ✓ count=6
[3,4]        → product = 12 >= 10 ✗
[4]          → product = 4 < 10 ✓ count=7

Result: 7 ✓
*/
class Solution1 {
public:
    long long countSubArrayProductLessThanK(const vector<int>& arr, int n, long long k) {
        
        long long count = 0;
        
        // Iterate all starting positions
        for(int i = 0; i < n; i++) {
            long long product = 1;
            
            // Iterate all ending positions from i
            for(int j = i; j < n; j++) {
                product *= arr[j];
                
                // If product < k, count this subarray
                if(product < k) {
                    count++;
                } else {
                    break;  // No point checking further (all elements positive)
                }
            }
        }
        
        return count;
    }
};


// ============================================================
// APPROACH 2: SLIDING WINDOW (Two Pointer) ⭐ OPTIMAL
// Time: O(n), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
1. Maintain a window [left, right] with product < k
2. Expand window by moving right pointer
3. When product >= k, shrink from left
4. For each valid window ending at right:
   - All subarrays ending at right and starting from (left to right) are valid
   - Count = (right - left + 1)

WHY THIS WORKS:
- All elements are positive → monotonic property holds
- When we move right, product only increases (or stays same)
- When we move left, product only decreases (or stays same)
- Each element visited at most twice (once by right, once by left)
- Each window contributes exactly (window_size) subarrays

KEY INSIGHT:
Instead of checking all subarrays O(n²), we use the fact that if 
subarray [l..r] has product < k, then ALL subarrays [i..r] where 
l <= i <= r also have product < k (because they use fewer elements).

EXAMPLE / DRY RUN:
arr = [1, 2, 3, 4], k = 10

Iteration 1: right=0, arr[0]=1
  product = 1
  1 < 10 ✓
  window = [0..0], size = 1, count += 1 → count = 1
  
Iteration 2: right=1, arr[1]=2
  product = 1*2 = 2
  2 < 10 ✓
  window = [0..1], size = 2, count += 2 → count = 3
  (subarrays: [0..1], [1..1])
  
Iteration 3: right=2, arr[2]=3
  product = 2*3 = 6
  6 < 10 ✓
  window = [0..2], size = 3, count += 3 → count = 6
  (subarrays: [0..2], [1..2], [2..2])
  
Iteration 4: right=3, arr[3]=4
  product = 6*4 = 24
  24 >= 10 ✗
  Shrink: product = 24/arr[0]=24/1 = 24, left=1
          product = 24/arr[1]=24/2 = 12, left=2
          product = 12/arr[2]=12/3 = 4, left=3
  4 < 10 ✓
  window = [3..3], size = 1, count += 1 → count = 7
  (subarray: [3..3])

Result: 7 ✓
*/
class Solution {  // Main Solution - Use this one
public:
    long long countSubArrayProductLessThanK(const vector<int>& arr, int n, long long k) {
        
        // Edge case: if k <= 1, no subarray possible (all elements >= 1)
        if(k <= 1) return 0;
        
        long long product = 1;       // Current window product
        long long count = 0;         // Answer
        int left = 0;                // Left pointer
        
        // Expand window using right pointer
        for(int right = 0; right < n; right++) {
            
            product *= arr[right];   // Include current element
            
            // Shrink window from left until product < k
            while(product >= k) {
                product /= arr[left];
                left++;
            }
            
            // Count all subarrays ending at 'right'
            // These are: [left..right], [left+1..right], ..., [right..right]
            count += (right - left + 1);
        }
        
        return count;
    }
};


/*
================================================================================
SUMMARY & COMPARISON
================================================================================

APPROACH 1 - Brute Force:
✗ TLE for large inputs (n up to 10^6)
✓ Easy to understand
✓ Useful for small constraints

APPROACH 2 - Sliding Window: ⭐ OPTIMAL
✓ Efficient for all constraints
✓ Single pass with two pointers
✓ Leverages monotonic property of positive numbers
✓ Scalable to very large arrays

WHY SLIDING WINDOW WORKS HERE:
1. All elements are positive ✓
2. Product changes monotonically with window size ✓
3. If [l..r] product >= k, then [l-1..r] product also >= k
   (removing left element decreases product)
4. So we can use two pointers without re-checking past subarrays

STEP-BY-STEP ALGORITHM:
START: left = 0, right = 0, product = 1, count = 0

For each right pointer:
  1. Multiply product by arr[right]
  2. While product >= k:
     - Divide by arr[left]
     - Increment left
  3. Add (right - left + 1) to count

END: Return count

================================================================================
*/
