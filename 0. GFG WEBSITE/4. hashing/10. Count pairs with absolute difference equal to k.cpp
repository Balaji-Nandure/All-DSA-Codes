/*
Problem:
Count Pairs with Absolute Difference Equal to k

Given an integer array arr[] and an integer k,
count the number of pairs (i, j) such that:
- i < j
- |arr[i] - arr[j]| == k

Examples:
Input  : arr = [1, 5, 3, 4, 2], k = 2
Output : 3
Explanation:
Pairs are (1,3), (5,3), (4,2)

Input  : arr = [1, 2, 2, 1], k = 1
Output : 4
Explanation:
Pairs are (1,2) four times considering indices

Input  : arr = [3, 3, 3], k = 0
Output : 3
Explanation:
All possible pairs of equal elements


Approach (Expected / Optimal – Hashing):
1. Use an unordered_map to store frequency of elements seen so far.
2. For each element x:
   - For k > 0:
       Valid pairs are formed with (x - k) and (x + k)
   - For k == 0:
       Valid pairs are formed only with previously seen x
3. Add corresponding frequencies to the answer.
4. Increment frequency of x.

Why this works:
- Absolute difference condition breaks into two linear cases.
- Hashing allows O(1) average-time lookup.
- Counting is done only with previously seen elements,
  so each pair is counted exactly once.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/count-pairs-with-given-difference/

LeetCode:
No direct equivalent problem.
(Related to Two Sum / difference-based hashing problems)
*/

int countPairsWithAbsDiffK(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int x : arr) {
        if (k == 0) {
            // Only equal elements form valid pairs
            if (freq.count(x)) {
                count += freq[x];
            }
        } else {
            if (freq.count(x - k)) {
                count += freq[x - k];
            }
            if (freq.count(x + k)) {
                count += freq[x + k];
            }
        }

        // Mark current element as seen
        freq[x]++;
    }

    return count;
}
