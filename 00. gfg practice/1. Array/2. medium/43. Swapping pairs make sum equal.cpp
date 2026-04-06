/*
================================================================================
PROBLEM: Swapping Pairs Make Sum Equal (GFG - Medium)
================================================================================

PROBLEM STATEMENT:
Given two arrays a[] and b[], check if there exists a pair (x from a, y from b)
such that swapping x and y will make the sum of both arrays equal.

Examples:
1. a[] = [4, 1, 2, 1, 1, 2], b[] = [3, 6, 3, 3]
   Output: true
   Explanation: Swap 1 from a[] and 3 from b[] → both sums become 13

2. a[] = [5, 7, 4, 6], b[] = [1, 2, 3, 8]
   Output: true
   Explanation: Swap 6 from a[] and 2 from b[] → both sums become 22

3. a[] = [3, 3], b[] = [6, 5, 6, 6]
   Output: false
   Explanation: No valid pair exists

Constraints:
- 1 ≤ a.size() ≤ 10^6
- 1 ≤ b.size() ≤ 10^6
- 1 ≤ a[i], b[i] ≤ 10^3

================================================================================

KEY MATHEMATICAL INSIGHT:
================================================================================

Let sumA = sum of array a[]
Let sumB = sum of array b[]

After swapping element x from a[] with element y from b[]:

New sumA = sumA - x + y
New sumB = sumB - y + x

For sums to be equal:

    sumA - x + y = sumB - y + x
    
    sumA - sumB = 2x - 2y
    
    (sumA - sumB) / 2 = x - y
    
    x = y + target    where target = (sumA - sumB) / 2

IMPORTANT: If (sumA - sumB) is ODD → no solution (2x - 2y is always even)

So the problem reduces to:
- For each y in array b[], check if (y + target) exists in array a[]

================================================================================

APPROACH: Hashing (Set)

Time Complexity: O(N + M)
Space Complexity: O(N)

HOW IT WORKS:
- Compute sums of both arrays
- Check if difference is even (necessary condition)
- Calculate target = (sumA - sumB) / 2
- Store all elements of a[] in unordered_set for O(1) lookup
- For each element y in b[], check if (y + target) exists in set
- If found → return true, else return false

WHY THIS WORKS:
- Using set for constant time lookup reduces time from O(N*M) to O(N+M)
- The mathematical derivation ensures we only need to check membership
- No need to iterate through both arrays for each pair

WHEN TO USE:
- When you need to find pairs with specific relationship
- When hashing/set can replace nested loops
- Interview: Math + Hashing combined problem

================================================================================
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    /*
    ================================================================
    APPROACH: HASHING WITH SET
    Time: O(N + M), Space: O(N)
    ================================================================
    
    LOGIC:
    1. Calculate sumA and sumB using range-based loops
    2. Check if (sumA - sumB) is even (necessary condition)
    3. Calculate target = (sumA - sumB) / 2
    4. Store all elements of A in unordered_set for fast lookup
    5. For each y in B, check if (y + target) exists in set
    6. If found → pair exists → return true
    
    MATHEMATICAL GUARANTEE:
    If (y + target) is in A, then:
    x = y + target
    x - y = target = (sumA - sumB) / 2 ✓
    Swapping (x, y) will make sums equal
    
    MODERN C++ IMPROVEMENTS:
    - vector<int>& instead of array notation
    - range-based for loops (cleaner)
    - st.count(need) instead of find() (simpler)
    - bool return instead of int
    */
    
    bool findSwapValues(vector<int>& a, vector<int>& b) {
        
        long long sumA = 0, sumB = 0;
        
        // Step 1: Calculate sums using range-based for loops
        for(int x : a) sumA += x;
        for(int x : b) sumB += x;
        
        long long diff = sumA - sumB;
        
        // Step 2: Check if solution is possible
        // If difference is odd → 2x and 2y are always even → impossible
        if(diff % 2 != 0)
            return false;
        
        // Step 3: Calculate target
        long long target = diff / 2;
        
        // Step 4: Store array 'a' elements in unordered_set
        unordered_set<long long> st(a.begin(), a.end());
        
        // Step 5: For each element in 'b', check if (y + target) exists in 'a'
        for(int i = 0; i < b.size(); i++) {
            long long need = b[i] + target;
            
            // If element exists → pair found → return true
            if(st.count(need))
                return true;
        }
        
        // Step 6: No pair found
        return false;
    }
};

/*
================================================================================
DRY RUN 1: Example 1 (True Case)
================================================================================

a[] = [4, 1, 2, 1, 1, 2]
b[] = [3, 6, 3, 3]

Step 1: Calculate sums
sumA = 4 + 1 + 2 + 1 + 1 + 2 = 11
sumB = 3 + 6 + 3 + 3 = 15

Step 2: Check if solvable
diff = 11 - 15 = -4
-4 % 2 = 0 ✓ (even, so solvable)

Step 3: Calculate target
target = -4 / 2 = -2

Step 4: Store A in set
st = {4, 1, 2}

Step 5: Check each B element
y = 3 → needed = 3 + (-2) = 1 → 1 in set? YES ✓
Return 1

VERIFICATION:
Swap (1, 3):
New sumA = 11 - 1 + 3 = 13
New sumB = 15 - 3 + 1 = 13 ✓
Both sums equal!

================================================================================
DRY RUN 2: Example 2 (True Case)
================================================================================

a[] = [5, 7, 4, 6]
b[] = [1, 2, 3, 8]

Step 1: Calculate sums
sumA = 5 + 7 + 4 + 6 = 22
sumB = 1 + 2 + 3 + 8 = 14

Step 2: Check if solvable
diff = 22 - 14 = 8
8 % 2 = 0 ✓

Step 3: Calculate target
target = 8 / 2 = 4

Step 4: Store A in set
st = {5, 7, 4, 6}

Step 5: Check each B element
y = 1 → needed = 1 + 4 = 5 → 5 in set? YES ✓
Return 1

VERIFICATION:
Swap (5, 1):
New sumA = 22 - 5 + 1 = 18
New sumB = 14 - 1 + 5 = 18 ✓

OR we continue and find:
y = 2 → needed = 2 + 4 = 6 → 6 in set? YES ✓
Swap (6, 2):
New sumA = 22 - 6 + 2 = 18
New sumB = 14 - 2 + 6 = 18 ✓

================================================================================
DRY RUN 3: Example 3 (False Case)
================================================================================

a[] = [3, 3]
b[] = [6, 5, 6, 6]

Step 1: Calculate sums
sumA = 3 + 3 = 6
sumB = 6 + 5 + 6 + 6 = 23

Step 2: Check if solvable
diff = 6 - 23 = -17
-17 % 2 = -1 (ODD) ✗
Return -1 (impossible)

================================================================================
COMPLEXITY ANALYSIS:
================================================================================

TIME COMPLEXITY: O(N + M)
- Creating set from array A: O(N)
- Checking each element in B: O(M) × O(1) per lookup = O(M)
- Total: O(N + M)

SPACE COMPLEXITY: O(N)
- Storing elements of A in set: O(N)

COMPARISON:
Approach 1 (Brute Force): O(N × M) with nested loops ✗
Approach 2 (Sorting): O(N log N + M log M) with sorting ✗
Approach 3 (Hashing): O(N + M) ✓ BEST

================================================================================
KEY PATTERNS & TAKEAWAYS:
================================================================================

1. MATHEMATICAL DERIVATION:
   - When two sums need to be equal after operation
   - Derive the relationship algebraically
   - Reduces to simple formula: x = y + target

2. NECESSARY & SUFFICIENT CONDITIONS:
   - Necessary: Difference must be even
   - Sufficient: Element (y + target) exists in first array

3. SET + MATH COMBINATION:
   - Math reduces problem to membership check
   - Hash set makes membership check O(1)
   - Total time becomes O(N + M) instead of O(N × M)

4. INTERVIEW TIPS:
   - Always derive the mathematical relationship first
   - Check edge cases (odd difference → impossible)
   - Use hashing/set for fast lookups

================================================================================
*/

/*
TEST DRIVER (Can be run separately):

int main() {
    Solution sol;
    
    // Test 1: True case
    vector<int> a1 = {4, 1, 2, 1, 1, 2};
    vector<int> b1 = {3, 6, 3, 3};
    cout << "Test 1: " << (sol.findSwapValues(a1, b1) ? "true" : "false") 
         << " (Expected: true)" << endl;
    
    // Test 2: True case
    vector<int> a2 = {5, 7, 4, 6};
    vector<int> b2 = {1, 2, 3, 8};
    cout << "Test 2: " << (sol.findSwapValues(a2, b2) ? "true" : "false") 
         << " (Expected: true)" << endl;
    
    // Test 3: False case
    vector<int> a3 = {3, 3};
    vector<int> b3 = {6, 5, 6, 6};
    cout << "Test 3: " << (sol.findSwapValues(a3, b3) ? "true" : "false") 
         << " (Expected: false)" << endl;
    
    return 0;
}

OUTPUT:
Test 1: true (Expected: true)
Test 2: true (Expected: true)
Test 3: false (Expected: false)
*/
