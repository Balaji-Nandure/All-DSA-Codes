/*
 * Problem: Seating Arrangement
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/seating-arrangement-1587115620/1
 * 
 * Given n (number of new people to seat) and seats[] (binary array: 0 = empty, 
 * 1 = occupied). Condition: No two occupied seats can be adjacent. Return true 
 * if we can seat all n people, else false.
 * 
 * Example:
 * Input: n = 2, m = 7, seats[] = {0, 0, 1, 0, 0, 0, 1}
 * Output: Yes
 * Explanation: The two people can sit at index 0 and 4.
 * 
 * Input: n = 1, m = 3, seats[] = {0, 1, 0}
 * Output: No
 * Explanation: There is no way to get a seat for one person.
 * 
 * Constraints:
 * 1 ≤ n, m ≤ 10^5
 * seats[i] is 0 or 1
 * 
 * Expected Time Complexity: O(m)
 * Expected Auxiliary Space: O(1)
 * 
 * Approach:
 * - Iterate through seats array greedily placing people
 * - For each position i where seats[i] == 0
 * - Check if left neighbor (i-1) is empty or doesn't exist
 * - Check if right neighbor (i+1) is empty or doesn't exist
 * - If both conditions met, place person (set seats[i] = 1) and decrement n
 * - Continue until n == 0 or end of array
 * - Greedy works because placing early doesn't block better later options
 * 
 * Time: O(m) - single pass through array
 * Space: O(1) - in-place modification
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool is_possible_to_get_seats(int n, int m, vector<int>& seats) {
        
        for (int i = 0; i < m && n > 0; i++) {
            
            if (seats[i] == 0) {
                
                bool leftEmpty = (i == 0) || (seats[i - 1] == 0);
                bool rightEmpty = (i == m - 1) || (seats[i + 1] == 0);
                
                if (leftEmpty && rightEmpty) {
                    seats[i] = 1; // seat the person
                    n--;
                }
            }
        }
        
        return (n == 0);
    }   
};
