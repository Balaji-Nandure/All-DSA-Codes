// Problem: Allocate Minimum Number of Pages (Book Allocation Problem)
// Link (GFG): https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1
// Article: https://www.geeksforgeeks.org/dsa/allocate-minimum-number-pages/
// Difficulty: Hard
// Topic: Searching, Binary Search on Answer, Capacity Allocation, Minimize the Maximum

/*
Problem Statement:
You have n books, each with `arr[i]` pages. There are `m` students.
Books must be distributed among `m` students such that:
  1. Each book is allocated to exactly one student.
  2. Each student is assigned a CONTIGUOUS sequence of books.
  3. Every student gets at least one book.
The task is to allocate books such that the MAXIMUM number of pages assigned 
to any student is MINIMIZED.
If allocation is impossible (e.g. `m > n`), return -1.

Example 1:
Input: n = 4, arr = [12, 34, 67, 90], m = 2
Output: 113
Explanation: Allocation: [12, 34, 67] (sum = 113) to Student 1, and [90] (sum = 90) to Student 2.
Maximum pages allocated to a student = max(113, 90) = 113.

Example 2:
Input: n = 3, arr = [15, 17, 20], m = 2
Output: 32
Explanation: [15, 17] (32) and [20] (20) -> max is 32.

Constraints:
- 1 <= n <= 10^5
- 1 <= m <= 10^5
- 1 <= arr[i] <= 10^6
*/

// =============================================================================
// HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
// =============================================================================
// - In Problem 23 (Aggressive Cows):
//   * The goal was to MAXIMIZE the MINIMUM separation between cows.
// - In Problem 24 (Book Allocation):
//   * The goal is the DUAL: MINIMIZE the MAXIMUM load assigned to any student.
//   * Books cannot be re-ordered; they must be assigned in contiguous sequence.
//   * Search space bounds:
//       `low = max(arr)` (at minimum, the student getting the thickest book must read it).
//       `high = sum(arr)` (at maximum, a single student reads all books).

// =============================================================================
// APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
// =============================================================================
// Binary Search on Answer + Greedy Capacity Allocation (Optimal & Chosen):
//   - Guard: If `m > n`, return -1 (cannot give at least 1 book to each student).
//   - Range: `low = max_element(arr)`, `high = sum(arr)`.
//   - Predicate `isPossible(maxPages)`:
//       * Maintain `studentCount = 1`, `allocatedPages = 0`.
//       * For each book `pages`:
//           - If `allocatedPages + pages <= maxPages`:
//               Add to current student: `allocatedPages += pages`.
//           - Else:
//               Assign to NEXT student: `studentCount++`, `allocatedPages = pages`.
//               If `studentCount > m`: Return `false`!
//       * Return `true`.
//   - Binary Search:
//       * If `isPossible(mid)`: Valid allocation found! Record `ans = mid`, 
//         and greedily try to decrease the maximum cap: `high = mid - 1`.
//       * Else: Cap is too restrictive, increase: `low = mid + 1`.
//   - Complexity: O(N * log(sum(arr) - max(arr))) time, O(1) space.

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function: Checks if books can be allocated to at most m students with each student reading <= maxPages
    bool isAllocationFeasible(const vector<int>& arr, int n, int m, long long maxPages) {
        int studentsRequired = 1;
        long long currentPages = 0;

        for (int i = 0; i < n; ++i) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If adding the current book exceeds the capacity limit `maxPages`,
            // we must allocate this book to a new student.
            if (currentPages + arr[i] <= maxPages) {
                currentPages += arr[i];
            } else {
                studentsRequired++;
                currentPages = arr[i];

                // If number of students exceeds m, allocation with this maxPages cap is infeasible
                if (studentsRequired > m) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    long long findPages(int n, vector<int>& arr, int m) {
        // Impossible to allocate at least 1 book to each student if students > books
        if (m > n) return -1;

        long long low = *max_element(arr.begin(), arr.end());
        long long high = 0;
        for (int p : arr) high += p;

        long long ans = -1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If allocation is possible with max pages <= mid, record candidate
            // and search left (high = mid - 1) to find a smaller feasible maximum!
            if (isAllocationFeasible(arr, n, m, mid)) {
                ans = mid;
                high = mid - 1; // Try to minimize the maximum load further
            } else {
                low = mid + 1;  // Load cap was too small, increase capacity
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> arr1 = {12, 34, 67, 90};
    int m1 = 2;
    cout << "Minimum maximum pages (arr1): " << sol.findPages(arr1.size(), arr1, m1) << "\n";

    vector<int> arr2 = {15, 17, 20};
    int m2 = 2;
    cout << "Minimum maximum pages (arr2): " << sol.findPages(arr2.size(), arr2, m2) << "\n";

    return 0;
}

/*
Complexity Analysis:
- Time Complexity: O(N * log(sum - max)).
  * The search range is [max(arr), sum(arr)].
  * Binary search executes at most ~50 times.
  * In each step, the array is linearly traversed in O(N).
  * For N = 10^5, finishes in under 15 milliseconds.
- Space Complexity: O(1) auxiliary space.

Key Takeaways:
- Book Allocation is the universal template for Painter's Partition, Ship Packages Within D Days,
  and Split Array Largest Sum.
*/
