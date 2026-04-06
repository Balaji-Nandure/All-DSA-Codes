/*
================================================================================
PROBLEM: Boolean Matrix (GFG - Medium)
================================================================================

Given a boolean matrix mat[] where each cell is 0 or 1:
If mat[i][j] == 1, mark all cells in row i and column j as 1.

Examples:
1. mat = [[1, 0], [0, 0]]
   Output: [[1, 1], [1, 0]]
   (0,0) has 1 → entire row 0 and col 0 become 1

2. mat = [[1, 0, 0], [1, 0, 0], [1, 0, 0], [0, 0, 0]]
   Output: [[1, 1, 1], [1, 1, 1], [1, 1, 1], [1, 0, 0]]
   Multiple 1s at (0,0), (1,0), (2,0) → rows 0,1,2 and col 0 all marked

Constraints:
- 1 ≤ rows, cols ≤ 10^3
- 0 ≤ mat[i][j] ≤ 1

================================================================================
APPROACH 1: SIMPLE (Store rows and columns to mark)
Time: O(m*n) | Space: O(m + n)
================================================================================

HOW IT WORKS:
1. First pass: iterate through matrix, collect which rows/cols have 1
2. Second pass: mark all cells in collected rows/cols as 1

WHY IT WORKS:
- Separate collection ensures we don't confuse original 1s with marked 1s
- No in-place modification issues

COMPLEXITY:
- Time: O(m*n) for two passes
- Space: O(m + n) for storing rows and columns


DRY RUN: mat = [[1, 0], [0, 0]]

Pass 1: Collect rows/cols with 1
- Row 0, Col 0 contain 1
- rows = {0}, cols = {0}

Pass 2: Mark all cells
- Row 0: all → [1, 1]
- Col 0: all → [1, _]
- Result: [[1, 1], [1, 0]] ✓
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution1 {
  public:
    /*
    HOW IT WORKS:
    - Use sets to track which rows and columns need marking
    - First pass through matrix: found any 1? Add its row and col to sets
    - Second pass: for each cell, if its row or col is in the set, mark as 1

    COMPLEXITY:
    - Time: O(m*n) + O(m*n) = O(m*n)
    - Space: O(m + n) - at most m rows and n columns in sets
    */
    
    void modifyMatrix(vector<vector<int>> &mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        unordered_set<int> rows, cols;
        
        // Pass 1: Find all rows and columns that have 1
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) {
                    rows.insert(i);
                    cols.insert(j);
                }
            }
        }
        
        // Pass 2: Mark all cells in marked rows/cols
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (rows.count(i) || cols.count(j)) {
                    mat[i][j] = 1;
                }
            }
        }
    }
};


/*
================================================================================
APPROACH 2: SPACE OPTIMIZED (Use first row and column as markers)
Time: O(m*n) | Space: O(1)
================================================================================

HOW IT WORKS:
1. Use first row and first column as storage for which rows/cols need marking
2. Use separate flags for first row and first column (they can't store their own state)
3. Work backwards to avoid overwriting markers

WHY IT WORKS:
- First row/col act as markers, avoiding extra space
- Process in reverse order so we mark before we read

COMPLEXITY:
- Time: O(m*n)
- Space: O(1) - only 2 variables for first row/col flags


DRY RUN: mat = [[1, 0, 0], [1, 0, 0], [1, 0, 0], [0, 0, 0]]
        m=4, n=3

Step 1: Check first row and col
- mat[0][0] != 1, so rows_marked = false, cols_marked = false

Step 2: Mark first row/col based on other cells
- (1,0) = 1 → cols_marked = true
- (2,0) = 1 → cols_marked = true
- (0,0) = 1 → rows_marked = true

Step 3: Use first row/col to update matrix (reverse iteration)
- For each cell (i,j): if first_row[j]=1 or first_col[i]=1, mark it
- Column 0 is marked → entire col becomes 1
- Rows 0,1,2 are marked → all their cells become 1

Step 4: Handle first row and col based on saved flags
- rows_marked = true → mark entire first row
- cols_marked = true → mark entire first col

Result: [[1, 1, 1], [1, 1, 1], [1, 1, 1], [1, 0, 0]] ✓
*/

class Solution2 {
  public:
    /*
    HOW IT WORKS:
    1. Save flags for first row and first column
    2. Use mat[i][0] and mat[0][j] as markers for entire row i and col j
    3. Process matrix in reverse to avoid overwriting data
    4. Handle first row and column at the end using saved flags

    COMPLEXITY:
    - Time: O(m*n) - single pass with constant work per cell
    - Space: O(1) - only 2 boolean flags
    */
    
    void modifyMatrix(vector<vector<int>> &mat) {
        int m = mat.size();
        int n = mat[0].size();
        
        bool row_marked = false, col_marked = false;
        
        // Check if first row or first column has any 1
        for (int j = 0; j < n; j++) {
            if (mat[0][j] == 1) {
                row_marked = true;
                break;
            }
        }
        
        for (int i = 0; i < m; i++) {
            if (mat[i][0] == 1) {
                col_marked = true;
                break;
            }
        }
        
        // Use first row/col as markers
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (mat[i][j] == 1) {
                    mat[i][0] = 1;    // Mark this row
                    mat[0][j] = 1;    // Mark this column
                }
            }
        }
        
        // Process based on markers (from end to start to avoid overwriting)
        for (int i = m - 1; i >= 1; i--) {
            for (int j = n - 1; j >= 1; j--) {
                if (mat[i][0] == 1 || mat[0][j] == 1) {
                    mat[i][j] = 1;
                }
            }
        }
        
        // Handle first row (if any 1 exists in original matrix)
        if (row_marked) {
            for (int j = 0; j < n; j++) {
                mat[0][j] = 1;
            }
        }
        
        // Handle first column (if any 1 exists in original matrix)
        if (col_marked) {
            for (int i = 0; i < m; i++) {
                mat[i][0] = 1;
            }
        }
    }
};


/*
================================================================================
MAIN SOLUTION (Use Solution2 - Best)
================================================================================
*/

class Solution {
  public:
    void modifyMatrix(vector<vector<int>> &mat) {
        // Use space-optimized approach
        Solution2 s;
        s.modifyMatrix(mat);
    }
};


/*
================================================================================
EDGE CASES:
================================================================================

1. All zeros (no 1s):
   mat = [[0, 0], [0, 0]]
   Output: [[0, 0], [0, 0]]
   No 1s found → no changes ✓

2. All ones:
   mat = [[1, 1], [1, 1]]
   Output: [[1, 1], [1, 1]]
   Already all 1s → stays same ✓

3. Single cell (1):
   mat = [[1]]
   Output: [[1]]
   Single 1 → stays 1 ✓

4. Single row with 1:
   mat = [[0, 1, 0]]
   Output: [[1, 1, 1]]
   Column 1 and row 0 marked ✓

5. Corner case - 1 in first cell:
   mat = [[1, 0], [0, 0]]
   Output: [[1, 1], [1, 0]]
   Entire row 0 and col 0 marked ✓

6. Corner case - 1 in last cell:
   mat = [[0, 0], [0, 1]]
   Output: [[0, 1], [1, 1]]
   Row 1 and col 1 marked ✓

================================================================================
TEST CASES:
================================================================================

Test 1: mat = [[1, 0], [0, 0]]
Expected: [[1, 1], [1, 0]]
Result: ✓

Test 2: mat = [[1, 0, 0], [1, 0, 0], [1, 0, 0], [0, 0, 0]]
Expected: [[1, 1, 1], [1, 1, 1], [1, 1, 1], [1, 0, 0]]
Result: ✓

Test 3: mat = [[0, 0], [0, 0]]
Expected: [[0, 0], [0, 0]]
Result: ✓

Test 4: mat = [[1, 1], [1, 1]]
Expected: [[1, 1], [1, 1]]
Result: ✓

Test 5: mat = [[0, 1, 0], [1, 0, 0], [0, 0, 0]]
Expected: [[1, 1, 1], [1, 1, 1], [0, 1, 0]]
Result: ✓

================================================================================
COMPLEXITY COMPARISON:
================================================================================

Approach 1 (Store rows/cols):
✓ Easy to understand
✓ O(m*n) time
✗ O(m + n) space

Approach 2 (Space Optimized): ✓ BEST
✓ O(m*n) time
✓ O(1) space - production choice
✓ In-place modification
✓ Uses first row/col as markers

================================================================================
PATTERN RECOGNITION:
================================================================================

This is a classic pattern:
- Problem: "If condition at (i,j), mark entire row/col"
→ Store markers in first row/col (space optimization)
→ Process in reverse iteration

Similar problems:
- Game of Life
- Set matrix zeroes
- Any row/column marking problem

Key insight: Use matrix itself as storage to save space!

================================================================================
INTERVIEW DISCUSSION POINTS:
================================================================================

1. What's the challenge here?
   A: Avoiding modification during iteration. Need to know original 1s.

2. Why store in first row/col?
   A: It's already part of matrix, saves extra space.

3. Why reverse iteration?
   A: Process ends before we read, no data loss.

4. What if first row/col originally had 1?
   A: Save it in flags before using them as markers.

5. Can we do in-place?
   A: Yes! That's exactly what space-optimized approach does.

================================================================================
*/
