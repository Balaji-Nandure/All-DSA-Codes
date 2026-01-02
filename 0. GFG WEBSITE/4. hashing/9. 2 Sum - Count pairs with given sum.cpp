/*
Problem:
2 Sum – Count Pairs with Given Sum

Given an integer array arr[] and an integer target,
count the number of pairs (i, j) such that:
- i < j
- arr[i] + arr[j] == target

Examples:
Input  : arr = [1, 5, 7, -1], target = 6
Output : 2
Explanation:
Pairs are (1,5) and (7,-1)

Input  : arr = [1, 1, 1, 1], target = 2
Output : 6
Explanation:
All possible pairs of (1,1)

Input  : arr = [10, 12, 10, 15, -1], target = 9
Output : 1


Approach (Expected / Optimal – Hashing):
1. Use an unordered_map to store frequency of elements seen so far.
2. For each element x in the array:
   - The required value to form the sum is (target - x).
   - If (target - x) already exists in the map,
     then it can form valid pairs with current element.
3. Add freq[target - x] to the answer.
4. Increment frequency of current element x in the map.
5. Continue till the end.

Why this works:
- Hashing allows O(1) average lookup for complement.
- Each valid pair is counted exactly once because we only
  pair current element with previously seen elements.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/count-pairs-with-given-sum/

LeetCode:
https://leetcode.com/problems/two-sum/
(Note: LeetCode asks to return indices, but core logic is identical)
*/

int countPairsWithSum(vector<int>& arr, int target) {
    unordered_map<int, int> freq;
    int count = 0;

    for (int x : arr) {
        int need = target - x;

        // If complement exists, it forms valid pairs
        if (freq.count(need)) {
            count += freq[need];
        }

        // Mark current element as seen
        freq[x]++;
    }

    return count;
}
