/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Longest Subarray with Sum Divisible by K (GFG)

Given an array arr[] and a positive integer k, find the length of the longest
subarray with the sum of elements divisible by k.

Note: If there is no subarray with sum divisible by k, return 0.

Example 1:
Input: arr[] = [2, 7, 6, 1, 4, 5], k = 3
Output: 4
Explanation: Subarray [7, 6, 1, 4] has sum = 18, divisible by 3

Example 2:
Input: arr[] = [-2, 2, -5, 12, -11, -1, 7], k = 3
Output: 5
Explanation: Subarray [2, -5, 12, -11, -1] has sum = -3, divisible by 3

Example 3:
Input: arr[] = [1, 2, -2], k = 2
Output: 2
Explanation: Subarray [2, -2] has sum = 0, divisible by 2

Constraints:
1 ≤ arr.size() ≤ 10^6
1 ≤ k ≤ 10^6
-10^6 ≤ arr[i] ≤ 10^6

GFG: https://www.geeksforgeeks.org/longest-subarray-sum-divisible-k/1
================================================================================
*/


// ============================================================
// APPROACH 1: BRUTE FORCE (All Subarrays)
// Time: O(n²), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
1. Check all possible subarrays
2. For each subarray [i..j], calculate sum
3. Check if sum % k == 0
4. Track maximum length

WHY THIS WORKS:
- Direct approach: examine every subarray
- Simple logic but inefficient for large arrays

EXAMPLE / DRY RUN:
arr = [2, 7, 6, 1, 4, 5], k = 3

Check all subarrays:
[2]       → sum = 2, 2%3 = 2 ✗
[2,7]     → sum = 9, 9%3 = 0 ✓ length = 2
[2,7,6]   → sum = 15, 15%3 = 0 ✓ length = 3
[2,7,6,1] → sum = 16, 16%3 = 1 ✗
[2,7,6,1,4] → sum = 20, 20%3 = 2 ✗
[2,7,6,1,4,5] → sum = 25, 25%3 = 1 ✗
[7]       → sum = 7, 7%3 = 1 ✗
[7,6]     → sum = 13, 13%3 = 1 ✗
[7,6,1]   → sum = 14, 14%3 = 2 ✗
[7,6,1,4] → sum = 18, 18%3 = 0 ✓ length = 4
[7,6,1,4,5] → sum = 23, 23%3 = 2 ✗
[6]       → sum = 6, 6%3 = 0 ✓ length = 1
[6,1]     → sum = 7, 7%3 = 1 ✗
[6,1,4]   → sum = 11, 11%3 = 2 ✗
[6,1,4,5] → sum = 16, 16%3 = 1 ✗
[1]       → sum = 1, 1%3 = 1 ✗
[1,4]     → sum = 5, 5%3 = 2 ✗
[1,4,5]   → sum = 10, 10%3 = 1 ✗
[4]       → sum = 4, 4%3 = 1 ✗
[4,5]     → sum = 9, 9%3 = 0 ✓ length = 2
[5]       → sum = 5, 5%3 = 2 ✗

Maximum length = 4 ✓

Issues:
- O(n²) time too slow for n up to 10^6
*/
class Solution1 {
public:
    int longestSubarray(vector<int>& arr, int k) {
        
        int n = arr.size();
        int maxLen = 0;
        
        // Check all subarrays
        for(int i = 0; i < n; i++) {
            long long sum = 0;
            
            for(int j = i; j < n; j++) {
                sum += arr[j];
                
                // If sum divisible by k, update max length
                if(sum % k == 0) {
                    maxLen = max(maxLen, j - i + 1);
                }
            }
        }
        
        return maxLen;
    }
};


// ============================================================
// APPROACH 2: PREFIX SUM + MODULO + MAP ⭐ OPTIMAL
// Time: O(n), Space: O(k)
// ============================================================
/*
HOW IT WORKS:

KEY INSIGHT - MODULO PROPERTY:
If prefix_sum[i] % k == prefix_sum[j] % k (where i < j):
  Then (prefix_sum[j] - prefix_sum[i]) % k == 0
  Meaning: sum of subarray from i+1 to j is divisible by k!

Algorithm:
1. Store first occurrence of each remainder in a map
2. Use prefix sum to calculate cumulative remainder
3. When we see a remainder again:
   - Length = current_index - first_occurrence[remainder]
4. Handle negative remainders: use ((sum % k) + k) % k

WHY THIS WORKS:
- Separates the problem into remainder tracking
- Instead of O(n²) comparisons, we compare remainders in O(1)
- Map stores only k possible remainders (0 to k-1)

CRITICAL DETAIL - Negative Modulo:
In C++, (-5) % 3 = -2 (negative)
We need positive remainder: ((-5 % 3) + 3) % 3 = (-2 + 3) % 3 = 1

But -5 = -2*3 + 1, so remainder is 1 ✓

EXAMPLE / DRY RUN:
arr = [2, 7, 6, 1, 4, 5], k = 3

Initialize:
map = {0: -1}  ← Store 0 remainder at index -1 (before array)
maxLen = 0, sum = 0

Index 0, arr[0] = 2:
  sum = 0 + 2 = 2
  remainder = 2 % 3 = 2
  map[2] not seen, insert map[2] = 0
  map = {0:-1, 2:0}

Index 1, arr[1] = 7:
  sum = 2 + 7 = 9
  remainder = 9 % 3 = 0
  map[0] already exists at index -1
  length = 1 - (-1) = 2
  maxLen = max(0, 2) = 2
  (subarray [2,7] has sum 9, divisible by 3) ✓

Index 2, arr[2] = 6:
  sum = 9 + 6 = 15
  remainder = 15 % 3 = 0
  map[0] exists at index -1
  length = 2 - (-1) = 3
  maxLen = max(2, 3) = 3
  (subarray [2,7,6] has sum 15, divisible by 3) ✓

Index 3, arr[3] = 1:
  sum = 15 + 1 = 16
  remainder = 16 % 3 = 1
  map[1] not seen, insert map[1] = 3
  map = {0:-1, 1:3, 2:0}

Index 4, arr[4] = 4:
  sum = 16 + 4 = 20
  remainder = 20 % 3 = 2
  map[2] already exists at index 0
  length = 4 - 0 = 4
  maxLen = max(3, 4) = 4
  (subarray [7,6,1,4] at indices 1-4 has sum 18, divisible by 3) ✓

Index 5, arr[5] = 5:
  sum = 20 + 5 = 25
  remainder = 25 % 3 = 1
  map[1] already exists at index 3
  length = 5 - 3 = 2
  maxLen = max(4, 2) = 4
  (subarray [4,5] at indices 4-5 has sum 9, divisible by 3)

Final: maxLen = 4 ✓

Another Example with Negatives:
arr = [-2, 2, -5, 12, -11, -1, 7], k = 3

map = {0: -1}

Index 0, arr[0] = -2:
  sum = -2
  remainder = ((-2 % 3) + 3) % 3 = (-2 + 3) % 3 = 1
  map[1] = 0

Index 1, arr[1] = 2:
  sum = -2 + 2 = 0
  remainder = 0
  map[0] exists at -1
  length = 1 - (-1) = 2
  maxLen = 2

Index 2, arr[2] = -5:
  sum = 0 + (-5) = -5
  remainder = ((-5 % 3) + 3) % 3 = (-2 + 3) % 3 = 1
  map[1] exists at 0
  length = 2 - 0 = 2
  maxLen = 2

Index 3, arr[3] = 12:
  sum = -5 + 12 = 7
  remainder = 7 % 3 = 1
  map[1] exists at 0
  length = 3 - 0 = 3
  maxLen = 3

Index 4, arr[4] = -11:
  sum = 7 + (-11) = -4
  remainder = ((-4 % 3) + 3) % 3 = (-1 + 3) % 3 = 2
  map[2] = 4

Index 5, arr[5] = -1:
  sum = -4 + (-1) = -5
  remainder = ((-5 % 3) + 3) % 3 = 1
  map[1] exists at 0
  length = 5 - 0 = 5
  maxLen = max(3, 5) = 5
  (subarray [2,-5,12,-11,-1] at indices 1-5 has sum -3, divisible by 3) ✓

Index 6, arr[6] = 7:
  sum = -5 + 7 = 2
  remainder = 2 % 3 = 2
  map[2] exists at 4
  length = 6 - 4 = 2
  maxLen = 5

Final: maxLen = 5 ✓
*/
class Solution {  // Main Solution - Use this one
public:
    int longestSubarray(vector<int>& arr, int k) {
        
        int n = arr.size();
        
        // Map to store first occurrence of each remainder
        unordered_map<int, int> remainderIndex;
        
        // Initialize: remainder 0 exists at index -1 (before array starts)
        // This handles case where prefix sum itself is divisible by k
        remainderIndex[0] = -1;
        
        long long sum = 0;
        int maxLen = 0;
        
        for(int i = 0; i < n; i++) {
            
            sum += arr[i];
            
            // Calculate remainder (handle negative numbers)
            int remainder = ((sum % k) + k) % k;
            
            // If this remainder seen before
            if(remainderIndex.find(remainder) != remainderIndex.end()) {
                
                // Subarray from remainderIndex[remainder]+1 to i
                // has sum divisible by k
                int length = i - remainderIndex[remainder];
                maxLen = max(maxLen, length);
            }
            else {
                // First time seeing this remainder, store its index
                remainderIndex[remainder] = i;
            }
        }
        
        return maxLen;
    }
};


/*
================================================================================
SUMMARY & COMPARISON
================================================================================

APPROACH 1 - Brute Force:
✗ TLE for large inputs (n up to 10^6)
✗ O(n²) time complexity
✓ Easy to understand
✓ Works for small constraints

APPROACH 2 - Prefix Sum + Map: ⭐ OPTIMAL
✓ Time: O(n) - single pass through array
✓ Space: O(k) - at most k different remainders
✓ Handles both positive and negative numbers
✓ Avoids nested loops entirely
✓ Uses modular arithmetic property efficiently

WHY IT'S OPTIMAL:
1. Mathematical insight: same remainder → divisible sum
2. Map stores only k possible values (0 to k-1)
3. Single pass → O(n) time
4. No nested loops ever needed

KEY LEARNING - MODULO PROPERTY:
When we have two prefix sums with same remainder:
  prefix[j] % k == prefix[i] % k
  ⟹ (prefix[j] - prefix[i]) % k == 0
  ⟹ sum of subarray from i+1 to j is divisible by k

HANDLING EDGE CASES:
1. Negative numbers: use ((sum % k) + k) % k for positive remainder
2. Whole array divisible: handled by storing 0 at index -1
3. Empty subarrays: we only count subarrays of length ≥ 1

SIMILAR PROBLEMS:
- Subarray Sum Equals K (find subarray with specific sum)
- Longest Subarray with Equal 0s and 1s (use 1/-1 and find sum 0)
- Count of Subarrays with Sum Divisible by K
- LeetCode 974: Subarray Sums Divisible by K

WHEN TO USE EACH:
- Brute Force: Only for small arrays (n < 1000)
- Optimal: Always use for production code or interviews

================================================================================
*/
