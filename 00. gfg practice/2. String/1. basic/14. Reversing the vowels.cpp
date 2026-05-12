/*
Problem:
Reverse only the vowels in the string.

Vowels:
a, e, i, o, u

Example:
s = "practice"

Vowels:
a, i, e

Reversed vowels:
e, i, a

Answer:
"prectica"

Approach:
Two Pointer Technique

1. Take two pointers:
      left  -> start
      right -> end

2. Move left until vowel found.
3. Move right until vowel found.
4. Swap both vowels.
5. Continue until pointers cross.

Why this works?
- Only vowels are swapped.
- Consonants remain at same positions.
- Vowels automatically get reversed.

Pattern:
Two Pointers

Time Complexity: O(N)
Space Complexity: O(1)

GFG Link:
https://www.geeksforgeeks.org/problems/reversing-the-vowels5304/1
*/

class Solution {
public:

    // Check vowel
    bool isVowel(char ch) {

        return (ch == 'a' || ch == 'e' ||
                ch == 'i' || ch == 'o' ||
                ch == 'u');
    }

    string modify(string s) {

        int left = 0;
        int right = s.size() - 1;

        // Two pointer traversal
        while(left < right) {

            // Move left until vowel found
            while(left < right && !isVowel(s[left])) {
                left++;
            }

            // Move right until vowel found
            while(left < right && !isVowel(s[right])) {
                right--;
            }

            // Swap vowels
            swap(s[left], s[right]);

            left++;
            right--;
        }

        return s;
    }
};

/*
Summary:
- Use two pointers
- Find vowels from both sides
- Swap them
- Only vowels get reversed
*/