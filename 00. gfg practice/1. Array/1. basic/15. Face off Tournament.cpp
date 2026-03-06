/*
 * Problem: Face off Tournament
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/face-off-tournament/0
 * 
 * Ram and Rohan are participating in a tournament where they must compete against contenders 
 * whose strengths are given in an array arr[]. Ram's strength is m, and Rohan's strength is n. 
 * They take turns competing against the contenders, with Ram always going first. 
 * A contender is defeated if their strength is an exact multiple of either Ram's or Rohan's strength. 
 * Once defeated, a contender cannot compete again.
 * 
 * Determine who wins more matches: Ram or Rohan. If both win the same number of matches, 
 * declare both as winners.
 * 
 * Examples:
 * Input: arr[] = [4, 5, 7, 6, 9, 10, 14], m = 2, n = 3
 * Output: "Ram"
 * Explanation: Ram wins against contenders with strengths [4, 6, 10, 14]. 
 *              Rohan wins against the contender with strength [9].
 * 
 * Input: arr[] = [1, 9, 9, 10, 9, 18], m = 5, n = 3
 * Output: "Rohan"
 * Explanation: Ram wins against the contender with strength [10]. 
 *              Rohan wins against contenders with strengths [9, 9, 9, 18].
 * 
 * Constraints:
 * 1 ≤ arr.size() ≤ 10^6
 * 1 ≤ m, n ≤ 10^6
 * 1 ≤ arr[i] ≤ 10^6
 * 
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Count how many contenders are multiples of m (Ram's wins)
 * - Count how many contenders are multiples of n (Rohan's wins)
 * - For contenders that are multiples of both m and n, they go to Ram since he goes first
 * - So we need to handle the overlap carefully:
 *   * If a number is multiple of both m and n, it should only count for Ram
 *   * This means: Ram wins = count(multiples of m), Rohan wins = count(multiples of n but not m)
 * - Compare the counts and return the winner
 * 
 * Time: O(n) - single pass through array
 * Space: O(1) - constant extra space
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string whoWins(vector<int>& arr, int m, int n) {
        int ramWins = 0;
        int rohanWins = 0;
        
        for (int strength : arr) {
            bool ramCanWin = (strength % m == 0);
            bool rohanCanWin = (strength % n == 0);
            
            if (ramCanWin) {
                ramWins++;
            } else if (rohanCanWin) {
                rohanWins++;
            }
            // If neither can win, skip this contender
        }
        
        if (ramWins > rohanWins) {
            return "Ram";
        } else if (rohanWins > ramWins) {
            return "Rohan";
        } else {
            return "Both";
        }
    }
};

// Main function for testing
int main() {
    Solution sol;
    
    // Test case 1
    vector<int> arr1 = {4, 5, 7, 6, 9, 10, 14};
    cout << "Test 1: " << sol.whoWins(arr1, 2, 3) << endl; // Expected: "Ram"
    
    // Test case 2
    vector<int> arr2 = {1, 9, 9, 10, 9, 18};
    cout << "Test 2: " << sol.whoWins(arr2, 5, 3) << endl; // Expected: "Rohan"
    
    // Test case 3: Both win same number
    vector<int> arr3 = {2, 3, 4, 6};
    cout << "Test 3: " << sol.whoWins(arr3, 2, 3) << endl; // Expected: "Both"
    
    // Test case 4: Ram wins all
    vector<int> arr4 = {2, 4, 6, 8, 10};
    cout << "Test 4: " << sol.whoWins(arr4, 2, 3) << endl; // Expected: "Ram"
    
    // Test case 5: Rohan wins all
    vector<int> arr5 = {3, 6, 9, 12, 15};
    cout << "Test 5: " << sol.whoWins(arr5, 2, 3) << endl; // Expected: "Rohan"
    
    // Test case 6: No one wins
    vector<int> arr6 = {5, 7, 11, 13};
    cout << "Test 6: " << sol.whoWins(arr6, 2, 3) << endl; // Expected: "Both" (0-0)
    
    // Test case 7: Same strengths for both
    vector<int> arr7 = {6, 12, 18};
    cout << "Test 7: " << sol.whoWins(arr7, 2, 3) << endl; // Expected: "Ram" (all go to Ram)
    
    // Test case 8: Single element
    vector<int> arr8 = {6};
    cout << "Test 8: " << sol.whoWins(arr8, 2, 3) << endl; // Expected: "Ram"
    
    return 0;
}
