/*
Problem: Count Group Occurrences

GFG: https://www.geeksforgeeks.org/problems/count-group-occurrences/1

Description:
Given a string s. Count the characters that have 'k' number of occurrences. 
If a character appears consecutively it is counted as 1 occurrence.

Examples:

Input: s = "abc", k = 1
Output: 3
Explanation: 'a', 'b' and 'c' all have 1 occurrence.

Input: s = "geeksforgeeks", k = 2
Output: 4
Explanation: 'g', 'e', 'k' and 's' have 2 occurrences.

Input: s = "aaaaa", k = 2
Output: 0
Explanation: There is only one group occurrence of 'a'

Constraints:
1 <= s.length() <= 10^5
1 <= k <= 10^3

Approach (String Traversal + Group Counting):
Key insight:
- Consecutive same characters form one group
- New group starts only when character changes from previous
- Count groups for each character, then count those with exactly k groups

Algorithm:
1. Create frequency array to store group counts
2. First character always starts a group, increment its count
3. Traverse string from index 1
4. When current character differs from previous, it's a new group
5. Increment group count for that character
6. Finally count characters with exactly k groups

Time Complexity: O(n)
Space Complexity: O(1) - fixed size frequency array

Pattern: String Traversal + Frequency Counting
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GROUP COUNTING APPROACH
=====================================================

TC: O(n)
SC: O(1) - fixed size frequency array

🔥 STRING TRAVERSAL WITH GROUP DETECTION
- Identify group boundaries (character changes)
- Count groups for each character
- Find characters with exactly k groups

🧠 KEY INSIGHT:
Group formation rule:
- Consecutive same characters = one group
- New group starts when character changes
- First character always starts a group

🎯 ALGORITHM:
1. Initialize frequency array for group counts
2. First character starts first group
3. Traverse string looking for character changes
4. Increment group count on character change
5. Count characters with exactly k groups

⚡ GROUP COUNTING LOGIC:
s = "geeksforgeeks", k = 2

Step 1: Initialize group counts
freq[26] = {0}

Step 2: First character starts group
g -> freq['g'] = 1

Step 3: Traverse and detect groups
Index 1: 'e' != 'g' -> new group -> freq['e'] = 1
Index 2: 'e' == 'e' -> same group -> skip
Index 3: 'k' != 'e' -> new group -> freq['k'] = 1
Index 4: 's' != 'k' -> new group -> freq['s'] = 1
Index 5: 'f' != 's' -> new group -> freq['f'] = 1
Index 6: 'o' != 'f' -> new group -> freq['o'] = 1
Index 7: 'r' != 'o' -> new group -> freq['r'] = 1
Index 8: 'g' != 'r' -> new group -> freq['g'] = 2
Index 9: 'e' != 'g' -> new group -> freq['e'] = 2
Index 10: 'e' == 'e' -> same group -> skip
Index 11: 'k' != 'e' -> new group -> freq['k'] = 2
Index 12: 's' != 'k' -> new group -> freq['s'] = 2

Step 4: Count characters with exactly k=2 groups
g: 2, e: 2, k: 2, s: 2 -> 4 characters

Final: 4
*/

class Solution {
public:

    // TC: O(n)
    // SC: O(1) - fixed size frequency array

    int getCount(string s, int k) {

        // Stores group occurrences for each character
        int freq[26] = {0};

        // First character always starts a group
        freq[s[0] - 'a']++;

        // Traverse string to find group boundaries
        for(int i = 1; i < s.size(); i++) {

            // New group starts when character changes
            if(s[i] != s[i - 1]) {

                freq[s[i] - 'a']++;
            }
        }

        int ans = 0;

        // Count characters having exactly k groups
        for(int i = 0; i < 26; i++) {

            if(freq[i] == k) {
                ans++;
            }
        }

        return ans;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    GROUP COUNTING
    + CONSECUTIVE CHARACTER HANDLING
    + FREQUENCY ANALYSIS

Think immediately:
    STRING TRAVERSAL WITH CHANGE DETECTION

-----------------------------------------------------

KEY OBSERVATIONS:

1. Groups are defined by character changes
2. First character always starts a group
3. Consecutive duplicates belong to same group
4. Need to count groups, not individual characters

-----------------------------------------------------

COMMON MISTAKES:

1. Counting individual characters instead of groups
2. Not handling first character separately
3. Missing edge case of single character string
4. Using complex data structures unnecessarily

-----------------------------------------------------

SIMILAR PROBLEMS

- Run-length encoding
- Character grouping problems
- String compression tasks

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Count character groups/blocks
- Handle consecutive duplicates
- Need change detection in strings

Think:
String Traversal with Change Detection

Algorithm:
1. Handle first character separately
2. Traverse looking for character changes
3. Increment counts on changes
4. Apply final condition on counts

Key insight:
Groups are identified by character boundaries

-----------------------------------------------------
*/
