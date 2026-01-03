/*
Problem:
Camel Case of a Given Sentence

Given a sentence string s consisting of words separated by spaces,
convert it into Camel Case format.

Camel Case Rules (as per GfG):
- First letter of each word should be capitalized.
- All other letters should be in lowercase.
- Words should be concatenated without spaces.

Examples:
Input  : s = "i got intern at geeksforgeeks"
Output : "IGotInternAtGeeksforgeeks"

Input  : s = "hello world"
Output : "HelloWorld"

Input  : s = "CAMEL case SENTENCE"
Output : "CamelCaseSentence"


Approach (Expected / Optimal – String Traversal):
1. Traverse the string character by character.
2. Use a flag to indicate start of a new word.
3. If character is a space:
   - Mark next character as start of a new word.
4. If character is not a space:
   - If start of word → convert to uppercase and append.
   - Else → convert to lowercase and append.
5. Skip spaces entirely in the output.

Why this works:
- Each word boundary is detected using space.
- Controlled casing ensures Camel Case compliance.
- Single pass ensures optimal performance.

Time Complexity:
O(n)

Space Complexity:
O(1) extra space (output excluded)


GeeksforGeeks:
https://www.geeksforgeeks.org/camel-case-of-a-given-sentence/

LeetCode:
No direct equivalent problem.
(Related to string manipulation and formatting)
*/

string camelCase(string s) {
    string result;
    bool newWord = false;

    for (char ch : s) {
        if (ch == ' ') {
            newWord = true;
        } else {
            if (newWord) {
                result.push_back(toupper(ch));
                newWord = false;
            } else {
                result.push_back(tolower(ch));
            }
        }
    }

    return result;
}
