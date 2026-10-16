#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <climits>

using namespace std;

/**
 * Problem: Least Recently Used (LRU) Page Replacement algorithm
 * 
 * Given a sequence of page references `pages[]` of length N and frame capacity C,
 * find the total number of page faults using the LRU replacement algorithm.
 * 
 * HOW THIS PROBLEM DIFFERS FROM PREVIOUSLY SOLVED PROBLEMS:
 * - This is an online caching and eviction simulation problem.
 * - Unlike static sorting greedy problems, decisions occur dynamically at each step t based on 
 *   temporal locality (when each item in cache was last accessed).
 * 
 * APPROACH & WHY THIS APPROACH ONLY (NOT OTHERS):
 * - Optimal Cache Simulation:
 *   Maintain a set/hash table of current memory frames for O(1) page presence lookup.
 *   Track the most recent reference timestamp for each resident page in a hash map: page -> last_referenced_time.
 *   
 *   For each page reference at time t:
 *   1. Hit (page already in memory):
 *      Update page's timestamp to t. Page fault does NOT occur.
 *   2. Miss (page NOT in memory):
 *      Page fault occurs!
 *      - If memory has free capacity (< C):
 *        Add page to memory and record timestamp.
 *      - If memory is full (size == C):
 *        Find the resident page with the minimum last_referenced_time (the Least Recently Used page).
 *        Evict that page from memory.
 *        Insert the new page into memory with timestamp t.
 */

class Solution {
public:
    int pageFaults(int N, int C, int pages[]) {
        unordered_set<int> memory;
        unordered_map<int, int> last_used_time; // page -> timestamp
        int faults = 0;

        for (int t = 0; t < N; t++) {
            int page = pages[t];

            // Check if page already exists in memory
            if (memory.find(page) == memory.end()) {
                // Page Fault occurred!
                faults++;

                // If memory is full, we must evict the Least Recently Used page
                if ((int)memory.size() == C) {
                    int lru_page = -1;
                    int min_time = INT_MAX;

                    // *** CRUCIAL LINE / WHAT MAKES THE DIFFERENCE ***
                    // Find the resident page whose last access timestamp is the oldest
                    for (int resident : memory) {
                        if (last_used_time[resident] < min_time) {
                            min_time = last_used_time[resident];
                            lru_page = resident;
                        }
                    }

                    // Evict LRU page
                    memory.erase(lru_page);
                }

                // Insert the incoming page
                memory.insert(page);
            }

            // *** CRUCIAL LINE: Update the recency of the accessed page ***
            last_used_time[page] = t;
        }

        return faults;
    }
};

int main() {
    Solution sol;
    int pages[] = {5, 0, 1, 3, 2, 4, 1, 0, 5};
    int N = sizeof(pages) / sizeof(pages[0]);
    int C = 4;

    cout << "Total Page Faults: " << sol.pageFaults(N, C, pages) << "\n";
    // Expected output: 8

    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * - Time Complexity: O(N * C) where C is the frame capacity. For each page miss when full,
 *   we inspect C resident pages to find min timestamp. With doubly linked list + hash map,
 *   this can be reduced to strictly O(N). Since C is typically small (<= 100), O(N * C) is fast and clean.
 * - Space Complexity: O(C) for resident set and hash map storing at most C active pages.
 */
