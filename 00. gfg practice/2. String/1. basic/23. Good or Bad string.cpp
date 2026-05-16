/*
Problem: Good or Bad string

GFG: https://www.geeksforgeeks.org/problems/good-or-bad-string1417/1

Description:
In this problem, a String S is composed of lowercase alphabets and wildcard characters i.e. '?'. 
Here, '?' can be replaced by any of the lowercase alphabets. Now you have to classify the given String 
on the basis of following rules:

If there are more than 3 consonants together or more than 5 vowels together, String is considered to be "BAD". 
A String is considered "GOOD" only if it is not "BAD".

NOTE: String is considered as "BAD" if the above condition is satisfied even once. Else it is "GOOD".

Examples:

Input: S = "aeioup??"
Output: 1
Explanation: The String doesn't contain more than 3 consonants or more than 5 vowels together. So, it's a GOOD string.

Input: S = "bcdaeiou??"
Output: 0
Explanation: The String contains substring "aeiou??" which counts as 7 vowels together. So, it's a BAD string.

Constraints:
1 <= |S| <= 100000

Approach (Greedy String Traversal):
Key insight:
- Track consecutive vowels and consonants separately
- '?' can act as both vowel and consonant (worst case)
- If either count exceeds limits at any point, string is BAD
- Use greedy approach assuming '?' becomes the worst possible character

Algorithm:
1. Initialize vowelCount and consonantCount to 0
2. Traverse string character by character
3. For each character:
   - If vowel: increment vowelCount, reset consonantCount
   - If consonant: increment consonantCount, reset vowelCount
   - If '?': increment both counts (worst case scenario)
4. If vowelCount > 5 or consonantCount > 3: return 0 (BAD)
5. If traversal completes without exceeding limits: return 1 (GOOD)

Time Complexity: O(n)
Space Complexity: O(1)

Pattern: Greedy String Traversal / Pattern Recognition
*/

#include <bits/stdc++.h>
using namespace std;

/*
=====================================================
GOOD/BAD STRING CLASSIFICATION APPROACH
=====================================================

TC: O(n)
SC: O(1)

🔥 GREEDY PATTERN DETECTION
- Track consecutive vowels and consonants
- '?' acts as both vowel and consonant
- Check limits during traversal

🧠 KEY INSIGHT:
Worst case analysis:
- '?' can become vowel OR consonant
- To be safe, assume '?' becomes the worst option
- If even worst case is GOOD, then string is GOOD

🎯 ALGORITHM:
1. Track consecutive vowels and consonants
2. Handle '?' as both vowel and consonant
3. Check limits during traversal
4. Return BAD if limits exceeded
5. Return GOOD if traversal completes

⚡ CLASSIFICATION LOGIC:
s = "aeioup??"

Step 1: Initialize
vowelCount = 0, consonantCount = 0

Step 2: Traverse and classify
a: vowel -> vowelCount=1, consonantCount=0
e: vowel -> vowelCount=2, consonantCount=0
i: vowel -> vowelCount=3, consonantCount=0
o: vowel -> vowelCount=4, consonantCount=0
u: vowel -> vowelCount=5, consonantCount=0
p: consonant -> vowelCount=0, consonantCount=1
?: wildcard -> vowelCount=1, consonantCount=2
?: wildcard -> vowelCount=2, consonantCount=3

Step 3: Check limits
vowelCount (2) <= 5 ✓
consonantCount (3) <= 3 ✓

Result: GOOD -> 1

s = "bcdaeiou??"

Step 1: Initialize
vowelCount = 0, consonantCount = 0

Step 2: Traverse and classify
b: consonant -> vowelCount=0, consonantCount=1
c: consonant -> vowelCount=0, consonantCount=2
d: consonant -> vowelCount=0, consonantCount=3
a: vowel -> vowelCount=1, consonantCount=0
e: vowel -> vowelCount=2, consonantCount=0
i: vowel -> vowelCount=3, consonantCount=0
o: vowel -> vowelCount=4, consonantCount=0
u: vowel -> vowelCount=5, consonantCount=0
?: wildcard -> vowelCount=6, consonantCount=1
?: wildcard -> vowelCount=7, consonantCount=2

Step 3: Check limits
vowelCount (7) > 5 ✗ -> BAD

Result: BAD -> 0
*/

class Solution {
public:

    // Helper function to check if character is vowel
    bool isVowel(char ch) {

        return (ch == 'a' || ch == 'e' ||
                ch == 'i' || ch == 'o' ||
                ch == 'u');
    }

    // TC: O(n)
    // SC: O(1)

    int isGoodorBad(string S) {

        int vowels = 0;
        int consonants = 0;

        // Traverse string
        for(char ch : S) {

            // Vowel
            if(isVowel(ch)) {

                vowels++;
                consonants = 0;
            }

            // Wildcard - can be both vowel and consonant
            else if(ch == '?') {

                // In worst case, '?' can be vowel or consonant
                vowels++;
                consonants++;
            }

            // Consonant
            else {

                consonants++;
                vowels = 0;
            }

            // BAD condition check
            if(vowels > 5 || consonants > 3) {
                return 0;
            }
        }

        // GOOD string
        return 1;
    }
};


/*
-----------------------------------------------------

🧠 INTERVIEW INSIGHT

Whenever problem involves:
    PATTERN RECOGNITION
    + WILDCARD HANDLING
    + STRING CLASSIFICATION

Think immediately:
    GREEDY PATTERN DETECTION

-----------------------------------------------------

KEY OBSERVATIONS:

1. '?' can be both vowel and consonant
2. Need worst case analysis
3. Limits are strict: >5 vowels or >3 consonants
4. Single violation makes string BAD

-----------------------------------------------------

COMMON MISTAKES:

1. Not handling '?' as both types
2. Resetting counts incorrectly
3. Not checking limits during traversal
4. Missing edge cases with consecutive '?'

-----------------------------------------------------

SIMILAR PROBLEMS

- Pattern validation
- String classification
- Wildcard handling problems

-----------------------------------------------------

🎯 REUSABLE PATTERN:

Whenever:
- Validate string patterns
- Handle wildcards/flexible characters
- Check consecutive character limits

Think:
Greedy Pattern Detection with Worst Case Analysis

Algorithm:
1. Track consecutive character types
2. Handle wildcards as worst case
3. Check limits during traversal
4. Return classification result

Key insight:
Worst case analysis ensures correctness with wildcards

-----------------------------------------------------
*/
