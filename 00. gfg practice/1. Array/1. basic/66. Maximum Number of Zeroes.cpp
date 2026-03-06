/*
 * Problem: Maximum Number of Zeroes
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/maximum-number-of-zeroes/1
 * 
 * Given an array arr[] of integers, the task is to find the number that has the 
 * maximum number of zeroes. If there are no zeroes then print -1. If there are 
 * multiple numbers with the same (max) number of zeroes then print the maximum 
 * number among them.
 * 
 * Examples:
 * Input: arr[] = [10, 20, 3000, 9999, 200]
 * Output: 3000
 * Explanation: 3000 contains 3 zero's in it.
 * 
 * Input: arr[] = [1, 2, 3, 4]
 * Output: -1
 * Explanation: No zero is present.
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^5
 * 1 < arr[i] < 10^100
 * 
 * Expected Time Complexity: O(n*log10(max(arr[i])))
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - For each number, count the number of zeros by converting to string or 
 *   using modulo operations
 * - Keep track of maximum zero count and the corresponding number
 * - If multiple numbers have same max zero count, choose the larger number
 * - If no zeros found in any number, return -1
 * - Use string conversion for simplicity and to handle large numbers
 * 
 * Time: O(n * log10(max(arr[i]))) - for each number, count digits
 * Space: O(1) - constant extra space (excluding string conversion)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    
    // Helper function to count zeros in a string number
    int countZeros(const string& num) {
        int count = 0;
        
        for(char c : num) {
            if(c == '0') {
                count++;
            }
        }
        
        return count;
    }
    
    // Helper function to compare two string numbers numerically
    bool isGreater(const string& a, const string& b) {
        if(a.length() != b.length()) {
            return a.length() > b.length();
        }
        return a > b;  // Lexicographic comparison works for same length
    }
    
    string maxZero(vector<string> &arr) {
        
        int maxZeros = 0;
        string result = "-1";
        
        for(const string& num : arr) {
            
            int zeros = countZeros(num);
            
            // Update result if current number has more zeros
            // or same zeros but larger value
            if(zeros > maxZeros || (zeros == maxZeros && zeros > 0 && isGreater(num, result))) {
                maxZeros = zeros;
                result = num;
            }
        }
        
        // If no zeros found in any number
        if(maxZeros == 0) {
            return "-1";
        }
        
        return result;
    }
};