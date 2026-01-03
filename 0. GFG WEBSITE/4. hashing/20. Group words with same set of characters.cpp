/*
Problem:
Group Words with Same Set of Characters

Given an array of strings words[],
group together all words that have the same set of characters.
Order of characters and frequency do NOT matter.
Only the presence/absence of characters matters.

Examples:
Input  : words = ["may", "student", "students", "dog", "studentssess", "god", "yam"]
Output :
[
  ["may", "yam"],
  ["dog", "god"],
  ["student", "students", "studentssess"]
]

Explanation:
- "may" and "yam" have the same character set {m, a, y}
- "dog" and "god" have the same character set {d, o, g}
- All student-related words share {s, t, u, d, e, n}


-----------------------------------
Approach (Expected / Optimal – Canonical Key using Set/Bitmask):
-----------------------------------
1. For each word, compute its character set key:
   - Use a boolean array / bitmask / set to mark present characters.
   - Convert it into a canonical string key (e.g., sorted unique characters).
2. Use a hash map:
      key → list of words
3. Insert each word into its corresponding group.
4. Collect and return all groups.

Why this works:
- Words with the same unique character set
  produce the same canonical key.
- Hashing groups them efficiently.

Time Complexity:
O(n * L log L)
  where:
  n = number of words
  L = average word length

Space Complexity:
O(n * L)


GeeksforGeeks:
https://www.geeksforgeeks.org/group-words-same-set-characters/

LeetCode:
No direct equivalent problem.
(Related to grouping and hashing problems)
*/


vector<vector<string>> groupWordsWithSameCharSet(vector<string>& words) {
    unordered_map<string, vector<string>> groups;

    for (string& word : words) {
        vector<bool> present(26, false);

        // Step 1: Mark character presence
        for (char ch : word) {
            present[ch - 'a'] = true;
        }

        // Step 2: Build canonical key
        string key = "";
        for (int i = 0; i < 26; i++) {
            if (present[i]) {
                key.push_back(char('a' + i));
            }
        }

        // Step 3: Group words by key
        groups[key].push_back(word);
    }

    // Step 4: Collect result
    vector<vector<string>> result;
    for (auto& it : groups) {
        result.push_back(it.second);
    }

    return result;
}
