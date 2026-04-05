/*
PROBLEM: Longest subarray with Atmost two distinct integers

Given an array of positive integers, find the length of the longest
subarray that contains at most two distinct integers.

Examples:
arr[] = [2, 1, 2]
Output: 3
→ Entire array [2, 1, 2] has 2 distinct (1, 2)

arr[] = [3, 1, 2, 2, 2, 2]
Output: 5
→ Subarray [1, 2, 2, 2, 2] has 2 distinct (1, 2), length = 5

--------------------------------------------------

INTUITION / APPROACH:

This is a SLIDING WINDOW + HASHMAP problem.

Key insight: We maintain a window [left, right] with at most 2 distinct values.
- Expand right to include new elements
- When distinct count > 2, shrink from left
- Track max window size

Algorithm:
1. Use hashmap to count frequencies of elements in current window
2. Expand right pointer, add arr[right] to map
3. If map size > 2, move left pointer and remove elements until size <= 2
4. Update max length = right - left + 1

Why it works:
- Greedy approach: always expand as much as possible (right)
- Contract only when necessary (distinct count exceeds 2)
- This guarantees we find the longest valid subarray

--------------------------------------------------

PATTERN:
"Longest/shortest subarray with constraint" → Sliding Window

--------------------------------------------------

TIME COMPLEXITY:
O(N) - each element visited at most twice (once by right, once by left)

SPACE COMPLEXITY:
O(1) - at most 3 keys in hashmap (2 distinct + 1 being removed)

--------------------------------------------------

GFG:
https://practice.geeksforgeeks.org/problems/longest-subarray-with-atmost-two-distinct-integers/

LeetCode similar:
https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

--------------------------------------------------
*/

class Solution {
  public:
    int longestSubarray(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> cnt;  // element -> frequency
        int left = 0, maxLen = 0;
        
        for(int right = 0; right < n; right++) {
            cnt[arr[right]]++;
            
            // Shrink window if distinct count > 2
            while(cnt.size() > 2) {
                cnt[arr[left]]--;
                if(cnt[arr[left]] == 0) 
                    cnt.erase(arr[left]);
                left++;
            }
            
            maxLen = max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
};


/*
---------------- DRY RUN ----------------

arr[] = [3, 1, 2, 2, 2, 2]

left=0, right=0: arr[0]=3
  cnt={3:1}, size=1 ≤ 2 ✓
  maxLen = max(0, 0-0+1) = 1

left=0, right=1: arr[1]=1
  cnt={3:1, 1:1}, size=2 ≤ 2 ✓
  maxLen = max(1, 1-0+1) = 2

left=0, right=2: arr[2]=2
  cnt={3:1, 1:1, 2:1}, size=3 > 2 ✗
  → Shrink: remove arr[0]=3
    cnt={1:1, 2:1}, size=2 ≤ 2 ✓
    left=1
  maxLen = max(2, 2-1+1) = 2

left=1, right=3: arr[3]=2
  cnt={1:1, 2:2}, size=2 ≤ 2 ✓
  maxLen = max(2, 3-1+1) = 3

left=1, right=4: arr[4]=2
  cnt={1:1, 2:3}, size=2 ≤ 2 ✓
  maxLen = max(3, 4-1+1) = 4

left=1, right=5: arr[5]=2
  cnt={1:1, 2:4}, size=2 ≤ 2 ✓
  maxLen = max(4, 5-1+1) = 5

Answer = 5 ✓
Subarray: [1, 2, 2, 2, 2] from index 1-5

--------------------------------------------------

FINAL SUMMARY:

Category: Array
Pattern: Sliding Window + HashMap
Key Idea: Maintain window with ≤2 distinct, expand right, shrink left when needed

Whenever problem says:
- Longest/shortest subarray with constraint
- At most/exactly K distinct elements
- Window-based operations
→ Think Sliding Window

TIME: O(N)
SPACE: O(1) - max 3 elements in map
*/
