/*
Problem:
K-th Distinct (Non-Repeating) Element in an Array

Given an integer array arr[] and an integer k,
find the k-th distinct (non-repeating) element in the array.

Definition:
- A distinct (non-repeating) element appears exactly once in the array.
- The order of appearance in the original array matters.

Return:
- The value of the k-th distinct element (1-based index).
- If there are fewer than k distinct elements, return -1.

Examples:
Input  : arr = [1, 2, 1, 3, 4, 2], k = 2
Output : 3
Explanation:
Distinct elements in order: [3, 4]
2nd distinct element is 3

Input  : arr = [1, 2, 3, 4], k = 3
Output : 3

Input  : arr = [1, 1, 1], k = 1
Output : -1


-----------------------------------
Approach (Expected / Optimal – Hashing + Order Preservation):
-----------------------------------
1. Use a hash map to count frequency of each element.
2. Traverse the array again in original order:
   - For each element, if its frequency is exactly 1,
     decrement k.
   - When k becomes 0, return the current element.
3. If traversal ends and k > 0, return -1.

Why this works:
- Hash map identifies distinct (frequency = 1) elements.
- Second traversal preserves original order.
- Each element is processed at most twice.

Time Complexity:
O(n)

Space Complexity:
O(n)


GeeksforGeeks:
https://www.geeksforgeeks.org/kth-distinct-or-non-repeating-element-in-an-array/

LeetCode:
No direct equivalent problem.
(Related to frequency counting and order preservation)
*/

int kthDistinctElement(vector<int>& arr, int k) {
    unordered_map<int, int> freq;

    // Step 1: Count frequencies
    for (int x : arr) {
        freq[x]++;
    }

    // Step 2: Traverse in original order to find k-th distinct
    for (int x : arr) {
        if (freq[x] == 1) {
            k--;
            if (k == 0) {
                return x;
            }
        }
    }

    return -1;
}
