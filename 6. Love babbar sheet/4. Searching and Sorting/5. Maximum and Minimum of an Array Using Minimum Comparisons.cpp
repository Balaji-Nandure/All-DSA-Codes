// Problem: Maximum and Minimum of an Array Using Minimum Comparisons & Middle of Three
// Link (GFG): https://www.geeksforgeeks.org/problems/middle-of-three2926/1
// Article: https://www.geeksforgeeks.org/dsa/maximum-and-minimum-in-an-array/
// Difficulty: Basic / Easy
// Topic: Searching, Decision Trees, Minimum Comparisons, Tournament Method

/*
Problem Statement:
Part 1 (Array Min-Max Optimization):
Find the maximum and minimum elements in an array of size N using the MINIMUM 
possible number of comparisons (strictly less than 2N - 2).

Part 2 (GFG Middle of Three Problem):
Given three distinct numbers A, B, and C. Find the number with the value in the middle 
using the MINIMUM number of comparisons (at most 3 comparisons).

Example 1 (Middle of Three):
Input: A = 978, B = 518, C = 300
Output: 518
Explanation: 518 is between 300 and 978.

Example 2 (Array Min-Max):
Input: arr = [1000, 11, 445, 1, 330, 3000]
Output: Min = 1, Max = 3000 (computed in ~3N/2 comparisons)

Constraints:
- 1 <= N <= 10^5
- 1 <= A, B, C <= 10^9
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In standard code:
//   * Developers naively write multiple `min()` / `max()` or sort the numbers.
// - In Comparison Optimization:
//   * The problem is a theoretical DECISION TREE optimization!
//   * For Middle of Three: Sorting takes 3 comparisons and memory allocation.
//     A custom decision tree determines the median in AT MOST 2 to 3 comparisons!
//   * For Array Min-Max: Pairwise grouping reduces comparisons from 2N to 1.5N.

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Middle of Three Optimal Decision Tree:
//   - Comparison 1: `if (A > B)`
//       * Branch 1 (`A > B`):
//           - Comparison 2: `if (B > C)` -> Order is A > B > C -> Middle is B.
//           - Else Comparison 3: `if (A > C)` -> Order is A > C >= B -> Middle is C.
//           - Else: Order is C >= A > B -> Middle is A.
//       * Branch 2 (`B >= A`):
//           - Comparison 2: `if (A > C)` -> Order is B >= A > C -> Middle is A.
//           - Else Comparison 3: `if (B > C)` -> Order is B > C >= A -> Middle is C.
//           - Else: Order is C >= B >= A -> Middle is B.
//   - At most 2 to 3 comparisons total. Zero arithmetic overflow risk (avoids `A + B + C - min - max`).

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------------------
    // Part 2: Middle of Three (GFG Practice Problem - Minimal comparisons)
    // -------------------------------------------------------------------------
    int middle(int A, int B, int C) {
        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Decision Tree: Avoids calculating sums (which could overflow 32-bit int).
        // Resolves median in at most 2-3 branch comparisons.
        if (A > B) {
            if (B > C) {
                return B; // A > B > C
            } else if (A > C) {
                return C; // A > C >= B
            } else {
                return A; // C >= A > B
            }
        } else {
            // Here B >= A
            if (A > C) {
                return A; // B >= A > C
            } else if (B > C) {
                return C; // B > C >= A
            } else {
                return B; // C >= B >= A
            }
        }
    }

    // -------------------------------------------------------------------------
    // Part 1: Array Min-Max in ~ 3N/2 Comparisons (Tournament / Pairwise Method)
    // -------------------------------------------------------------------------
    pair<int, int> getMinMax(const vector<int>& arr) {
        int n = arr.size();
        int minVal, maxVal;
        int i = 0;

        // If array size is odd, initialize min and max to first element
        if (n % 2 != 0) {
            minVal = maxVal = arr[0];
            i = 1;
        } else {
            // If even, compare first two elements (1 comparison)
            if (arr[0] < arr[1]) {
                minVal = arr[0];
                maxVal = arr[1];
            } else {
                minVal = arr[1];
                maxVal = arr[0];
            }
            i = 2;
        }

        // Compare elements in pairs: 3 comparisons per 2 elements!
        while (i < n - 1) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // 1st comparison: compare pair elements against each other to find local min & max
            if (arr[i] < arr[i + 1]) {
                // 2nd comparison: compare local min with global min
                if (arr[i] < minVal) minVal = arr[i];
                // 3rd comparison: compare local max with global max
                if (arr[i + 1] > maxVal) maxVal = arr[i + 1];
            } else {
                if (arr[i + 1] < minVal) minVal = arr[i + 1];
                if (arr[i] > maxVal) maxVal = arr[i];
            }
            i += 2;
        }

        return {minVal, maxVal};
    }
};

int main() {
    Solution sol;
    cout << "Middle of (978, 518, 300): " << sol.middle(978, 518, 300) << "\n";
    cout << "Middle of (40, 100, 20): " << sol.middle(40, 100, 20) << "\n\n";

    vector<int> arr = {1000, 11, 445, 1, 330, 3000};
    auto p = sol.getMinMax(arr);
    cout << "Array Min: " << p.first << ", Max: " << p.second << "\n";

    return 0;
}

/*
Complexity Analysis:
- Middle of Three:
  * Time Complexity: O(1) (at most 3 comparisons).
  * Space Complexity: O(1).
- Array Min-Max:
  * Total Comparisons: 3 * (N / 2) = 1.5 N comparisons (compared to 2N in naive scan).
  * Time Complexity: O(N).
  * Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Grouping elements into pairs cuts global comparisons by 25%.
*/
