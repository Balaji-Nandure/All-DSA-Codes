/*
Problem: Sort the fest
Difficulty: Basic

Given the menu of the two restaurants. There may be a chance of fight between them if any one of them have any item in common and you surely don't want that to happen. Each of the menu has 5 items (strings) in them. So, your task is to find out if there is any need to change the menu or let them be happy with their respective menu.

Example 1:
Input:
cake pastry fish candy meat
burger ham fish cake sauce
Output: CHANGE
Explanation: "fish" is common in both the menu.

Example 2:
Input:
pizza chicken cake chilli candy
choco coco cabbage panner cheese
Output: BEHAPPY
Explanation: No item is common.

Your Task:
You don't need to read or print anything. Your task is to complete the function is_common() which takes first menu as first parameter and second menu as second parameter and returns the string "CHANGE" if any item is common otherwise returns "BEHAPPY"(Without quotes).
 
Expected Time Complexity: O(n)
Expected Space Complexity: O(n)

Constraints:
1 <= Size of each string <= 1000
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // TC: O(N) where N is the total characters across strings
    // SC: O(N)
    string is_common(vector<string> s1, vector<string> s2) {
        unordered_set<string> menu1;
        
        // Insert all items of the first menu into a hash set
        for (const string& item : s1) {
            menu1.insert(item);
        }
        
        // Check if any item in the second menu exists in the first menu
        for (const string& item : s2) {
            if (menu1.find(item) != menu1.end()) {
                return "CHANGE";
            }
        }
        
        return "BEHAPPY";
    }
};
