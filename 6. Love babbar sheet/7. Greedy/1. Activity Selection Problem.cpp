/**
 * ============================================================================
 * Problem: Activity Selection Problem / N Meetings in One Room
 * Category: Greedy
 * 
 * Problem Statement:
 * There is one meeting room in a firm. There are N meetings in the form of 
 * `(start[i], end[i])` where `start[i]` is start time of meeting i and `end[i]`
 * is finish time of meeting i.
 * 
 * Find the maximum number of meetings that can be accommodated in the meeting 
 * room when only one meeting can be held in the meeting room at a particular time.
 * Note: The start time of one chosen meeting cannot be equal to or less than 
 * the end time of the previously held meeting (strict start > lastEnd, or start >= lastEnd).
 * 
 * Example 1:
 * Input:
 *   start[] = {1, 3, 0, 5, 8, 5}
 *   end[]   = {2, 4, 6, 7, 9, 9}
 * Output: 4
 * Explanation: Meetings selected: (1, 2), (3, 4), (5, 7), (8, 9).
 * 
 * Example 2:
 * Input:
 *   start[] = {10, 12, 20}
 *   end[]   = {20, 25, 30}
 * Output: 1
 * 
 * Constraints:
 * 1 <= N <= 10^5
 * 0 <= start[i] < end[i] <= 10^5
 * Must run in O(N log N) time and O(N) space.
 * ============================================================================
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * ----------------------------------------------------------------------------
 * 1. Unweighted vs Weighted Scheduling (Category 4, Problem 26):
 *    - In Weighted Job Scheduling, each job had a profit/weight, which destroyed
 *      the greedy choice property and strictly mandated Dynamic Programming + Binary Search.
 *    - Here, all activities have EQUAL weight (each meeting counts as 1).
 *    - This restores the Greedy Choice Property: maximizing the total count of activities
 *      is provably optimal by selecting the activity that frees up the room earliest!
 * 2. Why Sort by Finish Time, NOT Start Time or Duration?
 *    - Sorting by Start Time fails: Meeting (0, 100) blocks meetings (1, 2), (3, 4)...
 *    - Sorting by Shortest Duration fails: (1, 5), (4, 7), (6, 10) -> Shortest is (4, 7),
 *      picking it yields 1 meeting, whereas picking (1, 5) and (6, 10) yields 2!
 *    - Sorting by Finish Time leaves the MAXIMUM remaining free time for all future meetings.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * ----------------------------------------------------------------------------
 * Greedy by Earliest Finish Time O(N log N) Time:
 *   - Step 1: Pack meetings into a vector of structs: `{start, end, id}`.
 *   - Step 2: Sort all meetings in non-decreasing order of their finish times (`end`).
 *   - Step 3: Greedily select the first meeting (finishes earliest):
 *       `count = 1;`
 *       `lastEnd = meetings[0].end;`
 *   - Step 4: Iterate through remaining meetings:
 *       - If `meetings[i].start > lastEnd`:
 *           Compatible! Select this meeting:
 *           `count++;`
 *           `lastEnd = meetings[i].end;`
 *   - Return `count`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting {
    int start;
    int end;
    int id;
};

class Solution {
public:
    /**
     * Finds the maximum number of meetings that can be held in one room.
     * @param start Vector of start times.
     * @param end Vector of end times.
     * @param n Total number of meetings.
     * @return Maximum number of compatible meetings.
     */
    int maxMeetings(int start[], int end[], int n) {
        if (n == 0) return 0;

        vector<Meeting> meetings(n);
        for (int i = 0; i < n; ++i) {
            meetings[i] = {start[i], end[i], i + 1};
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Greedy Choice Property: Sorting by earliest finish time guarantees that
        // the meeting room is freed as quickly as possible, leaving maximal remaining time.
        sort(meetings.begin(), meetings.end(), [](const Meeting& a, const Meeting& b) {
            if (a.end == b.end) return a.id < b.id;
            return a.end < b.end;
        });

        int count = 1;
        int lastEndTime = meetings[0].end;

        for (int i = 1; i < n; ++i) {
            if (meetings[i].start > lastEndTime) {
                count++;
                lastEndTime = meetings[i].end;
            }
        }

        return count;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1:
    // start[] = {1, 3, 0, 5, 8, 5}
    // end[]   = {2, 4, 6, 7, 9, 9}
    int start1[] = {1, 3, 0, 5, 8, 5};
    int end1[]   = {2, 4, 6, 7, 9, 9};
    int n1 = sizeof(start1) / sizeof(start1[0]);

    cout << "Test 1: Max Meetings = " << solver.maxMeetings(start1, end1, n1) 
         << " (Expected: 4)\n";

    // Test Case 2:
    int start2[] = {10, 12, 20};
    int end2[]   = {20, 25, 30};
    int n2 = sizeof(start2) / sizeof(start2[0]);

    cout << "Test 2: Max Meetings = " << solver.maxMeetings(start2, end2, n2) 
         << " (Expected: 1)\n";

    return 0;
}

/**
 * COMPLEXITY ANALYSIS:
 * ----------------------------------------------------------------------------
 * Time Complexity:
 *   - Sorting N meetings by end time: O(N log N).
 *   - Linear scan through sorted meetings: O(N).
 *   - Total Time: O(N log N).
 * 
 * Space Complexity:
 *   - Auxiliary Space: O(N) to store Meeting structs.
 * 
 * KEY TAKEAWAYS:
 * ----------------------------------------------------------------------------
 * 1. Sorting by finish time is the optimal greedy strategy for unweighted interval scheduling.
 * 2. If meetings had arbitrary profits, greedy fails and DP + Binary Search is needed.
 */
