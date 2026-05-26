/*
Problem: Remove b and ac from a given string

Given a string, remove:
1. Every 'b'
2. Every occurrence of "ac"

We must:
- Traverse only once
- Do it in O(n)
- Use O(1) extra space

Example:
Input : "aacbacc"
Output: "ac"

Explanation:
"aacbacc"
 -> remove "ac" from index 1
 -> remove 'b'
 -> remove another "ac"
Remaining = "ac"

--------------------------------------------------

Pattern:
String Processing + Two Pointer In-Place Modification

--------------------------------------------------

Key Observation:

We only care about:
1. Single character 'b'
2. Pair "ac"

So while traversing:
- Skip 'b'
- If current = 'a' and next = 'c' -> skip both
- Otherwise keep character

--------------------------------------------------

Approach (Optimal)

Use:
- i -> read pointer
- j -> write pointer

Steps:
1. Traverse string using i
2. If s[i] == 'b'
      skip it

3. Else if s[i]=='a' AND s[i+1]=='c'
      skip both characters

4. Else
      copy s[i] to s[j]
      increment j

Finally resize string to j.

--------------------------------------------------

Dry Run:

s = "aacbacc"

i=0
"a" not followed by c
keep -> "a"

i=1
"ac" found
skip both

i=3
'b'
skip

i=4
"ac" found
skip both

i=6
'c'
keep

Result = "ac"

--------------------------------------------------

Time Complexity:
O(n)

Space Complexity:
O(1)

--------------------------------------------------

GFG Link:
https://www.geeksforgeeks.org/problems/remove-b-and-ac-from-a-given-string1009/1

LeetCode Link:
No exact LeetCode equivalent

--------------------------------------------------
*/
/*
Time Complexity: O(n)
Space Complexity: O(n)
*/

class Solution
{
public:

    string stringFilter(string str)
    {
        string ans;

        int n = str.size();

        for(int i = 0; i < n; i++)
        {
            // Remove 'b'
            if(str[i] == 'b')
            {
                continue;
            }

            // Remove "ac"
            if(i + 1 < n && str[i] == 'a' && str[i + 1] == 'c')
            {
                i++; // skip 'c'
                continue;
            }

            // Keep valid character
            ans.push_back(str[i]);
        }

        return ans;
    }
};