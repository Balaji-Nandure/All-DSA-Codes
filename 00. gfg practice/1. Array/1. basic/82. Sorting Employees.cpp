/*
 * Problem: Sorting Employees
 * 
 * GeeksforGeeks: https://www.geeksforgeeks.org/problems/sorting-employees/1
 * 
 * Given two arrays employee[] and salary[], sort the employee array based on 
 * their salaries in non-decreasing order. If two or more employees have the 
 * same salary, sort them alphabetically by their names.
 * 
 * Examples:
 * Input: employee = ["chef", "geek"], salary = [100, 50]
 * Output: ["geek", "chef"]
 * Explanation: "geek" has lower salary (50) than "chef" (100).
 * 
 * Input: employee = ["ram", "shyam", "rohan"], salary = [60, 45, 60]
 * Output: ["shyam", "ram", "rohan"]
 * Explanation: "shyam" has lowest salary (45). "ram" and "rohan" both have 
 * salary 60, so they maintain original order (stable sort).
 * 
 * Constraints:
 * 1 ≤ employee.size() = salary.size() ≤ 10^5
 * 1 ≤ salary[i] ≤ 10^6
 * employee[i] contains only lowercase alphabetic characters
 * 
 * Expected Time Complexity: O(n log n)
 * Expected Auxiliary Space: O(n)
 * 
 * Approach:
 * - Create pairs of (salary, employee) to maintain association
 * - Use custom comparator for sorting:
 *   1. Primary: Sort by salary (ascending)
 *   2. Secondary: Sort by name (lexicographically) for same salary
 * - Extract sorted employee names from the sorted pairs
 * - Alternative: Use indices array and sort indices based on criteria
 * 
 * Time: O(n log n) - sorting dominates
 * Space: O(n) - for pairs or indices array
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    
    // Custom comparator function
    static bool comp(const pair<int, string>& a, const pair<int, string>& b) {
        
        // Primary criteria: salary in ascending order
        if(a.first != b.first) {
            return a.first < b.first;
        }
        
        // Secondary criteria: name in lexicographical order
        return a.second < b.second;
    }
    
    vector<string> sortEmployees(vector<string>& employee, vector<int>& salary) {
        
        int n = employee.size();
        
        // Create pairs of (salary, employee) for easy sorting
        vector<pair<int, string>> employees;
        
        for(int i = 0; i < n; i++) {
            employees.push_back({salary[i], employee[i]});
        }
        
        // Sort using custom comparator function
        sort(employees.begin(), employees.end(), comp);
        
        // Extract sorted employee names
        vector<string> result;
        for(const auto& emp : employees) {
            result.push_back(emp.second);
        }
        
        return result;
    }
};