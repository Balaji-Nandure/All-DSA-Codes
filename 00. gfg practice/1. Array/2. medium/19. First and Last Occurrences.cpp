/*
Problem: First and Last Occurrences in Sorted Array

GFG: https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/

Description: Given a sorted array arr with possibly some duplicates, task is to find first and last occurrences of an element x in given array.
Note: If number x is not found in array then return both indices as -1.

Examples:

Input: arr[] = [1, 3, 5, 5, 5, 5, 67, 123, 125], x = 5
Output: [2, 5]
Explanation: First occurrence of 5 is at index 2 and last occurrence of 5 is at index 5
Input: arr[] = [1, 3, 5, 5, 5, 5, 7, 123, 125], x = 7
Output: [6, 6]
Explanation: First and last occurrence of 7 is at index 6
Input: arr[] = [1, 2, 3], x = 4
Output: [-1, -1]
Explanation: No occurrence of 4 in array, so, output is [-1, -1]

Constraints:
1 ≤ arr.size() ≤ 106
1 ≤ arr[i], x ≤ 109

Striver Intuition:

Since array is sorted and contains duplicates,
we use Binary Search.

Normal binary search finds any one occurrence.
But we need:
- First occurrence → move LEFT when found
- Last occurrence → move RIGHT when found

So we run binary search twice:
1. First Occurrence:
   If arr[mid] == x → store ans, move left (high = mid - 1)
2. Last Occurrence:
   If arr[mid] == x → store ans, move right (low = mid + 1)

Pattern:
Sorted Array + Duplicates → Binary Search (First/Last Occurrence)

Time Complexity: O(log n)
Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstOccurrence(vector<int>& arr, int x) {
        int low = 0, high = arr.size() - 1;
        int ans = -1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(arr[mid] == x) {
                ans = mid;
                high = mid - 1; // move left
            }
            else if(arr[mid] < x) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return ans;
    }

    int lastOccurrence(vector<int>& arr, int x) {
        int low = 0, high = arr.size() - 1;
        int ans = -1;

        while(low <= high) {
            int mid = low + (high - low) / 2;

            if(arr[mid] == x) {
                ans = mid;
                low = mid + 1; // move right
            }
            else if(arr[mid] < x) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }

        return ans;
    }

    vector<int> find(vector<int>& arr, int x) {
        int first = firstOccurrence(arr, x);
        int last = lastOccurrence(arr, x);
        return {first, last};
    }
};

/*
Final Summary (Interview Revision):

1. Array sorted + duplicates → Binary Search.
2. First occurrence:
      arr[mid] == x → move left
3. Last occurrence:
      arr[mid] == x → move right
4. Run binary search twice.
5. Time = O(log n)

Memory Trick:
First Occurrence → Go Left
Last Occurrence  → Go Right
*/
