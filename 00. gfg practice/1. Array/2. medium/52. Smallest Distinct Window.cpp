/*
================================================================================
PROBLEM STATEMENT & EXAMPLES
================================================================================

PROBLEM: Smallest Distinct Window (GFG)

Given a string, find the length of the smallest substring that contains
ALL DISTINCT CHARACTERS of the string at least once.

Examples:

Input: str = "aabcbcdbca"
Output: 4
Explanation: Distinct chars = {a, b, c, d}
SubString "dbca" has the smallest length that contains all characters of str.

Input: str = "aaab"
Output: 2
Explanation: Distinct chars = {a, b}
SubString "ab" has the smallest length that contains all characters of str.

Input: str = "geeksforgeeks"
Output: 7
Explanation: Distinct chars = {g, e, k, s, f, o, r}
Multiple substrings work: "eksforg" and "ksforge" both have length 7

Constraints:
1 ≤ str.size() ≤ 10^5
str contains only lower-case english alphabets.

GFG: https://practice.geeksforgeeks.org/problems/smallest-distant-window3132/1

================================================================================
*/


// ============================================================
// APPROACH: SLIDING WINDOW WITH MAP & SET
// Time: O(N), Space: O(26) = O(1)
// ============================================================
/*
HOW IT WORKS:

This is a sliding window problem with 2 phases:

Phase 1: Collect all distinct characters
- Use a SET to store all unique characters in the string
- This is our TARGET count

Phase 2: Sliding window
- Use MAP to track character frequencies in current window
- Expand RIGHT pointer: add each character to map
- If map.size() == required distinct count: we have all chars
- Shrink LEFT pointer: remove characters from left
- Update minimum length whenever we have a valid window

Why this works:
- We need ALL distinct characters, not all characters
- The map automatically tracks which distinct chars are in window
- map.size() directly tells us how many distinct chars we have
- Once window contains all distinct chars, minimize by shrinking
- Set makes it easy to know the target count

Example with "aabcbcdbca":
distinctSet = {a, b, c, d} → required = 4 chars

right expands:    a a b c b c d b c a
                  0 1 2 3 4 5 6 7 8 9

When we reach index 6 (d), map has all 4 keys
Window "aabcbcd" = length 7

Shrink left: remove 'a' at 0 → "abcbcd" = length 6
Continue... eventually get "dbca" = length 4 ✓


WHY THIS WORKS:
1. Set gives us the TARGET (number of distinct chars needed)
2. Map.size() directly tells us current distinct chars in window
3. No need to manually count formed characters
4. Cleaner code: map.find(c) tells if char exists


DRY RUN:

str = "aabcbcdbca"

Step 1: Collect distinct characters
distinctSet = {a, b, c, d} → required.size() = 4

───────────────────────────────────────

map<char, int> charMap
left = 0, minLen = INT_MAX

right = 0, str[0] = 'a':
    charMap['a']++ → charMap = {a:1}
    charMap.size() = 1 < required.size() (4), so don't shrink

right = 1, str[1] = 'a':
    charMap['a']++ → charMap = {a:2}
    charMap.size() = 1 < 4, so don't shrink

right = 2, str[2] = 'b':
    charMap['b']++ → charMap = {a:2, b:1}
    charMap.size() = 2 < 4, so don't shrink

right = 3, str[3] = 'c':
    charMap['c']++ → charMap = {a:2, b:1, c:1}
    charMap.size() = 3 < 4, so don't shrink

right = 4, str[4] = 'b':
    charMap['b']++ → charMap = {a:2, b:2, c:1}
    charMap.size() = 3 < 4, so don't shrink

right = 5, str[5] = 'c':
    charMap['c']++ → charMap = {a:2, b:2, c:2}
    charMap.size() = 3 < 4, so don't shrink

right = 6, str[6] = 'd':
    charMap['d']++ → charMap = {a:2, b:2, c:2, d:1}
    charMap.size() = 4 == required.size() ✓
    
    NOW SHRINK:
    
    Window: [0,6] = "aabcbcd" → length 7
    minLen = min(INT_MAX, 7) = 7
    
    Shrink left: charMap['a']-- → charMap['a'] = 1
    charMap still has all 4 keys, so map.size() still 4
    left++
    left = 1
    
    Window: [1,6] = "abcbcd" → length 6
    minLen = min(7, 6) = 6
    
    Shrink left: charMap['a']-- → charMap['a'] = 0
    Remove 'a' from map (when freq becomes 0)
    charMap = {b:2, c:2, d:1}, map.size() = 3
    charMap.size() < required.size(), exit shrink loop

right = 7, str[7] = 'b':
    charMap['b']++ → charMap = {b:3, c:2, d:1}
    charMap.size() = 3 < 4, so don't shrink

right = 8, str[8] = 'c':
    charMap['c']++ → charMap = {b:3, c:3, d:1}
    charMap.size() = 3 < 4, so don't shrink

right = 9, str[9] = 'a':
    charMap['a']++ → charMap = {a:1, b:3, c:3, d:1}
    charMap.size() = 4 == required.size() ✓
    
    NOW SHRINK:
    
    Window: [1,9] = "bcbcdbca" → length 8
    minLen = min(6, 8) = 6 (no update)
    
    (Continue shrinking...)
    
    Eventually reach:
    [6,9] = "dbca" with charMap = {d:1, b:1, c:1, a:1}
    Window length = 4
    minLen = min(6, 4) = 4 ✓

Final: minLen = 4 ✓

Result: ✓ Matches expected output "dbca"
*/

class Solution {
public:
    int findSubString(string str) {
        
        // Step 1: Store all distinct characters in a set
        unordered_set<char> distinctSet;
        for(char c : str) {
            distinctSet.insert(c);
        }
        
        int required = distinctSet.size();
        
        // Step 2: Sliding window with map
        unordered_map<char, int> charMap;
        int left = 0;
        int minLen = INT_MAX;
        
        for(int right = 0; right < str.size(); right++) {
            
            // Expand: Add character from right
            charMap[str[right]]++;
            
            // Step 3: Shrink window when we have all distinct chars
            while(charMap.size() == required) {
                
                // Update minimum length
                minLen = min(minLen, right - left + 1);
                
                // Remove character from left
                charMap[str[left]]--;
                
                // If frequency becomes 0, remove from map
                if(charMap[str[left]] == 0) {
                    charMap.erase(str[left]);
                }
                
                left++;
            }
        }
        
        return minLen;
    }
};


/*
================================================================================
KEY INSIGHTS & PATTERN RECOGNITION
================================================================================

SLIDING WINDOW PATTERN:
Problems asking for "smallest/longest window/substring":
→ Usually Sliding Window + Map/Set

WHEN TO USE MAP/SET vs FREQ ARRAY:
- FREQ ARRAY: Only lowercase letters (fixed 26 chars) → faster, O(1) space
- MAP/SET: Unicode, any characters, or cleaner code → flexible

WHY MAP + SET IS EASIER:
✓ charMap.size() directly tells us distinct chars in window
✓ No need to manually track "formed" counter
✓ charMap.erase() automatically removes when count becomes 0
✓ Set clearly shows what we're looking for (required)
✓ More readable: charMap.size() == required instead of formed == required

SLIDING WINDOW VARIANTS:
1. Smallest window with ALL DISTINCT chars → This problem
2. Smallest window with SPECIFIC char set → Use set for required
3. Longest substring with at most K distinct → Compare to K directly
4. Longest substring without repeating → charMap.size() <= 1

TWO PHASES - ALWAYS:
Phase 1: Determine REQUIREMENT (what we need to find)
Phase 2: Use sliding window to OPTIMIZE

WHEN TO SHRINK:
- EXPAND until: charMap.size() == required
- SHRINK while: charMap.size() == required
- UPDATE: minLen at each valid state
- STOP shrinking when: charMap.size() < required (lost a char)

TIME COMPLEXITY:
- Each character visited at most 2 times (right + left pointer)
- O(N)

SPACE COMPLEXITY:
- unordered_set: O(26) = O(1) for lowercase letters
- unordered_map: O(26) = O(1) for lowercase letters
- Overall: O(1)

SIMILAR PROBLEMS:
- LeetCode 76: Minimum Window Substring (specific chars)
- LeetCode 3: Longest Substring Without Repeating Characters
- LeetCode 159: Longest Substring with At Most Two Distinct Characters
- GFG: Smallest Distinct Window (this problem)

================================================================================
*/
