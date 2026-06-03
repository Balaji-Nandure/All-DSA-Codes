/*
GeeksforGeeks: Earthquake and the Paint Shop
Difficulty: Easy

Problem:
Geek's Paint Shop is one of the famous shops in Geekland, but 2014 Earthquake caused disarrangement of the items in his shop. 
Each item in his shop is a 40-digit alpha numeric code.
Now Chunky wants to retain the reputation of his shop, for that he has to arrange all the distinct items in lexicographical order.
Your task is to arrange all the distinct items in lexicographical ascending order and print them along with their count.

Examples:
Input:
N = 3
A[] =
["2234597891 zmxvvxbcij 8800654113 jihgfedcba",
"1234567891 abcdefghij 9876543219 jihgfedcba",
"2234597891 zmxvvxbcij 8800654113 jihgfedcba"]

Output:
1234567891 abcdefghij 9876543219 jihgfedcba 1
2234597891 zmxvvxbcij 8800654113 jihgfedcba 2

Core Idea:
We need to count the frequency of each 40-digit alphanumeric string AND we need to return them in perfectly sorted lexicographical (alphabetical/numerical) order.
While an `unordered_map` counts frequencies extremely fast, it does NOT sort the keys. We would have to manually extract the keys and sort them afterward.
However, a standard `std::map` (ordered map) in C++ is backed by a Red-Black Tree. It automatically and natively keeps all of its keys completely sorted at all times!
By just inserting the strings into a `std::map`, we solve both the frequency counting and the sorting simultaneously.

Approach:
1. Initialize an ordered `std::map<string, int> dict`.
2. Iterate through the input vector `A` and count the frequencies: `dict[str]++`. 
   (As elements are inserted, the `std::map` automatically places them in sorted order).
3. Initialize a `vector<alphanumeric> result`.
4. Iterate through the `std::map`. Because it's an ordered map, this loop naturally traverses the elements in strictly increasing lexicographical order.
5. Create an `alphanumeric` struct for each map entry and push it into the `result` vector.
6. Return `result`.

Time Complexity: O(N * L * log N), where N is the number of strings and L is the length of each string (40). The log N factor comes from inserting into the Red-Black Tree, and L comes from comparing strings during insertion.
Space Complexity: O(N * L) auxiliary space to store the strings in the map.

GFG Link: https://www.geeksforgeeks.org/problems/earthquake-and-the-paint-shop4518/1
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// This struct is predefined by the GFG driver code for this specific problem.
struct alphanumeric {
    string name;
    int count;
};

class Solution {
public:
    vector<alphanumeric> sortedStrings(int N, vector<string> A) {
        // We use std::map (not unordered_map) because it automatically sorts the keys!
        map<string, int> dict;
        
        // Count frequencies. std::map handles sorting under the hood.
        for (const string& s : A) {
            dict[s]++;
        }
        
        vector<alphanumeric> result;
        
        // Iterating through std::map naturally goes in ascending key order
        for (auto& entry : dict) {
            alphanumeric item;
            item.name = entry.first;
            item.count = entry.second;
            result.push_back(item);
        }
        
        return result;
    }
};

/*
Dry Run — Example 1:
A = [
  "223459...", 
  "123456...", 
  "223459..."
]

1. Insert into map:
   dict["223459..."]++ -> Map contains: {"223459...": 1}
   
   dict["123456..."]++ -> "123456..." is lexicographically smaller than "223459...".
   Map automatically orders them inside its Red-Black Tree:
   {"123456...": 1, "223459...": 1}
   
   dict["223459..."]++ -> Key already exists.
   Map updates count:
   {"123456...": 1, "223459...": 2}
   
2. Construct Result:
   Iteration 1: entry = {"123456...", 1}
   result.push_back({name: "123456...", count: 1})
   
   Iteration 2: entry = {"223459...", 2}
   result.push_back({name: "223459...", count: 2})

3. Return result.

Output structure matches exactly what is expected.
*/
