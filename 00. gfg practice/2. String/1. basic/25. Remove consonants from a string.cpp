/*
Problem: Remove consonants from a string

GFG: https://www.geeksforgeeks.org/problems/remove-consonants-from-a-string/1

Description:
Given a string S, remove all consonants and print modified string that contains vowels only.

Examples:

Input: S = "abEkipo"
Output: "aEio"
Explanation: a, E, i, o are only vowels in the string.

Input: S = "rrty"
Output: "No Vowel"
Explanation: There are no vowels.

Constraints:
1 <= |S| <= 10^5
The string should consist of only alphabets.

Approach (Vowel Filtering):
Key insight:
- Identify vowels (both lowercase and uppercase)
- Filter out all consonants
- Return only vowels or "No Vowel" if none found

Algorithm:
1. Create a set/check for vowels (a, e, i, o, u in both cases)
2. Initialize empty result string
3. Traverse string character by character
4. If character is vowel, add to result
5. After traversal, if result is empty return "No Vowel"
6. Otherwise return result string

Time Complexity: O(n)
Space Complexity: O(n) for result string

Pattern: String Filtering / Character Selection
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
VOWEL FILTERING APPROACH
=====================================================

TC: O(n)
SC: O(n) for result string

🔥 CHARACTER FILTERING
- Identify vowels (both cases)
- Filter out consonants
- Handle no vowel case

🧠 KEY INSIGHT:
Vowel identification:
- Lowercase: a, e, i, o, u
- Uppercase: A, E, I, O, U
- All other alphabets are consonants

🎯 ALGORITHM:
1. Check each character for vowel
2. Build result string with vowels only
3. Handle empty result case
4. Return appropriate output

⚡ FILTERING LOGIC:
S = "abEkipo"

Step 1: Initialize result = ""

Step 2: Traverse and filter
a -> vowel -> result = "a"
b -> consonant -> skip
E -> vowel -> result = "aE"
k -> consonant -> skip
i -> vowel -> result = "aEi"
p -> consonant -> skip
o -> vowel -> result = "aEio"

Step 3: Check result
result is not empty -> return "aEio"

Final: "aEio"

S = "rrty"

Step 1: Initialize result = ""

Step 2: Traverse and filter
r -> consonant -> skip
r -> consonant -> skip
t -> consonant -> skip
y -> consonant -> skip

Step 3: Check result
result is empty -> return "No Vowel"

Final: "No Vowel"
*/

class Solution {
public:

    // Helper function to check if character is vowel
    bool isVowel(char ch) {

        // Check both lowercase and uppercase vowels
        return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
                ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U');
    }

    // TC: O(n)
    // SC: O(n) for result string

    string removeConsonants(string S) {

        string result = "";

        // Filter vowels only
        for(char ch : S) {

            if(isVowel(ch)) {
                result += ch;
            }
        }

        // Handle no vowel case
        if(result.empty()) {
            return "No Vowel";
        }

        return result;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    VOWEL EXTRACTION
    + CHARACTER FILTERING
    + EMPTY RESULT HANDLING

Think immediately:
    VOWEL FILTERING

-----------------------------------------------------

KEY OBSERVATIONS:

1. Need to handle both uppercase and lowercase vowels
2. All other alphabets are consonants
3. Empty result requires special output
4. Simple filtering problem

-----------------------------------------------------

COMMON MISTAKES:

1. Forgetting uppercase vowels
2. Not handling empty result case
3. Using inefficient vowel checking
4. Complex logic for simple filtering

-----------------------------------------------------

SIMILAR PROBLEMS

- Character extraction
- String filtering problems
- Vowel/consonant manipulation

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Extract specific character types
- Filter string based on character properties
- Handle empty result cases

Think:
Character Filtering with Special Case Handling

Algorithm:
1. Define character selection criteria
2. Filter characters based on criteria
3. Handle empty result appropriately
4. Return filtered string or special message

Key insight:
Simple filtering with edge case handling

-----------------------------------------------------
*/
