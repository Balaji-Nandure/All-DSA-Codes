/*
Problem: K-th Element of Two Sorted Arrays

GFG: https://www.geeksforgeeks.org/k-th-element-two-sorted-arrays/
LeetCode (Median of Two Sorted Arrays): https://leetcode.com/problems/median-of-two-sorted-arrays/

Description: Given two sorted arrays a[] and b[] and an integer k, return the k-th element in the combined sorted array.

Examples:

Input: a[] = [2, 3, 6, 7, 9], b[] = [1, 4, 8, 10], k = 5
Output: 6
Explanation: The final combined sorted array would be [1, 2, 3, 4, 6, 7, 8, 9, 10]. The 5th element of this array is 6.
Input: a[] = [1, 4, 8, 10, 12], b[] = [5, 7, 11, 15, 17], k = 6
Output: 10
Explanation: Combined sorted array is [1, 4, 5, 7, 8, 10, 11, 12, 15, 17]. The 6th element of this array is 10.

Constraints:
1 ≤ a.size(), b.size() ≤ 106
1 ≤ k ≤ a.size() + b.size()
0 ≤ a[i], b[i] ≤ 108

Striver Intuition:

We need the k-th smallest element from two sorted arrays.

Brute force:
- Merge both arrays and return k-th element
- TC = O(n + m), SC = O(n + m)

Better:
- Use two pointers and stop at k
- TC = O(k), SC = O(1)

Optimal (Important):
This is same as Median of Two Sorted Arrays problem.

We partition both arrays such that:
Left part contains exactly k elements.

Let:
cut1 = elements taken from array a
cut2 = elements taken from array b

cut1 + cut2 = k

Now we check if partition is correct:
l1 = a[cut1 - 1]
l2 = b[cut2 - 1]
r1 = a[cut1]
r2 = b[cut2]

Correct partition if:
l1 <= r2 AND l2 <= r1

Then answer = max(l1, l2)

If l1 > r2 → move left in array a
Else → move right in array a

We binary search on the smaller array.

Why low = max(0, k - m)?
Because we must take at least (k - m) elements from array a
if array b cannot contribute more than m elements.

Why high = min(k, n)?
Because we cannot take more than n elements from array a.

Pattern:
If problem has:
- Two sorted arrays
- Median
- K-th element
→ Use Binary Search Partition

Time Complexity: O(log(min(n, m)))
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int kthElement(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();
        int m = b.size();

        // Always binary search on smaller array
        if (n > m) return kthElement(b, a, k);

        // Calculate search range
        // low = max(0, k - m): We must take at least (k - m) elements from array a
        // high = min(k, n): We cannot take more than k elements from array a
        int low = max(0, k - m);
        int high = min(k, n);

        while (low <= high) {
            // cut1: elements taken from array a
            // cut2: elements taken from array b (such that cut1 + cut2 = k)
            int cut1 = (low + high) / 2;
            int cut2 = k - cut1;

            // Handle boundary cases with INT_MIN and INT_MAX
            int l1 = (cut1 == 0) ? INT_MIN : a[cut1 - 1];  // last element in left part of a
            int l2 = (cut2 == 0) ? INT_MIN : b[cut2 - 1];  // last element in left part of b
            int r1 = (cut1 == n) ? INT_MAX : a[cut1];      // first element in right part of a
            int r2 = (cut2 == m) ? INT_MAX : b[cut2];      // first element in right part of b
 
            // Check if partition is correct
            if (l1 <= r2 && l2 <= r1) {
                // Correct partition found: answer is max of left parts
                return max(l1, l2);
            }
            else if (l1 > r2) {
                // l1 is too big, need to take fewer elements from array a
                high = cut1 - 1;
            }
            else {
                // l2 is too big, need to take more elements from array a
                low = cut1 + 1;
            }
        }

        return -1;
    }
};

/*
Final Summary (Interview Revision):

1. We are finding k-th element → think partition.
2. Partition such that left side has k elements.
3. Check partition using:
        l1 <= r2 && l2 <= r1
4. Answer = max(l1, l2)
5. Always binary search on smaller array.
6. Search range:
        low = max(0, k - m)
        high = min(k, n)

Memory Trick:
Two sorted arrays + Kth/Median → Binary Search Partition
*/
