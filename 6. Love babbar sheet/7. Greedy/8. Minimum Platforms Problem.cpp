/**
 * ============================================================================
 * Problem: Minimum Platforms (Maximum Concurrency / Overlapping Intervals)
 * Category: Greedy / Two Pointers
 * 
 * Problem Statement:
 * Given arrival and departure times of all trains that reach a railway station,
 * find the minimum number of platforms required for the railway station so that 
 * no train is kept waiting.
 * 
 * At any given time, the same platform cannot be used for both departure of a 
 * train and arrival of another train (i.e. if a train arrives at the exact time
 * another train departs, an additional platform is required).
 * 
 * Example:
 * Input:
 *   N = 6
 *   arr[] = {0900, 0940, 0950, 1100, 1500, 1800}
 *   dep[] = {0910, 1200, 1120, 1130, 1900, 2000}
 * Output: 3
 * Explanation:
 *   Between 11:00 and 11:20, there are 3 trains simultaneously at the station:
 *   Train 2 (arrived 0940, departs 1200),
 *   Train 3 (arrived 0950, departs 1120),
 *   Train 4 (arrived 1100, departs 1130).
 *   Hence, 3 platforms are required.
 * 
 * Constraints:
 * 1 <= N <= 5 * 10^4
 * 0000 <= arr[i] <= dep[i] <= 2359
 * Must run in O(N log N) time and O(1) auxiliary space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Resource Consumption (Max Peak Concurrent Demand):
 *    - In Problem 1 & 7, we MAXIMIZED the number of events accommodated in fixed rooms.
 *    - Here, ALL trains MUST be accommodated; we are MINIMIZING the capacity
 *      (number of platforms) to absorb the PEAK concurrent overlap.
 * 2. Independence of Arrival and Departure Pairing:
 *    - In interval scheduling, preserving the pairing between a train's start and end
 *      was mandatory.
 *    - For computing peak concurrent presence, identity DOES NOT MATTER!
 *      Every arrival increments active occupancy (+1), and every departure decrements (-1).
 *    - Sorting arrival and departure arrays INDEPENDENTLY allows an elegant O(N) sweep.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Timeline Two-Pointer Sweep O(N log N) Time, O(1) Space:
 *   - Step 1: Sort `arr[]` and `dep[]` independently in ascending order.
 *   - Step 2: Use two pointers: `i = 0` (arrivals), `j = 0` (departures).
 *   - Step 3: Maintain `currPlatforms = 0` and `maxPlatforms = 0`.
 *   - Step 4: While `i < n && j < n`:
 *       - If `arr[i] <= dep[j]`:
 *           A train has arrived before the earliest parked train departed:
 *           `currPlatforms++;`
 *           `maxPlatforms = max(maxPlatforms, currPlatforms);`
 *           `i++;`
 *       - Else:
 *           A train has departed, freeing up a platform:
 *           `currPlatforms--;`
 *           `j++;`
 *   - Return `maxPlatforms`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Computes minimum number of platforms required using two-pointer sweep.
     * @param arr Array of arrival times.
     * @param dep Array of departure times.
     * @param n Number of trains.
     * @return Minimum platforms needed.
     */
    int findPlatform(int arr[], int dep[], int n) {
        if (n <= 1) return n;

        // Step 1: Sort arrival and departure arrays independently
        sort(arr, arr + n);
        sort(dep, dep + n);

        int i = 0; // Pointer for arrivals
        int j = 0; // Pointer for departures
        int currentPlatforms = 0;
        int maxPlatforms = 0;

        // Step 2: Simulate chronological timeline
        while (i < n && j < n) {
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            // If arrival <= departure, a new train enters the station before any parked
            // train can leave, necessitating an additional platform (+1).
            if (arr[i] <= dep[j]) {
                currentPlatforms++;
                maxPlatforms = max(maxPlatforms, currentPlatforms);
                i++;
            } else {
                currentPlatforms--; // Train departed, freeing a platform
                j++;
            }
        }

        return maxPlatforms;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case:
    // arr[] = {0900, 0940, 0950, 1100, 1500, 1800}
    // dep[] = {0910, 1200, 1120, 1130, 1900, 2000}
    int arr[] = {900, 940, 950, 1100, 1500, 1800};
    int dep[] = {910, 1200, 1120, 1130, 1900, 2000};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Minimum Platforms Required = " << solver.findPlatform(arr, dep, n) 
         << " (Expected: 3)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting both arrays independently: O(N log N).
 *   - Two-pointer linear sweep: O(2N) = O(N).
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(1) in-place without auxiliary data structures.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Independent sorting of endpoints is the standard pattern for finding
 *    maximum concurrent interval overlap.
 * 2. When `arr[i] == dep[j]`, the problem states that a new platform is required,
 *    so the comparison must be `arr[i] <= dep[j]`.
 */
