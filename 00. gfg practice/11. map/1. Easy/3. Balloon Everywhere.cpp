/*
GeeksforGeeks: Balloon Everywhere
Difficulty: Easy

Problem:
Bob is very fond of balloons. Once he visited an amusement park with his mother. 
The mother told Bob that she would buy him a balloon only if he answers her problem right. 
She gave Bob a string s [contains only lowercase characters] and asked him to use the characters of the string to form as many instances of the word "balloon" as possible. 
Return the maximum number of instances that can be formed.
Note: You can use each character in the string at most once.

Examples:
Input: s = nlaebolko
Output: 1
Explanation:
Here, the number of occurences of 'b' = 1, 'a' = 1, 'l' = 2, 'o' = 2, 'n' = 1.
So, we can form 1 "balloon" using the letters.

Input: s = loonbalxballpoon
Output: 2
Explanation:
Here, the number of occurences of 'b' = 2, 'a' = 2, 'l' = 4, 'o' = 4, 'n' = 2.
So, we can form 2 "balloon" using the letters.

Core Idea:
To form the word "balloon", we specifically need the following character frequencies for a single instance:
- 'b': 1
- 'a': 1
- 'l': 2
- 'o': 2
- 'n': 1
By tracking the frequency of all characters in the string `s`, we can determine how many times we can spell "balloon". 
Because 'l' and 'o' appear twice in the word, we must divide their total frequencies by 2. 
The maximum number of times we can form "balloon" is strictly bottlenecked by the letter we have the least of. Therefore, it is simply the minimum of the available counts among these 5 specific characters.

Approach:
1. Initialize an array (or Hash Map) `freq` of size 26 to store the frequency of lowercase characters.
2. Traverse the string `s` and increment the count in `freq` for each character.
3. Calculate the potential instances for each required letter:
   - For 'b', 'a', and 'n', it is just `freq[char]`.
   - For 'l' and 'o', it is `freq[char] / 2`.
4. Return the minimum value among these 5 calculated counts using `std::min`.

Time Complexity: O(N) where N is the length of the string, as we traverse the string exactly once. Finding the minimum takes O(1) time.
Space Complexity: O(1) auxiliary space, as we only need an array of size 26 to store the character counts, which is a constant regardless of N.

GFG Link: https://www.geeksforgeeks.org/problems/balloon-everywhere0011/1
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxInstance(string s) {
        // Frequency map for lowercase English letters
        vector<int> freq(26, 0);
        
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        // Calculate the maximum number of times each character can fulfill its role in "balloon"
        int b_count = freq['b' - 'a'];
        int a_count = freq['a' - 'a'];
        int l_count = freq['l' - 'a'] / 2;
        int o_count = freq['o' - 'a'] / 2;
        int n_count = freq['n' - 'a'];
        
        // The limiting character dictates how many full words we can form
        return min({b_count, a_count, l_count, o_count, n_count});
    }
};

/*
Dry Run — Example 1:
Input: s = "nlaebolko"

1. Build frequency map (only relevant letters shown):
   'n': 1
   'l': 2
   'a': 1
   'e': 1 (ignored)
   'b': 1
   'o': 2
   'k': 1 (ignored)

2. Calculate counts based on required amounts:
   b_count = 1
   a_count = 1
   l_count = 2 / 2 = 1
   o_count = 2 / 2 = 1
   n_count = 1

3. Find Minimum:
   min({1, 1, 1, 1, 1}) = 1.

4. Return 1.

Output: 1
*/
