/*
Rotating an Array

Difficulty: Basic    Accuracy: 44.48%    Submissions: 129K+    Points: 1    Average Time: 20m

Given an array arr[]. The task is to rotate the array by d elements where d ≤ arr.size.

Examples:

Input: arr[] = [-1, -2, -3, 4, 5, 6, 7], d = 2
Output: [-3, 4, 5, 6, 7, -1, -2]

Explanation: 
Rotate by 1: [-2, -3, 4, 5, 6, 7, -1]
Rotate by 2: [-3, 4, 5, 6, 7, -1, -2]

Input: arr[] = [1, 3, 4, 2], d = 3
*/

#include <vector>
using namespace std;

// Solution: Using reversal algorithm for array rotation
class Solution {
public:
    // Helper method to reverse an array segment from index i to j
    void reverseSegment(vector<int>& arr, int i, int j) {
        while(i < j){
            int temp = arr[i];
            arr[i++] = arr[j];
            arr[j--] = temp;
        }
    }
    
    // Rotates arr[] by d elements to the left
    void leftRotate(vector<int>& arr, int d) {
        int n = arr.size();
        if(n == 0) return;
        d = d % n; // handle cases when d > n
        if(d == 0) return; // nothing to rotate

        // Reverse first d elements
        reverseSegment(arr, 0, d - 1);
        // Reverse the remaining n-d elements
        reverseSegment(arr, d, n - 1);
        // Reverse the entire array
        reverseSegment(arr, 0, n - 1);
    }
};