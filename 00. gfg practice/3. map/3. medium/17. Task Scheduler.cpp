/*
    Problem Name: Task Scheduler
    Difficulty: Medium
    Platform: GeeksforGeeks / LeetCode

    Problem Statement:
    Given a character array tasks of size N, representing the tasks a CPU needs to do. 
    CPU has a cooldown period for each task. CPU can repeat a task only after at least K units of time.
    Return the least number of units of times that the CPU will take to finish all the given tasks.

    Expected Complexities:
    Time Complexity: O(N) to count frequencies of tasks. Finding the max frequency and counting tasks with max frequency takes O(26) = O(1).
    Space Complexity: O(1) as we only use a fixed size array of 26 integers to store task frequencies.

    Love Babbar Style Approach:
    1. The bottleneck in scheduling is always the task(s) with the highest frequency. We must schedule them first and separate them by `K` units of time (or idles).
    2. Let the maximum frequency of any task be `max_freq`.
    3. We will have `(max_freq - 1)` chunks/gaps between these most frequent tasks. Each chunk needs to be of size `K` to satisfy the cooldown.
    4. So, the base time taken is `(max_freq - 1) * (K + 1)`.
    5. At the very end, we also need to append all tasks that share this exact same `max_freq`. Let the count of such tasks be `count_max_freq`.
    6. The formula for the required time considering idles is:
       `time_needed = (max_freq - 1) * (K + 1) + count_max_freq`
    7. Is it possible that we have so many other tasks that they fill all the gaps perfectly and we don't need any idle time at all? YES!
       In that case, the total time required is just `N` (the length of the tasks array).
    8. So, the final answer is simply `max(N, time_needed)`.

    Dry Run:
    Input: N = 6, K = 2, task = {'A', 'A', 'A', 'B', 'B', 'B'}
    - Frequencies: 'A' = 3, 'B' = 3.
    - max_freq = 3.
    - count_max_freq = 2 (both 'A' and 'B' appear 3 times).
    - time_needed = (3 - 1) * (2 + 1) + 2 = 2 * 3 + 2 = 8.
    - N = 6.
    - Result = max(6, 8) = 8.
    Matches Expected Output!
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int leastInterval(int N, int K, vector<char> &tasks) {

        vector<int> freq(26, 0);

        for (char ch : tasks)
            freq[ch - 'A']++;

        int mx = 0;

        for (int x : freq)
            mx = max(mx, x);

        int cnt = 0;

        for (int x : freq)
            if (x == mx)
                cnt++;

        return max(N, (mx - 1) * (K + 1) + cnt);
    }
};

int main() {
    int t;
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> t) {
        while (t--) {
            int n, k;
            cin >> n >> k;
            
            vector<char> tasks(n);
            for (int i = 0; i < n; i++) {
                cin >> tasks[i];
            }
            
            Solution ob;
            cout << ob.leastInterval(n, k, tasks) << "\n";
        }
    }
    return 0;
}
