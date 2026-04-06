/*
================================================================================
PROBLEM: Binary Array Sorting (GFG - Medium)
================================================================================

PROBLEM STATEMENT:
Given a binary array arr[] containing only 0s and 1s, rearrange it in increasing
order IN PLACE (without using extra space).

Examples:
1. arr[] = [1, 0, 1, 1, 0]
   Output: [0, 0, 1, 1, 1]

2. arr[] = [1, 0, 1, 1, 1, 1, 1, 0, 0, 0]
   Output: [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]

3. arr[] = [1, 1, 1, 1]
   Output: [1, 1, 1, 1]

Constraints:
- 1 ≤ arr.size() ≤ 10^6
- arr[i] ∈ {0, 1}

KEY OBSERVATION:
Since array contains ONLY 0s and 1s, sorting means:
- All 0s should come first
- Followed by all 1s
No comparison needed!

================================================================================
COMPARISON OF APPROACHES:
================================================================================

Approach     | Time   | Space | Passes | Simplicity | When to use
Counting     | O(N)   | O(1)  | 2      | Simple ✓   | For simplicity ✓ BEST
Two Pointer  | O(N)   | O(1)  | 1      | Medium ✓   | For interview technique

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;


// ============================================================
// APPROACH 1: COUNTING METHOD
// Time: O(N), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
1. Scan array once → count how many 0s exist
2. First count positions = 0
3. Remaining positions = 1

WHY THIS WORKS:
- Binary array has only TWO distinct values
- Once we know count of 0s, we know everything
- First 'count' positions must be 0, rest must be 1
- This arrangement is sorted and in-place

COMPLEXITY:
- Time: O(N) for counting + O(N) for filling = O(N)
- Space: O(1) - only one integer variable

WHEN TO USE:
- Simplest and most intuitive approach
- Works great for limited distinct values
- Preferred in interviews for clarity


DRY RUN: arr[] = [1, 0, 1, 1, 0]

Step 1: Count zeros
Scan: arr[0]=1(skip), arr[1]=0(count), arr[2]=1(skip), 
      arr[3]=1(skip), arr[4]=0(count)
count_0 = 2

Step 2: Fill first 2 positions with 0
arr[0] = 0 → arr = [0, 0, 1, 1, 0]
arr[1] = 0 → arr = [0, 0, 1, 1, 0]

Step 3: Fill remaining with 1
arr[2] = 1 → arr = [0, 0, 1, 1, 0]
arr[3] = 1 → arr = [0, 0, 1, 1, 0]
arr[4] = 1 → arr = [0, 0, 1, 1, 1]

RESULT: [0, 0, 1, 1, 1] ✓ SORTED!
*/

class Solution1 {
public:
    void binarySort(vector<int>& arr) {
        int n = arr.size();
        int count_0 = 0;
        
        // Step 1: Count number of 0s
        for(int x : arr) {
            if(x == 0)
                count_0++;
        }
        
        // Step 2: Fill first count_0 positions with 0
        for(int i = 0; i < count_0; i++) {
            arr[i] = 0;
        }
        
        // Step 3: Fill remaining positions with 1
        for(int i = count_0; i < n; i++) {
            arr[i] = 1;
        }
    }
};


// ============================================================
// APPROACH 2: TWO POINTER (PARTITION TECHNIQUE)
// Time: O(N), Space: O(1)
// ============================================================
/*
HOW IT WORKS:
Partition 0s to left and 1s to right using two pointers:

1. left pointer: scans from start
2. right pointer: scans from end
3. Goal: left half has all 0s, right half has all 1s

Algorithm:
while (left < right):
  if arr[left] == 0 → it's in right place, move left++
  if arr[right] == 1 → it's in right place, move right--
  if arr[left] == 1 AND arr[right] == 0 → SWAP them, both move
  
After loop ends: entire array is partitioned ✓

WHY THIS WORKS:
- 0s and 1s naturally partition when we swap misplaced pairs
- Similar to quicksort partition logic (Dutch National Flag)
- Maintains invariant: left area = 0s, right area = 1s

COMPLEXITY:
- Time: O(N) - each element touched at most twice
- Space: O(1) - only two pointers

WHEN TO USE:
- Show two-pointer technique knowledge
- When you want to do in single pass
- More advanced than counting


DRY RUN: arr[] = [1, 0, 1, 1, 0]

Initial: left=0, right=4

Pass 1:
- arr[left=0] = 1 (wrong, need to move)
- arr[right=4] = 0 (wrong, need to move)
- Swap them → arr = [0, 0, 1, 1, 1]
- left++, right-- → left=1, right=3

Pass 2:
- arr[left=1] = 0 (correct, move left++)
- left=2 (now arr[2]=1, wrong)
- arr[right=3] = 1 (correct, move right--)
- right=2 → now left=right=2, loop ends

RESULT: [0, 0, 1, 1, 1] ✓ SORTED!
*/

class Solution2 {

public:
    void binarySort(vector<int>& arr) {
        int n = arr.size();
        int left = 0, right = n - 1;
        
        while(left < right) {
            // Move left forward if it already holds 0
            while(left < right && arr[left] == 0)
                left++;
            
            // Move right backward if it already holds 1
            while(left < right && arr[right] == 1)
                right--;
            
            // If we reach here:
            // arr[left] = 1 (wrong place for left)
            // arr[right] = 0 (wrong place for right)
            // Swap them to fix both
            if(left < right) {
                swap(arr[left], arr[right]);
                left++;
                right--;
            }
        }
    }
};


// ============================================================
// MAIN SOLUTION (Use Solution1 - simpler and clearer)
// ============================================================

class Solution {
public:
    void sortArray(vector<int>& arr) {
        // Use Solution1: Counting (RECOMMENDED)
        Solution1 sol;
        sol.binarySort(arr);
        
        // Alternative: Use Solution2 (Two Pointer) if needed
        // Solution2 sol2;
        // sol2.binarySort(arr);
    }
};


/*
================================================================================
EDGE CASES:
================================================================================

1. All 0s: [0, 0, 0]
   → [0, 0, 0] ✓

2. All 1s: [1, 1, 1]
   → [1, 1, 1] ✓

3. Single element: [0] or [1]
   → [0] or [1] ✓

4. Already sorted: [0, 0, 1, 1]
   → [0, 0, 1, 1] ✓ (no change needed)

5. Reverse sorted: [1, 1, 0, 0]
   → [0, 0, 1, 1] ✓

================================================================================
TEST CASES:
================================================================================

Test 1: [1, 0, 1, 1, 0]
Expected: [0, 0, 1, 1, 1]
Solution1 (Counting): ✓
Solution2 (Two Pointer): ✓

Test 2: [1, 0, 1, 1, 1, 1, 1, 0, 0, 0]
Expected: [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
Solution1 (Counting): ✓
Solution2 (Two Pointer): ✓

Test 3: [1, 1, 1, 1]
Expected: [1, 1, 1, 1]
Solution1 (Counting): ✓
Solution2 (Two Pointer): ✓

================================================================================
KEY PATTERNS & INTERVIEW TIPS:
================================================================================

1. LIMITED DISTINCT VALUES:
   When array has only K distinct values and K is small
   → Counting approach reduces time complexity
   
2. PARTITION PROBLEMS:
   Separating elements by condition
   → Two pointer technique is powerful
   → Foundation for quicksort
   
3. IN-PLACE SORTING:
   No extra space allowed
   → Both approaches are O(1) space
   → Better than comparison sorting
   
4. WHEN TO USE COUNTING (Solution1):
   - Elements are from limited range
   - Simplicity matters
   - Interview: show clear thinking
   
5. WHEN TO USE TWO POINTERS (Solution2):
   - Show algorithmic technique
   - Use fewer passes
   - Interview: show advanced knowledge

================================================================================
TAKEAWAY:

Binary array sorting shows two COMPLETELY DIFFERENT approaches:

METHOD 1 (Solution1): COUNTING
- Count 0s, then fill positions
- Simpler logic, clearer thinking
- Best for interviews when clarity is important

METHOD 2 (Solution2): TWO POINTER PARTITION
- Use pointers from both ends
- Advanced technique foundation
- Best for showing algorithmic knowledge

BOTH ARE O(1) space and O(N) time!
Just different ways of thinking about the problem.

================================================================================
*/
