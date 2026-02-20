/*
Question:
Given an array arr[] of positive integers. Return true if all the array elements are palindrome otherwise, return false.

Examples:

Input: arr[] = [111, 222, 333, 444, 555]
Output: true
Explanation:
All elements are palindrome numbers.

Input: arr[] = [121, 131, 20]
Output: false
Explanation: 20 is not a palindrome hence the output is false.

Expected Time Complexity: O(nlogn)
Expected Space Complexity: O(1)

Constraints:
1 <= arr.size <= 20
1 <= arr[i] <= 10^5
*/

// Solution:
#include <iostream>
#include <vector>
using namespace std;

// Helper function to check if a number is palindrome
bool isPalindrome(int n) {
    int original = n, rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;
        n /= 10;
    }
    return rev == original;
}

// Function to check if all elements of the array are palindrome numbers
bool isPalindromicArray(const vector<int>& arr) {
    for (int num : arr) {
        if (!isPalindrome(num))
            return false;
    }
    return true;
}
