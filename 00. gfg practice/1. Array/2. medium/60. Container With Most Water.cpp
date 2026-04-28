/*
PROBLEM: Container With Most Water
------------------------------------------------
Given:
- arr[] of non-negative integers where arr[i] = height of vertical line
- Find maximum water that can be contained between any two lines + x-axis

Return:
- Maximum area (width * min(height1, height2))

Example:
arr = [1,5,4,3] -> Output: 6
arr = [3,1,2,4,5] -> Output: 12
arr = [2,1,8,6,4,6,5,5] -> Output: 25

Constraints:
1 <= arr.size() <= 10^5
0 <= arr[i] <= 10^4

------------------------------------------------
INTUITION / APPROACH:
------------------------------------------------
Pattern: Two Pointers (Classic Container Problem)

Key Idea:
- Area = (j - i) * min(arr[i], arr[j])
- To maximize area, we need both width and height
- Start with maximum width (i=0, j=n-1) and move inward
- Move the pointer with smaller height because:
  - Moving larger height pointer can only decrease or keep same area
  - Moving smaller height pointer might find larger height to compensate width loss

Algorithm:
1. left = 0, right = n-1, maxArea = 0
2. While left < right:
   - Calculate current area
   - Update maxArea
   - Move pointer with smaller height
3. Return maxArea

Why this works:
- Any pair between current pointers will have smaller width
- To beat current area, we need larger height
- Only possible if we move the smaller height pointer

------------------------------------------------
TIME COMPLEXITY:
O(n) - single pass with two pointers

SPACE COMPLEXITY:
O(1) - constant extra space

------------------------------------------------
GFG LINK:
https://www.geeksforgeeks.org/problems/container-with-most-water/

Related:
- Two Sum, Trapping Rain Water
- Other two-pointer problems

------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // ---------------- TWO POINTER APPROACH ----------------
    // TC: O(n)  SC: O(1)
    int maxWater(vector<int> &arr) {
        int n = arr.size();
        
        // Edge case: single line cannot hold water
        if(n <= 1) return 0;
        
        int left = 0, right = n - 1;
        int maxArea = 0;
        
        while(left < right) {
            // Current width and height
            int width = right - left;
            int height = min(arr[left], arr[right]);
            
            // Current area
            int currentArea = width * height;
            maxArea = max(maxArea, currentArea);
            
            // Move pointer with smaller height
            if(arr[left] < arr[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;
    }
};

/*
ALGORITHM SUMMARY:
--------------------------------
1. Two pointers: left=0, right=n-1
2. Area = (right-left) * min(arr[left], arr[right])
3. Update maxArea
4. Move pointer with smaller height
5. Repeat until left >= right

Key Insights:
- Maximum width initially, then reduce width for potential height gain
- Moving larger height pointer is never optimal
- Greedy approach works due to monotonic width reduction

Interview Tips:
- Explain why we move smaller pointer
- Compare with brute force O(n^2) approach
- Mention similarity to trapping rain water problem

------------------------------------------------
TEST CASES:
--------------------------------
1. arr = [1,5,4,3] -> 6
2. arr = [3,1,2,4,5] -> 12
3. arr = [2,1,8,6,4,6,5,5] -> 25
4. arr = [1,1] -> 1
5. arr = [1] -> 0
6. arr = [4,3,2,1,4] -> 16
7. arr = [1,2,1] -> 2

------------------------------------------------
*/
