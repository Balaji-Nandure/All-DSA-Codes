/*
Problem: K Closest Elements

GFG: https://www.geeksforgeeks.org/problems/k-closest-elements3619/1

Description:
You are given a sorted array arr[] of unique integers, an integer k, and a target value x. Return exactly k elements from the array closest to x, excluding x if it exists.

An element a is closer to x than b if:
|a - x| < |b - x|, or
|a - x| == |b - x| and a > b (i.e., prefer the larger element if tied)

Return the k closest elements in order of closeness.

Examples:

Input: arr[] = [1, 3, 4, 10, 12], k = 2, x = 4
Output: [3, 1]
Explanation: 4 is excluded from the consideration.
The closest element to 4 is 3 with a distance of 1.
The next closest element is 1 with a distance of 3.

Input: arr[] = [10, 20, 30, 40, 50], k = 3, x = 25
Output: [30, 20, 40]
Explanation: First closest element to 25 is 30, since 30 > 20.
Second closest element to 25 is 20.
Third closest element to 25 is 40.

Constraints:
1 ≤ arr.size() ≤ 10^5
1 ≤ k ≤ arr.size()
1 ≤ x ≤ 10^6
1 ≤ arr[i] ≤ 10^6

Approach (Binary Search + Two Pointers):
1. Find lower_bound of x → gives insertion point
2. Initialize:
   left = idx - 1
   right = idx
3. Loop k times:
   - If left valid & right valid:
        compare abs(arr[left] - x) and abs(arr[right] - x)
        pick smaller difference
        if equal → pick right (larger element)
   - Else take from valid side
4. Store result in order of selection

Why it works:
- Sorted array → nearest elements lie around x
- Expanding outwards ensures closest picks first
- Binary search gives us the starting point efficiently
- Two-pointer approach guarantees we pick elements in order of closeness

Time Complexity:
- Binary Search → O(log n)
- K iterations → O(k)
Total → O(log n + k)

Space Complexity:
- O(k) (result storage)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findIndex(vector<int> & arr, int x){
        int n = arr.size();
        int low = 0, high = n - 1;
        int ans = n;
        
        while(low <= high){
            int mid = low + (high - low) / 2;
            
            if(arr[mid] >= x){
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        return ans;
    }
    
    vector<int> printKClosest(vector<int> arr, int k, int x) {
        // Code here
        int n = arr.size();
        int indx = findIndex(arr, x);
        
        int left = indx - 1;
        // because we want to exclude x from calculations
        if(indx < n && arr[indx] == x){
            indx++;
        }
        int right = indx;
        
        vector<int> result;
        
        while(k --){
            if(left >= 0 && right < n){
                int dl = abs(arr[left] - x);
                int dr = abs(arr[right] - x);
                
                if(dl < dr){
                    result.push_back(arr[left]);
                    left--;
                } else {
                    result.push_back(arr[right]);
                    right++;
                }
            } else if(left >= 0){
                result.push_back(arr[left]);
                left--;
            } else {
                result.push_back(arr[right]);
                right++;
            }
        }
        
        
        return result;
    }
};
