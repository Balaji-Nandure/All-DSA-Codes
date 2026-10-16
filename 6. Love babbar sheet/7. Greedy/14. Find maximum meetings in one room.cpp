#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Problem: Find maximum meetings in one room (Return meeting numbers)
 * 
 * Given start times S[] and finish times F[] of N meetings, find the maximum number 
 * of meetings that can be accommodated in a single meeting room.
 * Output the 1-based original indices of the selected meetings (sorted in ascending order).
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - In "1. Activity Selection Problem", we only needed to return the integer COUNT of maximum non-overlapping intervals.
 * - Here, we must track original 1-based indices, handle tie-breaking on finish times (favoring smaller original index),
 *   and return the lexicographically sorted list of meeting indices selected.
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Greedy by earliest finish time:
 *   Finishing as early as possible frees the single room at the earliest moment, leaving maximum 
 *   remaining room availability for subsequent meetings.
 * - Why not sort by shortest duration? A short meeting can be in the dead center of two long meetings, 
 *   blocking both.
 * - Why not sort by start time? A meeting starting early could run until the end of the day, blocking all others.
 * - Earliest finish time is mathematically optimal (Matroid greedy choice property).
 */

struct Meeting {
    int start;
    int end;
    int id; // 1-based original index
};

class Solution {
public:
    static bool compareMeetings(const Meeting& a, const Meeting& b) {
        // Tie-breaker: If end times are equal, pick meeting with smaller original index
        if (a.end != b.end) {
            return a.end < b.end;
        }
        return a.id < b.id;
    }

    vector<int> maxMeetings(int N, vector<int>& start, vector<int>& end) {
        vector<Meeting> meetings(N);
        for (int i = 0; i < N; i++) {
            meetings[i] = {start[i], end[i], i + 1};
        }

        // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
        // Sort meetings primarily by finish time ascending, secondary by original index ascending.
        sort(meetings.begin(), meetings.end(), compareMeetings);

        vector<int> selectedMeetings;
        int lastEndTime = -1;

        for (int i = 0; i < N; i++) {
            // Strict inequality: meetings cannot overlap at endpoints in standard problem specification
            // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
            if (meetings[i].start > lastEndTime) {
                selectedMeetings.push_back(meetings[i].id);
                lastEndTime = meetings[i].end;
            }
        }

        // Problem requires returning indices in sorted order
        sort(selectedMeetings.begin(), selectedMeetings.end());
        return selectedMeetings;
    }
};

int main() {
    Solution sol;
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end   = {2, 4, 6, 7, 9, 9};
    int N = start.size();

    vector<int> ans = sol.maxMeetings(N, start, end);
    cout << "Selected meeting indices: ";
    for (int id : ans) {
        cout << id << " ";
    }
    cout << "\n";
    // Expected output: 1 2 4 5

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N log N) dominated by sorting the meetings and sorting the final selected indices.
 * - Space Complexity: O(N) to store the Meeting structs with their original IDs.
 */
