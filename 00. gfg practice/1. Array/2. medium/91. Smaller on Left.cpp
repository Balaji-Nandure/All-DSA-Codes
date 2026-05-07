/*
Problem: Smaller on Left

GFG: https://www.geeksforgeeks.org/problems/smaller-on-left20360700/1

Description:
Given an array arr[] of n positive integers, the task is to find the greatest element on the left of every element which is strictly smaller than itself. If this element does not exist for an index, print "-1".

Examples:

Input: n = 5, arr[] = [2, 3, 4, 5, 1]
Output: -1 2 3 4 -1
Explanation:
Greatest element on the left of 3 smaller than itself is 2, for 4 it is 3 and for 5 it is 1. Since 2 is the first element and no element on its left is present, so it's greatest smaller element will be -1 and for 1 no element smaller than itself is present on its left, so it's greatest smaller element is -1.

Input: n = 3, arr[] = [1, 2, 3] 
Output: -1 1 2 
Constraints:
1 ≤ n ≤ 10^6
1 ≤ arr[i] ≤ 10^8

Approach (Ordered Set):
Since we need to greatest element on left that is strictly smaller than current element, we can use an ordered set to maintain all previous elements in sorted order.

For each element x:
- Use lower_bound(x) to find the first element >= x
- The element just before this (if any) is the greatest element < x
- If no such element exists, return -1

Algorithm:
1. Maintain ordered set of previous elements
2. For each current element x:
   - Find it = st.lower_bound(x)
   - If it == st.begin(): no smaller element → -1
   - Else: --it gives greatest element < x
3. Insert x into set

Why it works:
- Ordered set maintains elements in sorted order
- lower_bound gives O(log n) search
- Each element processed exactly once

Time Complexity: O(n log n)
Space Complexity: O(n)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> leftSmaller(int n, vector<int>& arr) {
        
        set<int> st;
        
        vector<int> ans;
        
        for (int x : arr) {
            
            auto it = st.lower_bound(x);
            
            // No smaller element
            if (it == st.begin()) {
                ans.push_back(-1);
            }
            else {
                
                --it;
                
                ans.push_back(*it);
            }
            
            st.insert(x);
        }
        
        return ans;
    }
};

/*
-----------------------------------------------------

🧠 INTERVIEW TAKEAWAY

Whenever question asks:
    "largest/smallest element satisfying condition"

Think immediately:
    Ordered Set / BST

-----------------------------------------------------

Useful operations:
lower_bound(x)
upper_bound(x)

-----------------------------------------------------

STACK:
    nearest queries

SET/BST:
    best-value queries

-----------------------------------------------------

🔥 IMPORTANT OBSERVATION

We need:
    greatest smaller element on left

NOT nearest smaller.

-----------------------------------------------------

PATTERN:
Ordered Set Query

-----------------------------------------------------

GFG LINK:
https://www.geeksforgeeks.org/problems/smaller-on-left20360700/1

LEETCODE:
https://leetcode.com/problems/next-greater-element-i/

-----------------------------------------------------

TIME COMPLEXITY:
O(n log n)

SPACE COMPLEXITY:
O(n)

-----------------------------------------------------
*/
