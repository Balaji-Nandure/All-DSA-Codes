/*
Problem: Rotate and Delete
GFG: https://www.geeksforgeeks.org/problems/rotate-and-delete-1587115621/1

Example:
Input:
arr = [1,2,3,4]

Operation 1:
Rotate -> [4,1,2,3]
Delete (n-k+1)th from beginning
n = 4, k = 1
Delete 4th element -> 3
Array = [4,1,2]

Operation 2:
Rotate -> [2,4,1]
n = 3, k = 2
Delete 2nd element -> 4
Array = [2,1]

Answer = 2

Intuition:
Instead of physically rotating the array,
we can directly simulate the process using vector operations.

At every operation:
1. Rotate right by 1
   -> last element comes to front

2. Delete (n-k) index (0-based)

We repeat this exactly sz/2 times.

Pattern:
Simulation / Array Manipulation

Time Complexity: O(n^2)
- rotation + erase both take O(n)

Space Complexity: O(1)
- ignoring vector internal modifications
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int rotateDelete(vector<int> &arr) {

        int sz = arr.size();

        // Perform exactly sz/2 operations
        for(int k = 1; k <= sz / 2; k++) {

            // -----------------------------
            // Step 1: Right rotate by 1
            // -----------------------------

            int last = arr.back();

            arr.pop_back();

            arr.insert(arr.begin(), last);

            // Current size after rotation
            int n = arr.size();

            // -----------------------------------------
            // Step 2: Delete (n-k+1)th element (1-based)
            // Convert to 0-based index => n-k
            // -----------------------------------------

            int deleteIndex = n - k;

            // If index exists, erase it
            if(deleteIndex >= 0 && deleteIndex < n) {

                arr.erase(arr.begin() + deleteIndex);
            }
        }

        // First element remaining
        return arr[0];
    }
};

/*
Why it works:

After every operation:
- Array becomes rotated
- Then a specific indexed element is removed

We directly simulate the exact process,
so final remaining first element is correct.

Final Summary:
- Rotate right by 1
- Delete (n-k) index
- Repeat sz/2 times
- Return arr[0]
*/


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    EXACT SIMULATION of operations

Think immediately:
    FOLLOW THE STEPS EXACTLY

-----------------------------------------------------

KEY OBSERVATIONS:

1. Array size decreases with each operation
2. Delete position formula: (current_size - k + 1)th element
3. Edge case when delete position <= 0

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling rotation correctly
2. Wrong delete index calculation
3. Forgetting to adjust start after deletion
4. Not reducing array size properly

-----------------------------------------------------

SIMILAR PROBLEMS

- Array Rotation
- Delete Operations
- Simulation Problems
- Josephus Problem variants

-----------------------------------------------------
*/
